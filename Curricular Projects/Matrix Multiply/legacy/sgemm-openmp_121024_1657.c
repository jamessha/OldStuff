#include <emmintrin.h>

void sgemm(int m, int n, float *A, float *C) {
    __m128 i_vec_1;
    __m128 i_vec_2;
    __m128 i_vec_1_1;
    __m128 i_vec_2_1;

    __m128 j_vec_1;
    __m128 j_vec_2;
    __m128 j_vec_3;
    __m128 j_vec_4;
    __m128 j_vec_5;
    __m128 j_vec_6;
    __m128 j_vec_7;
    __m128 j_vec_8;
    __m128 j_vec_9;
    __m128 j_vec_10;

    __m128 k_vec_1;
    __m128 k_vec_2;
    __m128 k_vec_3;
    __m128 k_vec_4;
    __m128 k_vec_5;
    __m128 k_vec_6;
    __m128 k_vec_7;
    __m128 k_vec_8;
    __m128 k_vec_9;
    __m128 k_vec_10;
    __m128 k_vec_1_1;
    __m128 k_vec_2_1;
    __m128 k_vec_3_1;
    __m128 k_vec_4_1;
    __m128 k_vec_5_1;
    __m128 k_vec_6_1;
    __m128 k_vec_7_1;
    __m128 k_vec_8_1;
    __m128 k_vec_9_1;
    __m128 k_vec_10_1;
	#pragma omp parallel for private (i_vec_1, i_vec_2, i_vec_1_1, i_vec_2_1, j_vec_1, j_vec_2, j_vec_3, j_vec_4, j_vec_5, j_vec_6, j_vec_7, j_vec_8, j_vec_9, j_vec_10, k_vec_1, k_vec_2, k_vec_3, k_vec_4, k_vec_5, k_vec_6, k_vec_7, k_vec_8, k_vec_9, k_vec_10, k_vec_1_1, k_vec_2_1, k_vec_3_1, k_vec_4_1, k_vec_5_1, k_vec_6_1, k_vec_7_1, k_vec_8_1, k_vec_9_1, k_vec_10_1)
    for (int j = 0; j < m - m % 10; j += 10) {
        for (int i = 0; i < m - m % 8; i += 8) {

            k_vec_1 = _mm_loadu_ps(C + i + (j + 0) * m);
            k_vec_2 = _mm_loadu_ps(C + i + (j + 1) * m);
            k_vec_3 = _mm_loadu_ps(C + i + (j + 2) * m);
            k_vec_4 = _mm_loadu_ps(C + i + (j + 3) * m);
            k_vec_5 = _mm_loadu_ps(C + i + (j + 4) * m);
            k_vec_6 = _mm_loadu_ps(C + i + (j + 5) * m);
            k_vec_7 = _mm_loadu_ps(C + i + (j + 6) * m);
            k_vec_8 = _mm_loadu_ps(C + i + (j + 7) * m);
            k_vec_9 = _mm_loadu_ps(C + i + (j + 8) * m);
            k_vec_10 = _mm_loadu_ps(C + i + (j + 9) * m);
            k_vec_1_1 = _mm_loadu_ps(C + i + 4 + (j + 2) * m);
            k_vec_2_1 = _mm_loadu_ps(C + i + 4 + (j + 3) * m);
            k_vec_3_1 = _mm_loadu_ps(C + i + 4 + (j + 4) * m);
            k_vec_4_1 = _mm_loadu_ps(C + i + 4 + (j + 5) * m);
            k_vec_5_1 = _mm_loadu_ps(C + i + 4 + (j + 6) * m);
            k_vec_6_1 = _mm_loadu_ps(C + i + 4 + (j + 7) * m);
            k_vec_7_1 = _mm_loadu_ps(C + i + 4 + (j + 6) * m);
            k_vec_8_1 = _mm_loadu_ps(C + i + 4 + (j + 7) * m);
            k_vec_9_1 = _mm_loadu_ps(C + i + 4 + (j + 8) * m);
            k_vec_10_1 = _mm_loadu_ps(C + i + 4 + (j + 9) * m);

            for (int k = 0; k < n - n % 2; k += 2) {
                i_vec_1 = _mm_loadu_ps((A + i + (k + 0) * m));
                i_vec_2 = _mm_loadu_ps((A + i + (k + 1) * m));
                i_vec_1_1 = _mm_loadu_ps((A + i + 4 + (k + 0) * m));
                i_vec_2_1 = _mm_loadu_ps((A + i + 4 + (k + 1) * m));

                j_vec_1 = _mm_set1_ps(A[j + (k + 0) * m + 0]);
                j_vec_2 = _mm_set1_ps(A[j + (k + 0) * m + 1]);
                j_vec_3 = _mm_set1_ps(A[j + (k + 0) * m + 2]);
                j_vec_4 = _mm_set1_ps(A[j + (k + 0) * m + 3]);
                j_vec_5 = _mm_set1_ps(A[j + (k + 0) * m + 4]);
                j_vec_6 = _mm_set1_ps(A[j + (k + 0) * m + 5]);
                j_vec_7 = _mm_set1_ps(A[j + (k + 0) * m + 6]);
                j_vec_8 = _mm_set1_ps(A[j + (k + 0) * m + 7]);
                j_vec_9 = _mm_set1_ps(A[j + (k + 0) * m + 8]);
                j_vec_10 = _mm_set1_ps(A[j + (k + 0) * m + 9]);

                k_vec_1 = _mm_add_ps(k_vec_1, _mm_mul_ps(i_vec_1, j_vec_1));
                k_vec_2 = _mm_add_ps(k_vec_2, _mm_mul_ps(i_vec_1, j_vec_2));
                k_vec_3 = _mm_add_ps(k_vec_3, _mm_mul_ps(i_vec_1, j_vec_3));
                k_vec_4 = _mm_add_ps(k_vec_4, _mm_mul_ps(i_vec_1, j_vec_4));
                k_vec_5 = _mm_add_ps(k_vec_5, _mm_mul_ps(i_vec_1, j_vec_5));
                k_vec_6 = _mm_add_ps(k_vec_6, _mm_mul_ps(i_vec_1, j_vec_6));
                k_vec_7 = _mm_add_ps(k_vec_7, _mm_mul_ps(i_vec_1, j_vec_7));
                k_vec_8 = _mm_add_ps(k_vec_8, _mm_mul_ps(i_vec_1, j_vec_8));
                k_vec_9 = _mm_add_ps(k_vec_9, _mm_mul_ps(i_vec_1, j_vec_9));
                k_vec_10 = _mm_add_ps(k_vec_10, _mm_mul_ps(i_vec_1, j_vec_10));
                k_vec_1_1 = _mm_add_ps(k_vec_1_1, _mm_mul_ps(i_vec_1_1, j_vec_1));
                k_vec_2_1 = _mm_add_ps(k_vec_2_1, _mm_mul_ps(i_vec_1_1, j_vec_2));
                k_vec_3_1 = _mm_add_ps(k_vec_3_1, _mm_mul_ps(i_vec_1_1, j_vec_3));
                k_vec_4_1 = _mm_add_ps(k_vec_4_1, _mm_mul_ps(i_vec_1_1, j_vec_4));
                k_vec_5_1 = _mm_add_ps(k_vec_5_1, _mm_mul_ps(i_vec_1_1, j_vec_5));
                k_vec_6_1 = _mm_add_ps(k_vec_6_1, _mm_mul_ps(i_vec_1_1, j_vec_6));
                k_vec_7_1 = _mm_add_ps(k_vec_7_1, _mm_mul_ps(i_vec_1_1, j_vec_7));
                k_vec_8_1 = _mm_add_ps(k_vec_8_1, _mm_mul_ps(i_vec_1_1, j_vec_8));
                k_vec_9_1 = _mm_add_ps(k_vec_9_1, _mm_mul_ps(i_vec_1_1, j_vec_9));
                k_vec_10_1 = _mm_add_ps(k_vec_10_1, _mm_mul_ps(i_vec_1_1, j_vec_10));

                j_vec_1 = _mm_set1_ps(A[j + (k + 1) * m + 0]);
                j_vec_2 = _mm_set1_ps(A[j + (k + 1) * m + 1]);
                j_vec_3 = _mm_set1_ps(A[j + (k + 1) * m + 2]);
                j_vec_4 = _mm_set1_ps(A[j + (k + 1) * m + 3]);
                j_vec_5 = _mm_set1_ps(A[j + (k + 1) * m + 4]);
                j_vec_6 = _mm_set1_ps(A[j + (k + 1) * m + 5]);
                j_vec_7 = _mm_set1_ps(A[j + (k + 1) * m + 6]);
                j_vec_8 = _mm_set1_ps(A[j + (k + 1) * m + 7]);
                j_vec_9 = _mm_set1_ps(A[j + (k + 1) * m + 8]);
                j_vec_10 = _mm_set1_ps(A[j + (k + 1) * m + 9]);

                k_vec_1 = _mm_add_ps(k_vec_1, _mm_mul_ps(i_vec_2, j_vec_1));
                k_vec_2 = _mm_add_ps(k_vec_2, _mm_mul_ps(i_vec_2, j_vec_2));
                k_vec_3 = _mm_add_ps(k_vec_3, _mm_mul_ps(i_vec_2, j_vec_3));
                k_vec_4 = _mm_add_ps(k_vec_4, _mm_mul_ps(i_vec_2, j_vec_4));
                k_vec_5 = _mm_add_ps(k_vec_5, _mm_mul_ps(i_vec_2, j_vec_5));
                k_vec_6 = _mm_add_ps(k_vec_6, _mm_mul_ps(i_vec_2, j_vec_6));
                k_vec_7 = _mm_add_ps(k_vec_7, _mm_mul_ps(i_vec_2, j_vec_7));
                k_vec_8 = _mm_add_ps(k_vec_8, _mm_mul_ps(i_vec_2, j_vec_8));
                k_vec_9 = _mm_add_ps(k_vec_9, _mm_mul_ps(i_vec_2, j_vec_9));
                k_vec_10 = _mm_add_ps(k_vec_10, _mm_mul_ps(i_vec_2, j_vec_10));
                k_vec_1_1 = _mm_add_ps(k_vec_1_1, _mm_mul_ps(i_vec_2_1, j_vec_1));
                k_vec_2_1 = _mm_add_ps(k_vec_2_1, _mm_mul_ps(i_vec_2_1, j_vec_2));
                k_vec_3_1 = _mm_add_ps(k_vec_3_1, _mm_mul_ps(i_vec_2_1, j_vec_3));
                k_vec_4_1 = _mm_add_ps(k_vec_4_1, _mm_mul_ps(i_vec_2_1, j_vec_4));
                k_vec_5_1 = _mm_add_ps(k_vec_5_1, _mm_mul_ps(i_vec_2_1, j_vec_5));
                k_vec_6_1 = _mm_add_ps(k_vec_6_1, _mm_mul_ps(i_vec_2_1, j_vec_6));
                k_vec_7_1 = _mm_add_ps(k_vec_7_1, _mm_mul_ps(i_vec_2_1, j_vec_7));
                k_vec_8_1 = _mm_add_ps(k_vec_8_1, _mm_mul_ps(i_vec_2_1, j_vec_8));
                k_vec_9_1 = _mm_add_ps(k_vec_9_1, _mm_mul_ps(i_vec_2_1, j_vec_9));
                k_vec_10_1 = _mm_add_ps(k_vec_10_1, _mm_mul_ps(i_vec_2_1, j_vec_10));
            }

            _mm_storeu_ps((C + i + (j + 0) * m), k_vec_1);
            _mm_storeu_ps((C + i + (j + 1) * m), k_vec_2);
            _mm_storeu_ps((C + i + (j + 2) * m), k_vec_3);
            _mm_storeu_ps((C + i + (j + 3) * m), k_vec_4);
            _mm_storeu_ps((C + i + (j + 4) * m), k_vec_5);
            _mm_storeu_ps((C + i + (j + 5) * m), k_vec_6);
            _mm_storeu_ps((C + i + (j + 6) * m), k_vec_7);
            _mm_storeu_ps((C + i + (j + 7) * m), k_vec_8);
            _mm_storeu_ps((C + i + (j + 8) * m), k_vec_9);
            _mm_storeu_ps((C + i + (j + 9) * m), k_vec_10);
            _mm_storeu_ps((C + i + 4 + (j + 0) * m), k_vec_1_1);
            _mm_storeu_ps((C + i + 4 + (j + 1) * m), k_vec_2_1);
            _mm_storeu_ps((C + i + 4 + (j + 2) * m), k_vec_3_1);
            _mm_storeu_ps((C + i + 4 + (j + 3) * m), k_vec_4_1);
            _mm_storeu_ps((C + i + 4 + (j + 4) * m), k_vec_5_1);
            _mm_storeu_ps((C + i + 4 + (j + 5) * m), k_vec_6_1);
            _mm_storeu_ps((C + i + 4 + (j + 6) * m), k_vec_7_1);
            _mm_storeu_ps((C + i + 4 + (j + 7) * m), k_vec_8_1);
            _mm_storeu_ps((C + i + 4 + (j + 8) * m), k_vec_9_1);
            _mm_storeu_ps((C + i + 4 + (j + 9) * m), k_vec_10_1);
        }
    }

    //Tail from unrolling k
    for (int k = n - n % 2; k < n; k++) {
        for (int i = 0; i < m - m % 8; i += 8) {
            i_vec_1 = _mm_loadu_ps((A + i + k * m));
            i_vec_2 = _mm_loadu_ps((A + i + 4 + k * m));
            for (int j = 0; j < m - m % 10; j += 1) {
                j_vec_1 = _mm_set1_ps(A[j + (k + 0) * m + 0]);
                k_vec_1 = _mm_loadu_ps(C + i + (j + 0) * m);
                k_vec_2 = _mm_loadu_ps(C + i + 4 + (j + 0) * m);
                k_vec_1 = _mm_add_ps(k_vec_1, _mm_mul_ps(i_vec_1, j_vec_1));
                k_vec_2 = _mm_add_ps(k_vec_2, _mm_mul_ps(i_vec_2, j_vec_1));
                _mm_storeu_ps((C + i + (j + 0) * m), k_vec_1);
                _mm_storeu_ps((C + i + 4 + (j + 0) * m), k_vec_2);
            }
        }
    }

    //Tail from unrolling j
    for (int j = m - m % 10; j < m; j++) {
        for (int i = 0; i < m - m % 8; i += 4) {
            k_vec_1 = _mm_loadu_ps(C + i + (j + 0) * m);
            for (int k = 0; k < n; k++) {
                j_vec_1 = _mm_set1_ps(A[j + (k + 0) * m + 0]);
                i_vec_1 = _mm_loadu_ps((A + i + k * m));
                k_vec_1 = _mm_add_ps(k_vec_1, _mm_mul_ps(i_vec_1, j_vec_1));
            }
            _mm_storeu_ps((C + i + (j + 0) * m), k_vec_1);
        }
    }

    //Tail from vectorizing i
    for (int i = m - m % 8; i < m; i++){
        for (int k = 0; k < n; k++){
            for (int j = 0; j < m - m%10; j += 2){
                C[i + (j + 0) * m] += A[i + k * m] * A[(j + 0) + k * m];
                C[i + (j + 1) * m] += A[i + k * m] * A[(j + 1) + k * m];
            }
        }
    }
    
    //Tail from unrolling the tail from vectorizing i
    for (int j = m - m%10; j < m; j += 1){
        for (int k = 0; k < n; k++){
            for (int i = m - m % 8; i < m; i++){
                C[i + (j + 0) * m] += A[i + k * m] * A[(j + 0) + k * m];
            }
        }
    }

// CONSIDER PADDING tails are bad
// 1000 by 32 matrix 	 56.3369 Gflop/s
// 7919 by 32 matrix 	 37.6739 Gflop/s
// 10000 by 32 matrix 	 55.3801 Gflop/s
// 1000 by 91 matrix 	 27.0952 Gflop/s
// 7919 by 91 matrix 	 23.0938 Gflop/s
// 10000 by 91 matrix 	 32.306 Gflop/s
// 1000 by 100 matrix 	 56.5696 Gflop/s
// 7919 by 100 matrix 	 37.8181 Gflop/s
// 10000 by 100 matrix 	 56.5165 Gflop/s
}

