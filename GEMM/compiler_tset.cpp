#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>



#define A(i,j) a[ (j) + (i) ]
#define B(i,j) b[ (j) + (i) ]
#define C(i,j) c[ (j) + (i) ]

/* Routine for computing C = A * B + C */

void MY_MMult( int m, int n, int k, double *a, 
                                    double *b,
                                    double *c )
{
  int i, j, p;

  for ( i=0; i<m; i++ ){        /* Loop over the rows of C */
    for ( j=0; j<n; j++ ){        /* Loop over the columns of C */
      for ( p=0; p<k; p++ ){        /* Update C( i,j ) with the inner
				       product of the ith row of A and
				       the jth column of B */
	C( i,j ) = C( i,j ) +  A( i,p ) * B( p,j );
      }
    }
  }
}

void random_init(int m, int n, double * a, int lda){
    for(int j=0;j<n;j++){
        for(int i=0;i<m;i++)
            A(i,j) = 2.0 * drand48() - 1.0;
    }
}

void display(double * matrix, int m, int n){
    for(int j=0;j<n;j++){
        for(int i=0;i<m;i++){
            printf("%f ",matrix[j*m+i]);
        }
        printf("\n");
    }
    return;
}

int main(){

    int m = 64;
    int n = 16;
    int k = 1;

    double * A = (double*)calloc(m*k,sizeof(double));
    double * B = (double*)calloc(k*n,sizeof(double));
    double * C = (double*)calloc(m*n,sizeof(double));

    struct timeval start,finish;
    double gflops = 2.0 * m*n*k * 1.0e-09;
    srand((unsigned)time(NULL));

    if(A==NULL || B==NULL || C==NULL){
        printf("Out of Memory!\n");
        exit(EXIT_FAILURE);
    }

    random_init(m,k,A,m);
    random_init(k,n,B,k);
    random_init(m,n,C,m);

    MY_MMult(m,n,k,A,B,C);
    double duration = ((double)(finish.tv_sec-start.tv_sec)*1000000 + (double)(finish.tv_usec-start.tv_usec)) / 1000000;

    if(m<=8){
        printf("Matrix A : \n");
        display(A,m,k);

        printf("Matrix B : \n");
        display(B,k,n);

        printf("Dot Product Result : \n");
        display(C,m,n);
    }
    
    printf("Dot product took %f seconds GFLOPS : %f\n",duration,gflops/duration);
    return 0;
}