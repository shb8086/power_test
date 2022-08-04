
#define A(i,j) a[ (j) + (i) ]
#define B(i,j) b[ (j) + (i) ]
#define C(i,j) c[ (j) + (i) ]

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