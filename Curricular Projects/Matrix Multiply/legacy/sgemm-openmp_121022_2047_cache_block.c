#include <emmintrin.h>

void sgemm(int m, int n, float *A, float *C) {
    __m128 i_vec_1;
    __m128 i_vec_2;

    __m128 j_vec_1;
    __m128 j_vec_2;
    __m128 j_vec_3;
    __m128 j_vec_4;
    __m128 j_vec_5;
    __m128 j_vec_6;

    __m128 k_vec_1;
    __m128 k_vec_2;
    __m128 k_vec_3;
    __m128 k_vec_4;
    __m128 k_vec_5;
    __m128 k_vec_6;

    int block_size = 200;
    #pragma omp parallel for private (i_vec_1, i_vec_2, j_vec_1, j_vec_2, j_vec_3, j_vec_4, j_vec_5, j_vec_6, k_vec_1, k_vec_2, k_vec_3, k_vec_4, k_vec_5, k_vec_6)
    for (int block_x = 0; block_x < m - m % block_size; block_x += block_size) {
        for (int block_y = 0; block_y < m - m % block_size; block_y += block_size) {
            for (int j = block_y; j < (block_y + block_size) - (block_size) % 6; j += 6) {
                for (int i = block_x; i < (block_x + block_size) - (block_size) % 4; i += 4) {

                    k_vec_1 = _mm_loadu_ps(C + i + (j + 0) * m);
                    k_vec_2 = _mm_loadu_ps(C + i + (j + 1) * m);
                    k_vec_3 = _mm_loadu_ps(C + i + (j + 2) * m);
                    k_vec_4 = _mm_loadu_ps(C + i + (j + 3) * m);
                    k_vec_5 = _mm_loadu_ps(C + i + (j + 4) * m);
                    k_vec_6 = _mm_loadu_ps(C + i + (j + 5) * m);

                    for (int k = 0; k < n - n % 2; k += 2) {
                        i_vec_1 = _mm_loadu_ps((A + i + (k + 0) * m));
                        i_vec_2 = _mm_loadu_ps((A + i + (k + 1) * m));

                        j_vec_1 = _mm_set1_ps(A[j + (k + 0) * m + 0]);
                        j_vec_2 = _mm_set1_ps(A[j + (k + 0) * m + 1]);
                        j_vec_3 = _mm_set1_ps(A[j + (k + 0) * m + 2]);
                        j_vec_4 = _mm_set1_ps(A[j + (k + 0) * m + 3]);
                        j_vec_5 = _mm_set1_ps(A[j + (k + 0) * m + 4]);
                        j_vec_6 = _mm_set1_ps(A[j + (k + 0) * m + 5]);

                        k_vec_1 = _mm_add_ps(k_vec_1, _mm_mul_ps(i_vec_1, j_vec_1));
                        k_vec_2 = _mm_add_ps(k_vec_2, _mm_mul_ps(i_vec_1, j_vec_2));
                        k_vec_3 = _mm_add_ps(k_vec_3, _mm_mul_ps(i_vec_1, j_vec_3));
                        k_vec_4 = _mm_add_ps(k_vec_4, _mm_mul_ps(i_vec_1, j_vec_4));
                        k_vec_5 = _mm_add_ps(k_vec_5, _mm_mul_ps(i_vec_1, j_vec_5));
                        k_vec_6 = _mm_add_ps(k_vec_6, _mm_mul_ps(i_vec_1, j_vec_6));

                        j_vec_1 = _mm_set1_ps(A[j + (k + 1) * m + 0]);
                        j_vec_2 = _mm_set1_ps(A[j + (k + 1) * m + 1]);
                        j_vec_3 = _mm_set1_ps(A[j + (k + 1) * m + 2]);
                        j_vec_4 = _mm_set1_ps(A[j + (k + 1) * m + 3]);
                        j_vec_5 = _mm_set1_ps(A[j + (k + 1) * m + 4]);
                        j_vec_6 = _mm_set1_ps(A[j + (k + 1) * m + 5]);

                        k_vec_1 = _mm_add_ps(k_vec_1, _mm_mul_ps(i_vec_2, j_vec_1));
                        k_vec_2 = _mm_add_ps(k_vec_2, _mm_mul_ps(i_vec_2, j_vec_2));
                        k_vec_3 = _mm_add_ps(k_vec_3, _mm_mul_ps(i_vec_2, j_vec_3));
                        k_vec_4 = _mm_add_ps(k_vec_4, _mm_mul_ps(i_vec_2, j_vec_4));
                        k_vec_5 = _mm_add_ps(k_vec_5, _mm_mul_ps(i_vec_2, j_vec_5));
                        k_vec_6 = _mm_add_ps(k_vec_6, _mm_mul_ps(i_vec_2, j_vec_6));
                    }

                    _mm_storeu_ps((C + i + (j + 0) * m), k_vec_1);
                    _mm_storeu_ps((C + i + (j + 1) * m), k_vec_2);
                    _mm_storeu_ps((C + i + (j + 2) * m), k_vec_3);
                    _mm_storeu_ps((C + i + (j + 3) * m), k_vec_4);
                    _mm_storeu_ps((C + i + (j + 4) * m), k_vec_5);
                    _mm_storeu_ps((C + i + (j + 5) * m), k_vec_6);
                }
            }
            //Tail from unrolling k
            for (int k = n - n % 2; k < n; k++) {
                for (int i = block_x; i < (block_x + block_size) - (block_size) % 4; i++) {
                    for (int j = block_y; j < (block_y + block_size) - (block_size) % 6; j += 1) {
                        C[i + j * m] += A[i + k * m] * A[j + k * m];
                    }
                }
            }

            //Tail from unrolling j
            for (int j = (block_y + block_size) - (block_size) % 6; j < (block_y + block_size); j++) {
                for (int i = block_x; i < (block_x + block_size) - (block_size) % 4; i++) {
                    for (int k = 0; k < n; k++) {
                        C[i + j * m] += A[i + k * m] * A[j + k * m];
                    }
                }
            }

            //Tail from vectorizing i
            for (int i = (block_x + block_size) - (block_size) % 4; i < (block_x + block_size); i++) {
                for (int k = 0; k < n; k++) {
                    for (int j = block_y; j < (block_y + block_size); j++) {
                        C[i + j * m] += A[i + k * m] * A[j + k * m];
                    }
                }
            }
        }
    }

    //Tail from j blocking vectorized
    for (int j = m - m % block_size; j < m; j++) {
        for (int k = 0; k < n; k++) {
            j_vec_1 = _mm_set1_ps(A[j + (k + 0) * m + 0]);
            for (int i = 0; i < (m - m % block_size) % 8; i += 8) {
                k_vec_1 = _mm_loadu_ps(C + i + (j + 0) * m);
                k_vec_2 = _mm_loadu_ps(C + i + 4 + (j + 0) * m);
                i_vec_1 = _mm_loadu_ps((A + i + (k + 0) * m));
                i_vec_2 = _mm_loadu_ps((A + i + 4 + (k + 0) * m));
                k_vec_1 = _mm_add_ps(k_vec_1, _mm_mul_ps(i_vec_1, j_vec_1));
                k_vec_2 = _mm_add_ps(k_vec_1, _mm_mul_ps(i_vec_2, j_vec_1));
                _mm_storeu_ps((C + i + (j + 0) * m), k_vec_1);
                _mm_storeu_ps((C + i + 4 + (j + 0) * m), k_vec_1);
            }
        }
    }

    //Tail from vectorizing j blocking
    for (int i = (m - m % block_size) % 4; i < m - m % block_size; i += 4) {
        for (int j = m - m % block_size; j < m; j++) {
            for (int k = 0; k < n; k++) {
                C[i + j * m] += A[i + k * m] * A[j + k * m];
            }
        }
    }

    //Tail from i blocking
    for (int i = m - m % block_size; i < m; i++) {
        for (int k = 0; k < n; k++) {
            for (int j = 0; j < m; j++) {
                C[i + j * m] += A[i + k * m] * A[j + k * m];
            }
        }
    }


}


