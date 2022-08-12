#include <iostream>
#include <cmath>
#include <chrono>
#include "kernels/gemm_ref.h"

extern "C" {
  void gemm_asm_power_8_4_1_sp( double const * i_a,
                                double const * i_b,
                                double       * io_c );

  void gemm_asm_power_8_4_1_dp( double const * i_a,
                                double const * i_b,
                                double       * io_c );
}

double max_diff( double const * i_mat0,
                 double const * i_mat1,
                 unsigned int  i_m,
                 unsigned int  i_n,
                 unsigned int  i_ld ) {
  double l_max_diff = 0;

  for( unsigned int l_m = 0; l_m < i_m; l_m++ ) {
    for( unsigned int l_n = 0; l_n < i_n; l_n++ ) {
      double l_diff = i_mat0[ l_n*i_ld + l_m ] - i_mat1[ l_n*i_ld + l_m ];
      l_diff = std::abs( l_diff );

      l_max_diff = std::max( l_max_diff, l_diff );
    }
  }

  return l_max_diff;
}

void display (double const * l_a,
              double const * l_b,
              double const * l_c,
              double const * l_c_ref,
              std::size_t l_size){
  for( unsigned int l_id = 0; l_id < l_size; l_id++ ) {
    std::cout<< "l_a[" << l_id << "]= ";
    std::cout<< double(l_a[l_id])<< std::endl;
  }
  std::cout<< std::endl;
  for( unsigned int l_id = 0; l_id < l_size; l_id++ ) {
    std::cout<< "l_b[" << l_id << "]= ";
    std::cout<< double(l_b[l_id])<< std::endl;
  }
  std::cout<< std::endl;
  for( unsigned int l_id = 0; l_id < l_size; l_id++ ) {
    std::cout<< "l_c[" << l_id << "]= ";
    std::cout<< double(l_c[l_id])<< std::endl;
  }
  std::cout<< std::endl;
  for( unsigned int l_id = 0; l_id < l_size; l_id++ ) {
    std::cout<< "l_c_ref[" << l_id << "]= ";
    std::cout<< double(l_c_ref[l_id])<< std::endl;
  }
}

int main() {
  // allocate memory
  std::size_t l_size = 4*4;
  double * l_a = new double[ l_size ];
  double * l_b = new double[ l_size ];
  double * l_c = new double[ l_size ];
  double * l_c_ref = new double[ l_size ];

  double l_max_diff = 0;
  std::chrono::high_resolution_clock::time_point l_tp0, l_tp1;
  std::chrono::duration<double> l_dur;
  double l_gflops = 0;
  unsigned int l_n_repetitions = 0;

  // init data
  srand48( time(NULL) );
  for( unsigned int l_id = 0; l_id < l_size; l_id++ ) {
    l_a[l_id] = l_id;
  }
  for( unsigned int l_id = 0; l_id < l_size; l_id++ ) {
    l_b[l_id] = l_id *2;
  }
  for( unsigned int l_id = 0; l_id < l_size; l_id++ ) {
    l_c[l_id] = l_id *10;
  }
  for( unsigned int l_id = 0; l_id < l_size; l_id++ ) {
    l_c_ref[l_id] = l_c[l_id];
  }

  /*
   * VS: 8, 4, 1
   */
  l_n_repetitions = 50000000;

  std::cout << "testing gemm_asm_power_8_4_1 kernel" << std::endl;

  // run reference implementation
  gemm_ref_mnk( l_a,
                l_b,
                l_c_ref,
                4,
                4,
                1,
                4,
                1,
                4 );

  // run assembly kernel
  gemm_asm_power_8_4_1_dp( l_a,
                           l_b,
                           l_c );

  l_max_diff = max_diff( l_c_ref,
                         l_c,
                         4,
                         4,
                         1 );

  std::cout << "  maximum difference: " << l_max_diff << "\n";

  // time power kernel
  l_tp0 = std::chrono::high_resolution_clock::now();
  for( unsigned int l_re = 0; l_re < l_n_repetitions; l_re++ ) {
    gemm_asm_power_8_4_1_dp( l_a,
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

  display(l_a,
          l_b,
          l_c,
          l_c_ref,
          l_size);

  // free memory
  delete[] l_a;
  delete[] l_b;
  delete[] l_c;
  delete[] l_c_ref;

  return EXIT_SUCCESS;
}
