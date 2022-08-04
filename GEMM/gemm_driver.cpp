#include <iostream>
#include <cmath>
#include <chrono>
#include "gemm_ref.h"

extern "C" {
  void gemm_asm_power_16_6_1( float const * i_a,
                              float const * i_b,
                              float       * io_c );
}

float max_diff( float const * i_mat0,
                float const * i_mat1,
                unsigned int  i_m,
                unsigned int  i_n,
                unsigned int  i_ld ) {
  float l_max_diff = 0;

  for( unsigned int l_m = 0; l_m < i_m; l_m++ ) {
    for( unsigned int l_n = 0; l_n < i_n; l_n++ ) {
      float l_diff = i_mat0[ l_n*i_ld + l_m ] - i_mat1[ l_n*i_ld + l_m ];
      l_diff = std::abs( l_diff );

      l_max_diff = std::max( l_max_diff, l_diff );
    }
  }

  return l_max_diff;
}

int main() {
  // allocate memory
  std::size_t l_size = 64*64;
  float * l_a = new float[ l_size ];
  float * l_b = new float[ l_size ];
  float * l_c = new float[ l_size ];
  float * l_c_ref = new float[ l_size ];

  float l_max_diff = 0;
  std::chrono::high_resolution_clock::time_point l_tp0, l_tp1;
  std::chrono::duration<double> l_dur;
  double l_gflops = 0;
  unsigned int l_n_repetitions = 0;

  // init data
  srand48( time(NULL) );
  for( unsigned int l_id = 0; l_id < l_size; l_id++ ) {
    l_a[l_id] = (float) drand48();
  }
  for( unsigned int l_id = 0; l_id < l_size; l_id++ ) {
    l_b[l_id] = (float) drand48();
  }
  for( unsigned int l_id = 0; l_id < l_size; l_id++ ) {
    l_c[l_id] = (float) drand48();
  }
  for( unsigned int l_id = 0; l_id < l_size; l_id++ ) {
    l_c_ref[l_id] = l_c[l_id];
  }

  /*
   * SVE: 16, 6, 1
   */
  l_n_repetitions = 50000000;

  std::cout << "testing gemm_asm_power_16_6_1 kernel" << std::endl;

  // run reference implementation
  gemm_ref_mnk( l_a,
                l_b,
                l_c_ref,
                64,
                6,
                1,
                64,
                1,
                64 );

  // run assembly kernel
  gemm_asm_power_16_6_1( l_a,
                         l_b,
                         l_c );

  l_max_diff = max_diff( l_c_ref,
                         l_c,
                         64,
                         6,
                         1 );

  std::cout << "  maximum difference: " << l_max_diff << "\n";

  // time sve kernel
  l_tp0 = std::chrono::high_resolution_clock::now();
  for( unsigned int l_re = 0; l_re < l_n_repetitions; l_re++ ) {
    gemm_asm_power_16_6_1( l_a,
                           l_b,
                          l_c );
  }
  l_tp1 = std::chrono::high_resolution_clock::now();

  l_dur = std::chrono::duration_cast< std::chrono::duration< double> >( l_tp1 - l_tp0 );

  std::cout << "  duration: " << l_dur.count() << " seconds" << std::endl;
  l_gflops  = l_n_repetitions;
  l_gflops *= 64 * 6 * 1 * 2;
  l_gflops *= 1.0E-9;
  l_gflops /= l_dur.count();
  std::cout << "  GFLOPS: " << l_gflops << std::endl;

  // free memory
  delete[] l_a;
  delete[] l_b;
  delete[] l_c;
  delete[] l_c_ref;

  return EXIT_SUCCESS;
}
