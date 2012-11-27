#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <cblas.h>

/* Your function must have the following signature: */

void sgemm( int m, int n, float *A, float *C );

/* The benchmarking program */

int main( int argc, char **argv )
{
    srand(time(NULL));

    double counter_random = 0.0;
    double total_random = 0.0;
    int sub50_random = 0;
    int m, n;

    printf("\nTesting random sizes from m = [1000, 10000] to n = [32, 100] 10 times\n");

    /* Try different size */
    for ( int i = 0; i < 10; i++ ){
  
	m = 1000 + (rand() % 9001);
	n = 32 + (rand() % 69);

        /* Allocate and fill 2 random matrices A, C */
        float *A = (float*) malloc( m * n * sizeof(float) );
        float *C = (float*) malloc( m * m * sizeof(float) );
    
        for( int i = 0; i < m*n; i++ ) A[i] = 2 * drand48() - 1;
        for( int i = 0; i < m*m; i++ ) C[i] = 2 * drand48() - 1;
    
        /* measure Gflop/s rate; time a sufficiently long sequence of calls to eliminate noise */
        double Gflop_s, seconds = -1.0;
        for( int n_iterations = 1; seconds < 0.1; n_iterations *= 2 ) 
        {
            /* warm-up */
            sgemm( m, n, A, C );
      
            /* measure time */
            struct timeval start, end;
            gettimeofday( &start, NULL );
            for( int i = 0; i < n_iterations; i++ )
                sgemm( m,n, A, C );
            gettimeofday( &end, NULL );
            seconds = (end.tv_sec - start.tv_sec) + 1.0e-6 * (end.tv_usec - start.tv_usec);
      
            /* compute Gflop/s rate */
            Gflop_s = 2e-9 * n_iterations * m * m * n / seconds;
        }
    
        printf( "%d by %d matrix \t %g Gflop/s\n", m, n, Gflop_s );
	total_random = total_random + Gflop_s;
	counter_random++;
	if (Gflop_s < 50.0) {
            sub50_random++;
	}

    
        /* Ensure that error does not exceed the theoretical error bound */
		
        /* Set initial C to 0 and do matrix multiply of A*B */
        memset( C, 0, sizeof( float ) * m * m );
        sgemm( m, n, A, C );

        /* Subtract A*B from C using standard sgemm (note that this should be 0 to within machine roundoff) */
        cblas_sgemm( CblasColMajor,CblasNoTrans,CblasTrans, m,m,n, -1, A,m, A,m, 1, C,m );

        /* Subtract the maximum allowed roundoff from each element of C */
        for( int i = 0; i < m*n; i++ ) A[i] = fabs( A[i] );
        for( int i = 0; i < m*m; i++ ) C[i] = fabs( C[i] );
        cblas_sgemm( CblasColMajor,CblasNoTrans,CblasTrans, m,m,n, -3.0*FLT_EPSILON*n, A,m, A,m, 1, C,m );

        /* After this test if any element in C is still positive something went wrong in square_sgemm */
        for( int i = 0; i < m * m; i++ )
            if( C[i] > 0 ) {
                printf( "FAILURE: error in matrix multiply exceeds an acceptable margin\n" );
                return -1;
            }

        /* release memory */
        free( C );
        free( A );
    }

    double average_random = total_random/counter_random;
    int total = 0;
    printf("\nAverage for random sizes: %.5f Gflop/s\n", average_random);
    printf("\nNumber of matrices that didn't achieve at least 50 Gflop/s: %d\n", sub50_random);
    printf("\nPotential Grade for proj3-2:\n");

    if (average_random >= 50){
	total = 55;
	printf("%d/55\n", total);
    }
    else if (average_random >= 45){
	total = 50;
	printf("%d/55\n", total);
    }
    else if (average_random >= 40){
	total = 45;
	printf("%d/55\n", total);
    }
    else if (average_random >= 35){
	total = 35;
	printf("%d/55\n", total);
    }
    else if (average_random >= 30){
	total = 25;
	printf("%d/55\n", total);
    }
    else if (average_random >= 25){
	total = 15;
	printf("%d/55\n", total);
    }
    else if (average_random >= 20){
	total = 10;
	printf("%d/55\n", total);
    }
    else if (average_random >= 15){
	total = 5;
	printf("%d/55\n", total);
    }
    else {
	total = 0;
	printf("%d/55\n", total);
    }
}
