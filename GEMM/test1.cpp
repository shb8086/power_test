#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <iostream>
#include <cmath>
#include <chrono>

void gemm( int m, int n, int k, float *a, 
                                    float *b,
                                    float *c )
{
  int i, j, p;

  for ( i=0; i<m; i++ ){        /* Loop over the rows of C */
    for ( j=0; j<n; j++ ){        /* Loop over the columns of C */
      for ( p=0; p<k; p++ ){        /* Update C( i,j ) with the inner
				       product of the ith row of A and
				       the jth column of B */
	    c[i+j] = c[i+j] + (a[i+p] * b[p+j]);
      }
    }
  }
}


void show (float const * matrix,
           int m,
           int n){
  for( unsigned int l_id = 0; l_id < m*n; l_id++ ) {
    std::cout<< "l_a[" << l_id << "]= ";
    std::cout<< matrix[l_id]<< std::endl;
  }
}

int main(){

    int m = 8;
    int n = 4;
    int k = 1;

    std::size_t l_size = 8*8;
    float * l_a = new float[ m*k ];
    float * l_b = new float[ k*n ];
    float * l_c = new float[ m*n ];

    // init data
    for( unsigned int l_id = 0; l_id < m*k; l_id++ ) {
        l_a[l_id] = l_id;
    }
    for( unsigned int l_id = 0; l_id < k*n; l_id++ ) {
        l_b[l_id] = l_id *5;
    }
    for( unsigned int l_id = 0; l_id < m*n; l_id++ ) {
        l_c[l_id] = l_id *10;
    }

    gemm(m,n,k,l_a,l_b,l_c);

    printf("Matrix A : \n");
    show(l_a,m,k);

    printf("Matrix B : \n");
    show(l_b,k,n);

    printf("Dot Product Result : \n");
    show(l_c,m,n);

    free(l_a);
    free(l_b);
    free(l_c);
    return 0;
}