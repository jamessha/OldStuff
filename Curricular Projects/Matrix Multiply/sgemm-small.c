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

    for (int j = 0; j < m - m % 6; j += 6) {
        for (int i = 0; i < m - m % 4; i += 4) {

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
        for (int i = 0; i < m - m % 4; i += 4) {
            i_vec_1 = _mm_loadu_ps((A + i + k * m));
            for (int j = 0; j < m - m % 6; j += 1) {
                j_vec_1 = _mm_set1_ps(A[j + (k + 0) * m + 0]);
                k_vec_1 = _mm_loadu_ps(C + i + (j + 0) * m);
                k_vec_1 = _mm_add_ps(k_vec_1, _mm_mul_ps(i_vec_1, j_vec_1));
                _mm_storeu_ps((C + i + (j + 0) * m), k_vec_1);
            }
        }
    }

    //Tail from unrolling j
    for (int j = m - m % 6; j < m; j++) {
        for (int i = 0; i < m - m % 4; i += 4) {
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
    for (int i = m - m % 4; i < m; i++)
        for (int k = 0; k < n; k++)
            for (int j = 0; j < m; j++)
                C[i + j * m] += A[i + k * m] * A[j + k * m];
}

