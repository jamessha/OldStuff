#include <emmintrin.h>

void sgemm(int m, int n, float *A, float *C) {
    for (int i = 0; i < m - m%4; i += 4) {
        for (int k = 0; k < n; k++) {
            for (int j = 0; j < m; j += 1) {
                __m128 i_vec = _mm_loadu_ps((A + i + k * m));
                __m128 j_vec = _mm_set1_ps(A[j + k * m]);
                __m128 c_vec = _mm_loadu_ps((C + i + j * m));
                __m128 tmp_vec = _mm_mul_ps(i_vec, j_vec);
                c_vec = _mm_add_ps(c_vec, tmp_vec);
                _mm_storeu_ps((C + i + j * m), c_vec);
            }
        }
    }
    for (int i = m - m%4; i < m; i++)
        for (int k = 0; k < n; k++)
            for (int j = 0; j < m; j++) 
                C[i + j * m] += A[i + k * m] * A[j + k * m];
}
