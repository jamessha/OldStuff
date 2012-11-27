#include <emmintrin.h>
void omp_set_num_threads(int n);
int omp_get_num_procs(void); 

void sgemm(int m, int n, float *A, float *C) {
    __m128 i_vec[10];
    __m128 j_vec[10];
    __m128 k_vec[50];
    
    omp_set_num_threads(omp_get_num_procs());
    #pragma omp parallel
{
    for (int j = 0; j < m - m % 10; j += 10) {
	#pragma omp for nowait private (i_vec, j_vec, k_vec)
        for (int i = 0; i < m - m % 20; i += 20) {
            i_vec[0] = _mm_loadu_ps((A + i      + 0 * m));
            i_vec[2] = _mm_loadu_ps((A + i +  4 + 0 * m));
            i_vec[4] = _mm_loadu_ps((A + i +  8 + 0 * m));
            i_vec[6] = _mm_loadu_ps((A + i + 12 + 0 * m));
            i_vec[8] = _mm_loadu_ps((A + i + 16 + 0 * m));

            j_vec[0] = _mm_set1_ps(A[j + 0 * m + 0]);
            j_vec[1] = _mm_set1_ps(A[j + 0 * m + 1]);
            j_vec[2] = _mm_set1_ps(A[j + 0 * m + 2]);
            j_vec[3] = _mm_set1_ps(A[j + 0 * m + 3]);
            j_vec[4] = _mm_set1_ps(A[j + 0 * m + 4]);
            j_vec[5] = _mm_set1_ps(A[j + 0 * m + 5]);
            j_vec[6] = _mm_set1_ps(A[j + 0 * m + 6]);
            j_vec[7] = _mm_set1_ps(A[j + 0 * m + 7]);
            j_vec[8] = _mm_set1_ps(A[j + 0 * m + 8]);
            j_vec[9] = _mm_set1_ps(A[j + 0 * m + 9]);
            
            k_vec[0]  = _mm_mul_ps(i_vec[0], j_vec[0]);
            k_vec[1]  = _mm_mul_ps(i_vec[0], j_vec[1]);
            k_vec[2]  = _mm_mul_ps(i_vec[0], j_vec[2]);
            k_vec[3]  = _mm_mul_ps(i_vec[0], j_vec[3]);
            k_vec[4]  = _mm_mul_ps(i_vec[0], j_vec[4]);
            k_vec[5]  = _mm_mul_ps(i_vec[0], j_vec[5]);
            k_vec[6]  = _mm_mul_ps(i_vec[0], j_vec[6]);
            k_vec[7]  = _mm_mul_ps(i_vec[0], j_vec[7]);
            k_vec[8]  = _mm_mul_ps(i_vec[0], j_vec[8]);
            k_vec[9]  = _mm_mul_ps(i_vec[0], j_vec[9]);

            k_vec[10] = _mm_mul_ps(i_vec[2], j_vec[0]);
            k_vec[11] = _mm_mul_ps(i_vec[2], j_vec[1]);
            k_vec[12] = _mm_mul_ps(i_vec[2], j_vec[2]);
            k_vec[13] = _mm_mul_ps(i_vec[2], j_vec[3]);
            k_vec[14] = _mm_mul_ps(i_vec[2], j_vec[4]);
            k_vec[15] = _mm_mul_ps(i_vec[2], j_vec[5]);
            k_vec[16] = _mm_mul_ps(i_vec[2], j_vec[6]);
            k_vec[17] = _mm_mul_ps(i_vec[2], j_vec[7]);
            k_vec[18] = _mm_mul_ps(i_vec[2], j_vec[8]);
            k_vec[19] = _mm_mul_ps(i_vec[2], j_vec[9]);

            k_vec[20] = _mm_mul_ps(i_vec[4], j_vec[0]);
            k_vec[21] = _mm_mul_ps(i_vec[4], j_vec[1]);
            k_vec[22] = _mm_mul_ps(i_vec[4], j_vec[2]);
            k_vec[23] = _mm_mul_ps(i_vec[4], j_vec[3]);
            k_vec[24] = _mm_mul_ps(i_vec[4], j_vec[4]);
            k_vec[25] = _mm_mul_ps(i_vec[4], j_vec[5]);
            k_vec[26] = _mm_mul_ps(i_vec[4], j_vec[6]);
            k_vec[27] = _mm_mul_ps(i_vec[4], j_vec[7]);
            k_vec[28] = _mm_mul_ps(i_vec[4], j_vec[8]);
            k_vec[29] = _mm_mul_ps(i_vec[4], j_vec[9]);

            k_vec[30] = _mm_mul_ps(i_vec[6], j_vec[0]);
            k_vec[31] = _mm_mul_ps(i_vec[6], j_vec[1]);
            k_vec[32] = _mm_mul_ps(i_vec[6], j_vec[2]);
            k_vec[33] = _mm_mul_ps(i_vec[6], j_vec[3]);
            k_vec[34] = _mm_mul_ps(i_vec[6], j_vec[4]);
            k_vec[35] = _mm_mul_ps(i_vec[6], j_vec[5]);
            k_vec[36] = _mm_mul_ps(i_vec[6], j_vec[6]);
            k_vec[37] = _mm_mul_ps(i_vec[6], j_vec[7]);
            k_vec[38] = _mm_mul_ps(i_vec[6], j_vec[8]);
            k_vec[39] = _mm_mul_ps(i_vec[6], j_vec[9]);

            k_vec[40] = _mm_mul_ps(i_vec[8], j_vec[0]);
            k_vec[41] = _mm_mul_ps(i_vec[8], j_vec[1]);
            k_vec[42] = _mm_mul_ps(i_vec[8], j_vec[2]);
            k_vec[43] = _mm_mul_ps(i_vec[8], j_vec[3]);
            k_vec[44] = _mm_mul_ps(i_vec[8], j_vec[4]);
            k_vec[45] = _mm_mul_ps(i_vec[8], j_vec[5]);
            k_vec[46] = _mm_mul_ps(i_vec[8], j_vec[6]);
            k_vec[47] = _mm_mul_ps(i_vec[8], j_vec[7]);
            k_vec[48] = _mm_mul_ps(i_vec[8], j_vec[8]);
            k_vec[49] = _mm_mul_ps(i_vec[8], j_vec[9]);
            
            i_vec[1] = _mm_loadu_ps((A + i      + (0 + 1) * m));
            i_vec[3] = _mm_loadu_ps((A + i +  4 + (0 + 1) * m));
            i_vec[5] = _mm_loadu_ps((A + i +  8 + (0 + 1) * m));                
            i_vec[7] = _mm_loadu_ps((A + i + 12 + (0 + 1) * m));
            i_vec[9] = _mm_loadu_ps((A + i + 16 + (0 + 1) * m));

            j_vec[0] = _mm_set1_ps(A[j + (0 + 1) * m + 0]);
            j_vec[1] = _mm_set1_ps(A[j + (0 + 1) * m + 1]);
            j_vec[2] = _mm_set1_ps(A[j + (0 + 1) * m + 2]);
            j_vec[3] = _mm_set1_ps(A[j + (0 + 1) * m + 3]);
            j_vec[4] = _mm_set1_ps(A[j + (0 + 1) * m + 4]);
            j_vec[5] = _mm_set1_ps(A[j + (0 + 1) * m + 5]);
            j_vec[6] = _mm_set1_ps(A[j + (0 + 1) * m + 6]);
            j_vec[7] = _mm_set1_ps(A[j + (0 + 1) * m + 7]);
            j_vec[8] = _mm_set1_ps(A[j + (0 + 1) * m + 8]);
            j_vec[9] = _mm_set1_ps(A[j + (0 + 1) * m + 9]);

            k_vec[0]  = _mm_add_ps(k_vec[0],  _mm_mul_ps(i_vec[1], j_vec[0]));
            k_vec[1]  = _mm_add_ps(k_vec[1],  _mm_mul_ps(i_vec[1], j_vec[1]));
            k_vec[2]  = _mm_add_ps(k_vec[2],  _mm_mul_ps(i_vec[1], j_vec[2]));
            k_vec[3]  = _mm_add_ps(k_vec[3],  _mm_mul_ps(i_vec[1], j_vec[3]));
            k_vec[4]  = _mm_add_ps(k_vec[4],  _mm_mul_ps(i_vec[1], j_vec[4]));
            k_vec[5]  = _mm_add_ps(k_vec[5],  _mm_mul_ps(i_vec[1], j_vec[5]));
            k_vec[6]  = _mm_add_ps(k_vec[6],  _mm_mul_ps(i_vec[1], j_vec[6]));
            k_vec[7]  = _mm_add_ps(k_vec[7],  _mm_mul_ps(i_vec[1], j_vec[7]));
            k_vec[8]  = _mm_add_ps(k_vec[8],  _mm_mul_ps(i_vec[1], j_vec[8]));
            k_vec[9]  = _mm_add_ps(k_vec[9],  _mm_mul_ps(i_vec[1], j_vec[9]));

            k_vec[10] = _mm_add_ps(k_vec[10], _mm_mul_ps(i_vec[3], j_vec[0]));
            k_vec[11] = _mm_add_ps(k_vec[11], _mm_mul_ps(i_vec[3], j_vec[1]));
            k_vec[12] = _mm_add_ps(k_vec[12], _mm_mul_ps(i_vec[3], j_vec[2]));
            k_vec[13] = _mm_add_ps(k_vec[13], _mm_mul_ps(i_vec[3], j_vec[3]));
            k_vec[14] = _mm_add_ps(k_vec[14], _mm_mul_ps(i_vec[3], j_vec[4]));
            k_vec[15] = _mm_add_ps(k_vec[15], _mm_mul_ps(i_vec[3], j_vec[5]));
            k_vec[16] = _mm_add_ps(k_vec[16], _mm_mul_ps(i_vec[3], j_vec[6]));
            k_vec[17] = _mm_add_ps(k_vec[17], _mm_mul_ps(i_vec[3], j_vec[7]));
            k_vec[18] = _mm_add_ps(k_vec[18], _mm_mul_ps(i_vec[3], j_vec[8]));
            k_vec[19] = _mm_add_ps(k_vec[19], _mm_mul_ps(i_vec[3], j_vec[9]));

            k_vec[20] = _mm_add_ps(k_vec[20], _mm_mul_ps(i_vec[5], j_vec[0]));
            k_vec[21] = _mm_add_ps(k_vec[21], _mm_mul_ps(i_vec[5], j_vec[1]));
            k_vec[22] = _mm_add_ps(k_vec[22], _mm_mul_ps(i_vec[5], j_vec[2]));
            k_vec[23] = _mm_add_ps(k_vec[23], _mm_mul_ps(i_vec[5], j_vec[3]));
            k_vec[24] = _mm_add_ps(k_vec[24], _mm_mul_ps(i_vec[5], j_vec[4]));
            k_vec[25] = _mm_add_ps(k_vec[25], _mm_mul_ps(i_vec[5], j_vec[5]));
            k_vec[26] = _mm_add_ps(k_vec[26], _mm_mul_ps(i_vec[5], j_vec[6]));
            k_vec[27] = _mm_add_ps(k_vec[27], _mm_mul_ps(i_vec[5], j_vec[7]));
            k_vec[28] = _mm_add_ps(k_vec[28], _mm_mul_ps(i_vec[5], j_vec[8]));
            k_vec[29] = _mm_add_ps(k_vec[29], _mm_mul_ps(i_vec[5], j_vec[9]));

            k_vec[30] = _mm_add_ps(k_vec[30], _mm_mul_ps(i_vec[7], j_vec[0]));
            k_vec[31] = _mm_add_ps(k_vec[31], _mm_mul_ps(i_vec[7], j_vec[1]));
            k_vec[32] = _mm_add_ps(k_vec[32], _mm_mul_ps(i_vec[7], j_vec[2]));
            k_vec[33] = _mm_add_ps(k_vec[33], _mm_mul_ps(i_vec[7], j_vec[3]));
            k_vec[34] = _mm_add_ps(k_vec[34], _mm_mul_ps(i_vec[7], j_vec[4]));
            k_vec[35] = _mm_add_ps(k_vec[35], _mm_mul_ps(i_vec[7], j_vec[5]));
            k_vec[36] = _mm_add_ps(k_vec[36], _mm_mul_ps(i_vec[7], j_vec[6]));
            k_vec[37] = _mm_add_ps(k_vec[37], _mm_mul_ps(i_vec[7], j_vec[7]));
            k_vec[38] = _mm_add_ps(k_vec[38], _mm_mul_ps(i_vec[7], j_vec[8]));
            k_vec[39] = _mm_add_ps(k_vec[39], _mm_mul_ps(i_vec[7], j_vec[9]));

            k_vec[40] = _mm_add_ps(k_vec[40], _mm_mul_ps(i_vec[9], j_vec[0]));
            k_vec[41] = _mm_add_ps(k_vec[41], _mm_mul_ps(i_vec[9], j_vec[1]));
            k_vec[42] = _mm_add_ps(k_vec[42], _mm_mul_ps(i_vec[9], j_vec[2]));
            k_vec[43] = _mm_add_ps(k_vec[43], _mm_mul_ps(i_vec[9], j_vec[3]));
            k_vec[44] = _mm_add_ps(k_vec[44], _mm_mul_ps(i_vec[9], j_vec[4]));
            k_vec[45] = _mm_add_ps(k_vec[45], _mm_mul_ps(i_vec[9], j_vec[5]));
            k_vec[46] = _mm_add_ps(k_vec[46], _mm_mul_ps(i_vec[9], j_vec[6]));
            k_vec[47] = _mm_add_ps(k_vec[47], _mm_mul_ps(i_vec[9], j_vec[7]));
            k_vec[48] = _mm_add_ps(k_vec[48], _mm_mul_ps(i_vec[9], j_vec[8]));
            k_vec[49] = _mm_add_ps(k_vec[49], _mm_mul_ps(i_vec[9], j_vec[9]));

            for (int k = 2; k < n - n % 2; k += 2) {
                i_vec[0] = _mm_loadu_ps((A + i      + (k + 0) * m));
                i_vec[2] = _mm_loadu_ps((A + i +  4 + (k + 0) * m));
                i_vec[4] = _mm_loadu_ps((A + i +  8 + (k + 0) * m));
                i_vec[6] = _mm_loadu_ps((A + i + 12 + (k + 0) * m));
                i_vec[8] = _mm_loadu_ps((A + i + 16 + (k + 0) * m));

                j_vec[0] = _mm_set1_ps(A[j + (k + 0) * m + 0]);
                j_vec[1] = _mm_set1_ps(A[j + (k + 0) * m + 1]);
                j_vec[2] = _mm_set1_ps(A[j + (k + 0) * m + 2]);
                j_vec[3] = _mm_set1_ps(A[j + (k + 0) * m + 3]);
                j_vec[4] = _mm_set1_ps(A[j + (k + 0) * m + 4]);
                j_vec[5] = _mm_set1_ps(A[j + (k + 0) * m + 5]);
                j_vec[6] = _mm_set1_ps(A[j + (k + 0) * m + 6]);
                j_vec[7] = _mm_set1_ps(A[j + (k + 0) * m + 7]);
                j_vec[8] = _mm_set1_ps(A[j + (k + 0) * m + 8]);
                j_vec[9] = _mm_set1_ps(A[j + (k + 0) * m + 9]);

                k_vec[0]  = _mm_add_ps(k_vec[0],  _mm_mul_ps(i_vec[0], j_vec[0]));
                k_vec[1]  = _mm_add_ps(k_vec[1],  _mm_mul_ps(i_vec[0], j_vec[1]));
                k_vec[2]  = _mm_add_ps(k_vec[2],  _mm_mul_ps(i_vec[0], j_vec[2]));
                k_vec[3]  = _mm_add_ps(k_vec[3],  _mm_mul_ps(i_vec[0], j_vec[3]));
                k_vec[4]  = _mm_add_ps(k_vec[4],  _mm_mul_ps(i_vec[0], j_vec[4]));
                k_vec[5]  = _mm_add_ps(k_vec[5],  _mm_mul_ps(i_vec[0], j_vec[5]));
                k_vec[6]  = _mm_add_ps(k_vec[6],  _mm_mul_ps(i_vec[0], j_vec[6]));
                k_vec[7]  = _mm_add_ps(k_vec[7],  _mm_mul_ps(i_vec[0], j_vec[7]));
                k_vec[8]  = _mm_add_ps(k_vec[8],  _mm_mul_ps(i_vec[0], j_vec[8]));
                k_vec[9]  = _mm_add_ps(k_vec[9],  _mm_mul_ps(i_vec[0], j_vec[9]));

                k_vec[10] = _mm_add_ps(k_vec[10], _mm_mul_ps(i_vec[2], j_vec[0]));
                k_vec[11] = _mm_add_ps(k_vec[11], _mm_mul_ps(i_vec[2], j_vec[1]));
                k_vec[12] = _mm_add_ps(k_vec[12], _mm_mul_ps(i_vec[2], j_vec[2]));
                k_vec[13] = _mm_add_ps(k_vec[13], _mm_mul_ps(i_vec[2], j_vec[3]));
                k_vec[14] = _mm_add_ps(k_vec[14], _mm_mul_ps(i_vec[2], j_vec[4]));
                k_vec[15] = _mm_add_ps(k_vec[15], _mm_mul_ps(i_vec[2], j_vec[5]));
                k_vec[16] = _mm_add_ps(k_vec[16], _mm_mul_ps(i_vec[2], j_vec[6]));
                k_vec[17] = _mm_add_ps(k_vec[17], _mm_mul_ps(i_vec[2], j_vec[7]));
                k_vec[18] = _mm_add_ps(k_vec[18], _mm_mul_ps(i_vec[2], j_vec[8]));
                k_vec[19] = _mm_add_ps(k_vec[19], _mm_mul_ps(i_vec[2], j_vec[9]));

                k_vec[20] = _mm_add_ps(k_vec[20], _mm_mul_ps(i_vec[4], j_vec[0]));
                k_vec[21] = _mm_add_ps(k_vec[21], _mm_mul_ps(i_vec[4], j_vec[1]));
                k_vec[22] = _mm_add_ps(k_vec[22], _mm_mul_ps(i_vec[4], j_vec[2]));
                k_vec[23] = _mm_add_ps(k_vec[23], _mm_mul_ps(i_vec[4], j_vec[3]));
                k_vec[24] = _mm_add_ps(k_vec[24], _mm_mul_ps(i_vec[4], j_vec[4]));
                k_vec[25] = _mm_add_ps(k_vec[25], _mm_mul_ps(i_vec[4], j_vec[5]));
                k_vec[26] = _mm_add_ps(k_vec[26], _mm_mul_ps(i_vec[4], j_vec[6]));
                k_vec[27] = _mm_add_ps(k_vec[27], _mm_mul_ps(i_vec[4], j_vec[7]));
                k_vec[28] = _mm_add_ps(k_vec[28], _mm_mul_ps(i_vec[4], j_vec[8]));
                k_vec[29] = _mm_add_ps(k_vec[29], _mm_mul_ps(i_vec[4], j_vec[9]));

                k_vec[30] = _mm_add_ps(k_vec[30], _mm_mul_ps(i_vec[6], j_vec[0]));
                k_vec[31] = _mm_add_ps(k_vec[31], _mm_mul_ps(i_vec[6], j_vec[1]));
                k_vec[32] = _mm_add_ps(k_vec[32], _mm_mul_ps(i_vec[6], j_vec[2]));
                k_vec[33] = _mm_add_ps(k_vec[33], _mm_mul_ps(i_vec[6], j_vec[3]));
                k_vec[34] = _mm_add_ps(k_vec[34], _mm_mul_ps(i_vec[6], j_vec[4]));
                k_vec[35] = _mm_add_ps(k_vec[35], _mm_mul_ps(i_vec[6], j_vec[5]));
                k_vec[36] = _mm_add_ps(k_vec[36], _mm_mul_ps(i_vec[6], j_vec[6]));
                k_vec[37] = _mm_add_ps(k_vec[37], _mm_mul_ps(i_vec[6], j_vec[7]));
                k_vec[38] = _mm_add_ps(k_vec[38], _mm_mul_ps(i_vec[6], j_vec[8]));
                k_vec[39] = _mm_add_ps(k_vec[39], _mm_mul_ps(i_vec[6], j_vec[9]));

                k_vec[40] = _mm_add_ps(k_vec[40], _mm_mul_ps(i_vec[8], j_vec[0]));
                k_vec[41] = _mm_add_ps(k_vec[41], _mm_mul_ps(i_vec[8], j_vec[1]));
                k_vec[42] = _mm_add_ps(k_vec[42], _mm_mul_ps(i_vec[8], j_vec[2]));
                k_vec[43] = _mm_add_ps(k_vec[43], _mm_mul_ps(i_vec[8], j_vec[3]));
                k_vec[44] = _mm_add_ps(k_vec[44], _mm_mul_ps(i_vec[8], j_vec[4]));
                k_vec[45] = _mm_add_ps(k_vec[45], _mm_mul_ps(i_vec[8], j_vec[5]));
                k_vec[46] = _mm_add_ps(k_vec[46], _mm_mul_ps(i_vec[8], j_vec[6]));
                k_vec[47] = _mm_add_ps(k_vec[47], _mm_mul_ps(i_vec[8], j_vec[7]));
                k_vec[48] = _mm_add_ps(k_vec[48], _mm_mul_ps(i_vec[8], j_vec[8]));
                k_vec[49] = _mm_add_ps(k_vec[49], _mm_mul_ps(i_vec[8], j_vec[9]));

                i_vec[1] = _mm_loadu_ps((A + i      + (k + 1) * m));
                i_vec[3] = _mm_loadu_ps((A + i +  4 + (k + 1) * m));
                i_vec[5] = _mm_loadu_ps((A + i +  8 + (k + 1) * m));                
                i_vec[7] = _mm_loadu_ps((A + i + 12 + (k + 1) * m));
                i_vec[9] = _mm_loadu_ps((A + i + 16 + (k + 1) * m));
		
		j_vec[0] = _mm_set1_ps(A[j + (k + 1) * m + 0]);
                j_vec[1] = _mm_set1_ps(A[j + (k + 1) * m + 1]);
                j_vec[2] = _mm_set1_ps(A[j + (k + 1) * m + 2]);
                j_vec[3] = _mm_set1_ps(A[j + (k + 1) * m + 3]);
                j_vec[4] = _mm_set1_ps(A[j + (k + 1) * m + 4]);
                j_vec[5] = _mm_set1_ps(A[j + (k + 1) * m + 5]);
                j_vec[6] = _mm_set1_ps(A[j + (k + 1) * m + 6]);
                j_vec[7] = _mm_set1_ps(A[j + (k + 1) * m + 7]);
                j_vec[8] = _mm_set1_ps(A[j + (k + 1) * m + 8]);
                j_vec[9] = _mm_set1_ps(A[j + (k + 1) * m + 9]);
                
                k_vec[0]  = _mm_add_ps(k_vec[0],  _mm_mul_ps(i_vec[1], j_vec[0]));
                k_vec[1]  = _mm_add_ps(k_vec[1],  _mm_mul_ps(i_vec[1], j_vec[1]));
                k_vec[2]  = _mm_add_ps(k_vec[2],  _mm_mul_ps(i_vec[1], j_vec[2]));
                k_vec[3]  = _mm_add_ps(k_vec[3],  _mm_mul_ps(i_vec[1], j_vec[3]));
                k_vec[4]  = _mm_add_ps(k_vec[4],  _mm_mul_ps(i_vec[1], j_vec[4]));
                k_vec[5]  = _mm_add_ps(k_vec[5],  _mm_mul_ps(i_vec[1], j_vec[5]));
                k_vec[6]  = _mm_add_ps(k_vec[6],  _mm_mul_ps(i_vec[1], j_vec[6]));
                k_vec[7]  = _mm_add_ps(k_vec[7],  _mm_mul_ps(i_vec[1], j_vec[7]));
                k_vec[8]  = _mm_add_ps(k_vec[8],  _mm_mul_ps(i_vec[1], j_vec[8]));
                k_vec[9]  = _mm_add_ps(k_vec[9],  _mm_mul_ps(i_vec[1], j_vec[9]));

                k_vec[10] = _mm_add_ps(k_vec[10], _mm_mul_ps(i_vec[3], j_vec[0]));
                k_vec[11] = _mm_add_ps(k_vec[11], _mm_mul_ps(i_vec[3], j_vec[1]));
                k_vec[12] = _mm_add_ps(k_vec[12], _mm_mul_ps(i_vec[3], j_vec[2]));
                k_vec[13] = _mm_add_ps(k_vec[13], _mm_mul_ps(i_vec[3], j_vec[3]));
                k_vec[14] = _mm_add_ps(k_vec[14], _mm_mul_ps(i_vec[3], j_vec[4]));
                k_vec[15] = _mm_add_ps(k_vec[15], _mm_mul_ps(i_vec[3], j_vec[5]));
                k_vec[16] = _mm_add_ps(k_vec[16], _mm_mul_ps(i_vec[3], j_vec[6]));
                k_vec[17] = _mm_add_ps(k_vec[17], _mm_mul_ps(i_vec[3], j_vec[7]));
                k_vec[18] = _mm_add_ps(k_vec[18], _mm_mul_ps(i_vec[3], j_vec[8]));
                k_vec[19] = _mm_add_ps(k_vec[19], _mm_mul_ps(i_vec[3], j_vec[9]));

                k_vec[20] = _mm_add_ps(k_vec[20], _mm_mul_ps(i_vec[5], j_vec[0]));
                k_vec[21] = _mm_add_ps(k_vec[21], _mm_mul_ps(i_vec[5], j_vec[1]));
                k_vec[22] = _mm_add_ps(k_vec[22], _mm_mul_ps(i_vec[5], j_vec[2]));
                k_vec[23] = _mm_add_ps(k_vec[23], _mm_mul_ps(i_vec[5], j_vec[3]));
                k_vec[24] = _mm_add_ps(k_vec[24], _mm_mul_ps(i_vec[5], j_vec[4]));
                k_vec[25] = _mm_add_ps(k_vec[25], _mm_mul_ps(i_vec[5], j_vec[5]));
                k_vec[26] = _mm_add_ps(k_vec[26], _mm_mul_ps(i_vec[5], j_vec[6]));
                k_vec[27] = _mm_add_ps(k_vec[27], _mm_mul_ps(i_vec[5], j_vec[7]));
                k_vec[28] = _mm_add_ps(k_vec[28], _mm_mul_ps(i_vec[5], j_vec[8]));
                k_vec[29] = _mm_add_ps(k_vec[29], _mm_mul_ps(i_vec[5], j_vec[9]));

                k_vec[30] = _mm_add_ps(k_vec[30], _mm_mul_ps(i_vec[7], j_vec[0]));
                k_vec[31] = _mm_add_ps(k_vec[31], _mm_mul_ps(i_vec[7], j_vec[1]));
                k_vec[32] = _mm_add_ps(k_vec[32], _mm_mul_ps(i_vec[7], j_vec[2]));
                k_vec[33] = _mm_add_ps(k_vec[33], _mm_mul_ps(i_vec[7], j_vec[3]));
                k_vec[34] = _mm_add_ps(k_vec[34], _mm_mul_ps(i_vec[7], j_vec[4]));
                k_vec[35] = _mm_add_ps(k_vec[35], _mm_mul_ps(i_vec[7], j_vec[5]));
                k_vec[36] = _mm_add_ps(k_vec[36], _mm_mul_ps(i_vec[7], j_vec[6]));
                k_vec[37] = _mm_add_ps(k_vec[37], _mm_mul_ps(i_vec[7], j_vec[7]));
                k_vec[38] = _mm_add_ps(k_vec[38], _mm_mul_ps(i_vec[7], j_vec[8]));
                k_vec[39] = _mm_add_ps(k_vec[39], _mm_mul_ps(i_vec[7], j_vec[9]));

                k_vec[40] = _mm_add_ps(k_vec[40], _mm_mul_ps(i_vec[9], j_vec[0]));
                k_vec[41] = _mm_add_ps(k_vec[41], _mm_mul_ps(i_vec[9], j_vec[1]));
                k_vec[42] = _mm_add_ps(k_vec[42], _mm_mul_ps(i_vec[9], j_vec[2]));
                k_vec[43] = _mm_add_ps(k_vec[43], _mm_mul_ps(i_vec[9], j_vec[3]));
                k_vec[44] = _mm_add_ps(k_vec[44], _mm_mul_ps(i_vec[9], j_vec[4]));
                k_vec[45] = _mm_add_ps(k_vec[45], _mm_mul_ps(i_vec[9], j_vec[5]));
                k_vec[46] = _mm_add_ps(k_vec[46], _mm_mul_ps(i_vec[9], j_vec[6]));
                k_vec[47] = _mm_add_ps(k_vec[47], _mm_mul_ps(i_vec[9], j_vec[7]));
                k_vec[48] = _mm_add_ps(k_vec[48], _mm_mul_ps(i_vec[9], j_vec[8]));
                k_vec[49] = _mm_add_ps(k_vec[49], _mm_mul_ps(i_vec[9], j_vec[9]));

            }

            for (int k = n - n % 2; k < n; ++k) {
                i_vec[0] = _mm_loadu_ps((A + i +      (k + 0) * m));
                i_vec[2] = _mm_loadu_ps((A + i +  4 + (k + 0) * m));
		i_vec[4] = _mm_loadu_ps((A + i +  8 + (k + 0) * m));
                i_vec[6] = _mm_loadu_ps((A + i + 12 + (k + 0) * m));
                i_vec[8] = _mm_loadu_ps((A + i + 16 + (k + 0) * m));

                j_vec[0] = _mm_set1_ps(A[j + (k + 0) * m + 0]);
                j_vec[1] = _mm_set1_ps(A[j + (k + 0) * m + 1]);
                j_vec[2] = _mm_set1_ps(A[j + (k + 0) * m + 2]);
                j_vec[3] = _mm_set1_ps(A[j + (k + 0) * m + 3]);
                j_vec[4] = _mm_set1_ps(A[j + (k + 0) * m + 4]);
                j_vec[5] = _mm_set1_ps(A[j + (k + 0) * m + 5]);
                j_vec[6] = _mm_set1_ps(A[j + (k + 0) * m + 6]);
                j_vec[7] = _mm_set1_ps(A[j + (k + 0) * m + 7]);
                j_vec[8] = _mm_set1_ps(A[j + (k + 0) * m + 8]);
                j_vec[9] = _mm_set1_ps(A[j + (k + 0) * m + 9]);

                k_vec[0]  = _mm_add_ps(k_vec[0],  _mm_mul_ps(i_vec[0], j_vec[0]));
                k_vec[1]  = _mm_add_ps(k_vec[1],  _mm_mul_ps(i_vec[0], j_vec[1]));
                k_vec[2]  = _mm_add_ps(k_vec[2],  _mm_mul_ps(i_vec[0], j_vec[2]));
                k_vec[3]  = _mm_add_ps(k_vec[3],  _mm_mul_ps(i_vec[0], j_vec[3]));
                k_vec[4]  = _mm_add_ps(k_vec[4],  _mm_mul_ps(i_vec[0], j_vec[4]));
                k_vec[5]  = _mm_add_ps(k_vec[5],  _mm_mul_ps(i_vec[0], j_vec[5]));
                k_vec[6]  = _mm_add_ps(k_vec[6],  _mm_mul_ps(i_vec[0], j_vec[6]));
                k_vec[7]  = _mm_add_ps(k_vec[7],  _mm_mul_ps(i_vec[0], j_vec[7]));
                k_vec[8]  = _mm_add_ps(k_vec[8],  _mm_mul_ps(i_vec[0], j_vec[8]));
                k_vec[9]  = _mm_add_ps(k_vec[9],  _mm_mul_ps(i_vec[0], j_vec[9]));

                k_vec[10] = _mm_add_ps(k_vec[10], _mm_mul_ps(i_vec[2], j_vec[0]));
                k_vec[11] = _mm_add_ps(k_vec[11], _mm_mul_ps(i_vec[2], j_vec[1]));
                k_vec[12] = _mm_add_ps(k_vec[12], _mm_mul_ps(i_vec[2], j_vec[2]));
                k_vec[13] = _mm_add_ps(k_vec[13], _mm_mul_ps(i_vec[2], j_vec[3]));
                k_vec[14] = _mm_add_ps(k_vec[14], _mm_mul_ps(i_vec[2], j_vec[4]));
                k_vec[15] = _mm_add_ps(k_vec[15], _mm_mul_ps(i_vec[2], j_vec[5]));
                k_vec[16] = _mm_add_ps(k_vec[16], _mm_mul_ps(i_vec[2], j_vec[6]));
                k_vec[17] = _mm_add_ps(k_vec[17], _mm_mul_ps(i_vec[2], j_vec[7]));
                k_vec[18] = _mm_add_ps(k_vec[18], _mm_mul_ps(i_vec[2], j_vec[8]));
                k_vec[19] = _mm_add_ps(k_vec[19], _mm_mul_ps(i_vec[2], j_vec[9]));

		k_vec[20] = _mm_add_ps(k_vec[20], _mm_mul_ps(i_vec[4], j_vec[0]));
                k_vec[21] = _mm_add_ps(k_vec[21], _mm_mul_ps(i_vec[4], j_vec[1]));
                k_vec[22] = _mm_add_ps(k_vec[22], _mm_mul_ps(i_vec[4], j_vec[2]));
                k_vec[23] = _mm_add_ps(k_vec[23], _mm_mul_ps(i_vec[4], j_vec[3]));
                k_vec[24] = _mm_add_ps(k_vec[24], _mm_mul_ps(i_vec[4], j_vec[4]));
                k_vec[25] = _mm_add_ps(k_vec[25], _mm_mul_ps(i_vec[4], j_vec[5]));
                k_vec[26] = _mm_add_ps(k_vec[26], _mm_mul_ps(i_vec[4], j_vec[6]));
                k_vec[27] = _mm_add_ps(k_vec[27], _mm_mul_ps(i_vec[4], j_vec[7]));
                k_vec[28] = _mm_add_ps(k_vec[28], _mm_mul_ps(i_vec[4], j_vec[8]));
                k_vec[29] = _mm_add_ps(k_vec[29], _mm_mul_ps(i_vec[4], j_vec[9]));

                k_vec[30] = _mm_add_ps(k_vec[30], _mm_mul_ps(i_vec[6], j_vec[0]));
                k_vec[31] = _mm_add_ps(k_vec[31], _mm_mul_ps(i_vec[6], j_vec[1]));
                k_vec[32] = _mm_add_ps(k_vec[32], _mm_mul_ps(i_vec[6], j_vec[2]));
                k_vec[33] = _mm_add_ps(k_vec[33], _mm_mul_ps(i_vec[6], j_vec[3]));
                k_vec[34] = _mm_add_ps(k_vec[34], _mm_mul_ps(i_vec[6], j_vec[4]));
                k_vec[35] = _mm_add_ps(k_vec[35], _mm_mul_ps(i_vec[6], j_vec[5]));
                k_vec[36] = _mm_add_ps(k_vec[36], _mm_mul_ps(i_vec[6], j_vec[6]));
                k_vec[37] = _mm_add_ps(k_vec[37], _mm_mul_ps(i_vec[6], j_vec[7]));
                k_vec[38] = _mm_add_ps(k_vec[38], _mm_mul_ps(i_vec[6], j_vec[8]));
                k_vec[39] = _mm_add_ps(k_vec[39], _mm_mul_ps(i_vec[6], j_vec[9]));

                k_vec[40] = _mm_add_ps(k_vec[40], _mm_mul_ps(i_vec[8], j_vec[0]));
                k_vec[41] = _mm_add_ps(k_vec[41], _mm_mul_ps(i_vec[8], j_vec[1]));
                k_vec[42] = _mm_add_ps(k_vec[42], _mm_mul_ps(i_vec[8], j_vec[2]));
                k_vec[43] = _mm_add_ps(k_vec[43], _mm_mul_ps(i_vec[8], j_vec[3]));
                k_vec[44] = _mm_add_ps(k_vec[44], _mm_mul_ps(i_vec[8], j_vec[4]));
                k_vec[45] = _mm_add_ps(k_vec[45], _mm_mul_ps(i_vec[8], j_vec[5]));
                k_vec[46] = _mm_add_ps(k_vec[46], _mm_mul_ps(i_vec[8], j_vec[6]));
                k_vec[47] = _mm_add_ps(k_vec[47], _mm_mul_ps(i_vec[8], j_vec[7]));
                k_vec[48] = _mm_add_ps(k_vec[48], _mm_mul_ps(i_vec[8], j_vec[8]));
                k_vec[49] = _mm_add_ps(k_vec[49], _mm_mul_ps(i_vec[8], j_vec[9]));
            }

            _mm_storeu_ps((C + i +      (j + 0) * m), k_vec[0]);
            _mm_storeu_ps((C + i +  4 + (j + 0) * m), k_vec[10]);
            _mm_storeu_ps((C + i +  8 + (j + 0) * m), k_vec[20]);
            _mm_storeu_ps((C + i + 12 + (j + 0) * m), k_vec[30]);
            _mm_storeu_ps((C + i + 16 + (j + 0) * m), k_vec[40]);

            _mm_storeu_ps((C + i +      (j + 1) * m), k_vec[1]);
            _mm_storeu_ps((C + i +  4 + (j + 1) * m), k_vec[11]);
            _mm_storeu_ps((C + i +  8 + (j + 1) * m), k_vec[21]);
            _mm_storeu_ps((C + i + 12 + (j + 1) * m), k_vec[31]);
            _mm_storeu_ps((C + i + 16 + (j + 1) * m), k_vec[41]);

            _mm_storeu_ps((C + i +      (j + 2) * m), k_vec[2]);
            _mm_storeu_ps((C + i +  4 + (j + 2) * m), k_vec[12]);
            _mm_storeu_ps((C + i +  8 + (j + 2) * m), k_vec[22]);
            _mm_storeu_ps((C + i + 12 + (j + 2) * m), k_vec[32]);
            _mm_storeu_ps((C + i + 16 + (j + 2) * m), k_vec[42]);

            _mm_storeu_ps((C + i +      (j + 3) * m), k_vec[3]);
            _mm_storeu_ps((C + i +  4 + (j + 3) * m), k_vec[13]);
            _mm_storeu_ps((C + i +  8 + (j + 3) * m), k_vec[23]);
            _mm_storeu_ps((C + i + 12 + (j + 3) * m), k_vec[33]);
            _mm_storeu_ps((C + i + 16 + (j + 3) * m), k_vec[43]);

            _mm_storeu_ps((C + i +      (j + 4) * m), k_vec[4]);
            _mm_storeu_ps((C + i +  4 + (j + 4) * m), k_vec[14]);
            _mm_storeu_ps((C + i +  8 + (j + 4) * m), k_vec[24]);
            _mm_storeu_ps((C + i + 12 + (j + 4) * m), k_vec[34]);
            _mm_storeu_ps((C + i + 16 + (j + 4) * m), k_vec[44]);

            _mm_storeu_ps((C + i +      (j + 5) * m), k_vec[5]);
            _mm_storeu_ps((C + i +  4 + (j + 5) * m), k_vec[15]);
            _mm_storeu_ps((C + i +  8 + (j + 5) * m), k_vec[25]);
            _mm_storeu_ps((C + i + 12 + (j + 5) * m), k_vec[35]);
            _mm_storeu_ps((C + i + 16 + (j + 5) * m), k_vec[45]);

            _mm_storeu_ps((C + i +      (j + 6) * m), k_vec[6]);
            _mm_storeu_ps((C + i +  4 + (j + 6) * m), k_vec[16]);
            _mm_storeu_ps((C + i +  8 + (j + 6) * m), k_vec[26]);
            _mm_storeu_ps((C + i + 12 + (j + 6) * m), k_vec[36]);
            _mm_storeu_ps((C + i + 16 + (j + 6) * m), k_vec[46]);

            _mm_storeu_ps((C + i +      (j + 7) * m), k_vec[7]);
            _mm_storeu_ps((C + i +  4 + (j + 7) * m), k_vec[17]);
            _mm_storeu_ps((C + i +  8 + (j + 7) * m), k_vec[27]);
            _mm_storeu_ps((C + i + 12 + (j + 7) * m), k_vec[37]);
            _mm_storeu_ps((C + i + 16 + (j + 7) * m), k_vec[47]);

            _mm_storeu_ps((C + i +      (j + 8) * m), k_vec[8]);
            _mm_storeu_ps((C + i +  4 + (j + 8) * m), k_vec[18]);
            _mm_storeu_ps((C + i +  8 + (j + 8) * m), k_vec[28]);
            _mm_storeu_ps((C + i + 12 + (j + 8) * m), k_vec[38]);
            _mm_storeu_ps((C + i + 16 + (j + 8) * m), k_vec[48]);

            _mm_storeu_ps((C + i +      (j + 9) * m), k_vec[9]);
            _mm_storeu_ps((C + i +  4 + (j + 9) * m), k_vec[19]);
            _mm_storeu_ps((C + i +  8 + (j + 9) * m), k_vec[29]);
            _mm_storeu_ps((C + i + 12 + (j + 9) * m), k_vec[39]);
            _mm_storeu_ps((C + i + 16 + (j + 9) * m), k_vec[49]);
        }
        
	#pragma omp for private (i_vec, j_vec, k_vec) nowait
        for (int i = m - m % 20; i < m - m % 4; i += 4) {
            i_vec[0] = _mm_loadu_ps((A + i + (0 + 0) * m));
            i_vec[1] = _mm_loadu_ps((A + i + (0 + 1) * m));

            j_vec[0] = _mm_set1_ps(A[j + (0 + 0) * m + 0]);
            j_vec[1] = _mm_set1_ps(A[j + (0 + 0) * m + 1]);
            j_vec[2] = _mm_set1_ps(A[j + (0 + 0) * m + 2]);
            j_vec[3] = _mm_set1_ps(A[j + (0 + 0) * m + 3]);
            j_vec[4] = _mm_set1_ps(A[j + (0 + 0) * m + 4]);
            j_vec[5] = _mm_set1_ps(A[j + (0 + 0) * m + 5]);
            j_vec[6] = _mm_set1_ps(A[j + (0 + 0) * m + 6]);
            j_vec[7] = _mm_set1_ps(A[j + (0 + 0) * m + 7]);
            j_vec[8] = _mm_set1_ps(A[j + (0 + 0) * m + 8]);
            j_vec[9] = _mm_set1_ps(A[j + (0 + 0) * m + 9]);
            
            k_vec[0] = _mm_mul_ps(i_vec[0], j_vec[0]);
            k_vec[1] = _mm_mul_ps(i_vec[0], j_vec[1]);
            k_vec[2] = _mm_mul_ps(i_vec[0], j_vec[2]);
            k_vec[3] = _mm_mul_ps(i_vec[0], j_vec[3]);
            k_vec[4] = _mm_mul_ps(i_vec[0], j_vec[4]);
            k_vec[5] = _mm_mul_ps(i_vec[0], j_vec[5]);
            k_vec[6] = _mm_mul_ps(i_vec[0], j_vec[6]);
            k_vec[7] = _mm_mul_ps(i_vec[0], j_vec[7]);
            k_vec[8] = _mm_mul_ps(i_vec[0], j_vec[8]);
            k_vec[9] = _mm_mul_ps(i_vec[0], j_vec[9]);
            
            j_vec[0] = _mm_set1_ps(A[j + (0 + 1) * m + 0]);
            j_vec[1] = _mm_set1_ps(A[j + (0 + 1) * m + 1]);
            j_vec[2] = _mm_set1_ps(A[j + (0 + 1) * m + 2]);
            j_vec[3] = _mm_set1_ps(A[j + (0 + 1) * m + 3]);
            j_vec[4] = _mm_set1_ps(A[j + (0 + 1) * m + 4]);
            j_vec[5] = _mm_set1_ps(A[j + (0 + 1) * m + 5]);
            j_vec[6] = _mm_set1_ps(A[j + (0 + 1) * m + 6]);
            j_vec[7] = _mm_set1_ps(A[j + (0 + 1) * m + 7]);
            j_vec[8] = _mm_set1_ps(A[j + (0 + 1) * m + 8]);
            j_vec[9] = _mm_set1_ps(A[j + (0 + 1) * m + 9]);

            k_vec[0] = _mm_add_ps(k_vec[0], _mm_mul_ps(i_vec[1], j_vec[0]));
            k_vec[1] = _mm_add_ps(k_vec[1], _mm_mul_ps(i_vec[1], j_vec[1]));
            k_vec[2] = _mm_add_ps(k_vec[2], _mm_mul_ps(i_vec[1], j_vec[2]));
            k_vec[3] = _mm_add_ps(k_vec[3], _mm_mul_ps(i_vec[1], j_vec[3]));
            k_vec[4] = _mm_add_ps(k_vec[4], _mm_mul_ps(i_vec[1], j_vec[4]));
            k_vec[5] = _mm_add_ps(k_vec[5], _mm_mul_ps(i_vec[1], j_vec[5]));
            k_vec[6] = _mm_add_ps(k_vec[6], _mm_mul_ps(i_vec[1], j_vec[6]));
            k_vec[7] = _mm_add_ps(k_vec[7], _mm_mul_ps(i_vec[1], j_vec[7]));
            k_vec[8] = _mm_add_ps(k_vec[8], _mm_mul_ps(i_vec[1], j_vec[8]));
            k_vec[9] = _mm_add_ps(k_vec[9], _mm_mul_ps(i_vec[1], j_vec[9]));

            for (int k = 2; k < n - n % 2; k += 2) {
                i_vec[0] = _mm_loadu_ps((A + i + (k + 0) * m));
                i_vec[1] = _mm_loadu_ps((A + i + (k + 1) * m));

                j_vec[0] = _mm_set1_ps(A[j + (k + 0) * m + 0]);
                j_vec[1] = _mm_set1_ps(A[j + (k + 0) * m + 1]);
                j_vec[2] = _mm_set1_ps(A[j + (k + 0) * m + 2]);
                j_vec[3] = _mm_set1_ps(A[j + (k + 0) * m + 3]);
                j_vec[4] = _mm_set1_ps(A[j + (k + 0) * m + 4]);
                j_vec[5] = _mm_set1_ps(A[j + (k + 0) * m + 5]);
                j_vec[6] = _mm_set1_ps(A[j + (k + 0) * m + 6]);
                j_vec[7] = _mm_set1_ps(A[j + (k + 0) * m + 7]);
                j_vec[8] = _mm_set1_ps(A[j + (k + 0) * m + 8]);
                j_vec[9] = _mm_set1_ps(A[j + (k + 0) * m + 9]);

                k_vec[0] = _mm_add_ps(k_vec[0], _mm_mul_ps(i_vec[0], j_vec[0]));
                k_vec[1] = _mm_add_ps(k_vec[1], _mm_mul_ps(i_vec[0], j_vec[1]));
                k_vec[2] = _mm_add_ps(k_vec[2], _mm_mul_ps(i_vec[0], j_vec[2]));
                k_vec[3] = _mm_add_ps(k_vec[3], _mm_mul_ps(i_vec[0], j_vec[3]));
                k_vec[4] = _mm_add_ps(k_vec[4], _mm_mul_ps(i_vec[0], j_vec[4]));
                k_vec[5] = _mm_add_ps(k_vec[5], _mm_mul_ps(i_vec[0], j_vec[5]));
                k_vec[6] = _mm_add_ps(k_vec[6], _mm_mul_ps(i_vec[0], j_vec[6]));
                k_vec[7] = _mm_add_ps(k_vec[7], _mm_mul_ps(i_vec[0], j_vec[7]));
                k_vec[8] = _mm_add_ps(k_vec[8], _mm_mul_ps(i_vec[0], j_vec[8]));
                k_vec[9] = _mm_add_ps(k_vec[9], _mm_mul_ps(i_vec[0], j_vec[9]));
                

                j_vec[0] = _mm_set1_ps(A[j + (k + 1) * m + 0]);
                j_vec[1] = _mm_set1_ps(A[j + (k + 1) * m + 1]);
                j_vec[2] = _mm_set1_ps(A[j + (k + 1) * m + 2]);
                j_vec[3] = _mm_set1_ps(A[j + (k + 1) * m + 3]);
                j_vec[4] = _mm_set1_ps(A[j + (k + 1) * m + 4]);
                j_vec[5] = _mm_set1_ps(A[j + (k + 1) * m + 5]);
                j_vec[6] = _mm_set1_ps(A[j + (k + 1) * m + 6]);
                j_vec[7] = _mm_set1_ps(A[j + (k + 1) * m + 7]);
                j_vec[8] = _mm_set1_ps(A[j + (k + 1) * m + 8]);
                j_vec[9] = _mm_set1_ps(A[j + (k + 1) * m + 9]);

                k_vec[0] = _mm_add_ps(k_vec[0], _mm_mul_ps(i_vec[1], j_vec[0]));
                k_vec[1] = _mm_add_ps(k_vec[1], _mm_mul_ps(i_vec[1], j_vec[1]));
                k_vec[2] = _mm_add_ps(k_vec[2], _mm_mul_ps(i_vec[1], j_vec[2]));
                k_vec[3] = _mm_add_ps(k_vec[3], _mm_mul_ps(i_vec[1], j_vec[3]));
                k_vec[4] = _mm_add_ps(k_vec[4], _mm_mul_ps(i_vec[1], j_vec[4]));
                k_vec[5] = _mm_add_ps(k_vec[5], _mm_mul_ps(i_vec[1], j_vec[5]));
                k_vec[6] = _mm_add_ps(k_vec[6], _mm_mul_ps(i_vec[1], j_vec[6]));
                k_vec[7] = _mm_add_ps(k_vec[7], _mm_mul_ps(i_vec[1], j_vec[7]));
                k_vec[8] = _mm_add_ps(k_vec[8], _mm_mul_ps(i_vec[1], j_vec[8]));
                k_vec[9] = _mm_add_ps(k_vec[9], _mm_mul_ps(i_vec[1], j_vec[9]));
            }

            for (int k = n - n % 2; k < n; k++) {
                i_vec[0] = _mm_loadu_ps((A + i + (k + 0) * m));

                j_vec[0] = _mm_set1_ps(A[j + (k + 0) * m + 0]);
                j_vec[1] = _mm_set1_ps(A[j + (k + 0) * m + 1]);
                j_vec[2] = _mm_set1_ps(A[j + (k + 0) * m + 2]);
                j_vec[3] = _mm_set1_ps(A[j + (k + 0) * m + 3]);
                j_vec[4] = _mm_set1_ps(A[j + (k + 0) * m + 4]);
                j_vec[5] = _mm_set1_ps(A[j + (k + 0) * m + 5]);
                j_vec[6] = _mm_set1_ps(A[j + (k + 0) * m + 6]);
                j_vec[7] = _mm_set1_ps(A[j + (k + 0) * m + 7]);
                j_vec[8] = _mm_set1_ps(A[j + (k + 0) * m + 8]);
                j_vec[9] = _mm_set1_ps(A[j + (k + 0) * m + 9]);

                k_vec[0] = _mm_add_ps(k_vec[0], _mm_mul_ps(i_vec[0], j_vec[0]));
                k_vec[1] = _mm_add_ps(k_vec[1], _mm_mul_ps(i_vec[0], j_vec[1]));
                k_vec[2] = _mm_add_ps(k_vec[2], _mm_mul_ps(i_vec[0], j_vec[2]));
                k_vec[3] = _mm_add_ps(k_vec[3], _mm_mul_ps(i_vec[0], j_vec[3]));
                k_vec[4] = _mm_add_ps(k_vec[4], _mm_mul_ps(i_vec[0], j_vec[4]));
                k_vec[5] = _mm_add_ps(k_vec[5], _mm_mul_ps(i_vec[0], j_vec[5]));
                k_vec[6] = _mm_add_ps(k_vec[6], _mm_mul_ps(i_vec[0], j_vec[6]));
                k_vec[7] = _mm_add_ps(k_vec[7], _mm_mul_ps(i_vec[0], j_vec[7]));
                k_vec[8] = _mm_add_ps(k_vec[8], _mm_mul_ps(i_vec[0], j_vec[8]));
                k_vec[9] = _mm_add_ps(k_vec[9], _mm_mul_ps(i_vec[0], j_vec[9]));
            }

            _mm_storeu_ps((C + i + (j + 0) * m), k_vec[0]);
            _mm_storeu_ps((C + i + (j + 1) * m), k_vec[1]);
            _mm_storeu_ps((C + i + (j + 2) * m), k_vec[2]);
            _mm_storeu_ps((C + i + (j + 3) * m), k_vec[3]);
            _mm_storeu_ps((C + i + (j + 4) * m), k_vec[4]);
            _mm_storeu_ps((C + i + (j + 5) * m), k_vec[5]);
            _mm_storeu_ps((C + i + (j + 6) * m), k_vec[6]);
            _mm_storeu_ps((C + i + (j + 7) * m), k_vec[7]);
            _mm_storeu_ps((C + i + (j + 8) * m), k_vec[8]);
            _mm_storeu_ps((C + i + (j + 9) * m), k_vec[9]);

        }
        
	#pragma omp for nowait
        for (int i = m - m % 4; i < m; i++) {
            for (int k = 0; k < n; k += 1) {
                C[i + (j + 0) * m] += A[i + (k + 0) * m] * A[(j + 0) + (k + 0) * m];
                C[i + (j + 1) * m] += A[i + (k + 0) * m] * A[(j + 1) + (k + 0) * m];
                C[i + (j + 2) * m] += A[i + (k + 0) * m] * A[(j + 2) + (k + 0) * m];
                C[i + (j + 3) * m] += A[i + (k + 0) * m] * A[(j + 3) + (k + 0) * m];
                C[i + (j + 4) * m] += A[i + (k + 0) * m] * A[(j + 4) + (k + 0) * m];
                C[i + (j + 5) * m] += A[i + (k + 0) * m] * A[(j + 5) + (k + 0) * m];
                C[i + (j + 6) * m] += A[i + (k + 0) * m] * A[(j + 6) + (k + 0) * m];
                C[i + (j + 7) * m] += A[i + (k + 0) * m] * A[(j + 7) + (k + 0) * m];
                C[i + (j + 8) * m] += A[i + (k + 0) * m] * A[(j + 8) + (k + 0) * m];
                C[i + (j + 9) * m] += A[i + (k + 0) * m] * A[(j + 9) + (k + 0) * m];
            }
        }
    }
}

    //Tail from unrolling j
#pragma omp parallel
{
    for (int j = m - m % 10; j < m; j++) {
#pragma omp for nowait private (i_vec, j_vec, k_vec)
        for (int i = 0; i < m - m % 20; i += 20) {
            i_vec[0] = _mm_loadu_ps((A + i      + 0 * m));
            i_vec[2] = _mm_loadu_ps((A + i +  4 + 0 * m));
            i_vec[4] = _mm_loadu_ps((A + i +  8 + 0 * m));
            i_vec[6] = _mm_loadu_ps((A + i + 12 + 0 * m));
            i_vec[8] = _mm_loadu_ps((A + i + 16 + 0 * m));

            j_vec[0] = _mm_set1_ps(A[j + 0 * m + 0]);
            
            k_vec[0]  = _mm_mul_ps(i_vec[0], j_vec[0]);

            k_vec[1] = _mm_mul_ps(i_vec[2], j_vec[0]);

            k_vec[2] = _mm_mul_ps(i_vec[4], j_vec[0]);

            k_vec[3] = _mm_mul_ps(i_vec[6], j_vec[0]);

            k_vec[4] = _mm_mul_ps(i_vec[8], j_vec[0]);
            
            i_vec[1] = _mm_loadu_ps((A + i      + (0 + 1) * m));
            i_vec[3] = _mm_loadu_ps((A + i +  4 + (0 + 1) * m));
            i_vec[5] = _mm_loadu_ps((A + i +  8 + (0 + 1) * m));                
            i_vec[7] = _mm_loadu_ps((A + i + 12 + (0 + 1) * m));
            i_vec[9] = _mm_loadu_ps((A + i + 16 + (0 + 1) * m));

            j_vec[0] = _mm_set1_ps(A[j + (0 + 1) * m + 0]);

            k_vec[0]  = _mm_add_ps(k_vec[0],  _mm_mul_ps(i_vec[1], j_vec[0]));

            k_vec[1] = _mm_add_ps(k_vec[1], _mm_mul_ps(i_vec[3], j_vec[0]));

            k_vec[2] = _mm_add_ps(k_vec[2], _mm_mul_ps(i_vec[5], j_vec[0]));

            k_vec[3] = _mm_add_ps(k_vec[3], _mm_mul_ps(i_vec[7], j_vec[0]));

            k_vec[4] = _mm_add_ps(k_vec[4], _mm_mul_ps(i_vec[9], j_vec[0]));

            for (int k = 2; k < n - n % 2; k += 2) {
                i_vec[0] = _mm_loadu_ps((A + i      + (k + 0) * m));
                i_vec[2] = _mm_loadu_ps((A + i +  4 + (k + 0) * m));
                i_vec[4] = _mm_loadu_ps((A + i +  8 + (k + 0) * m));
                i_vec[6] = _mm_loadu_ps((A + i + 12 + (k + 0) * m));
                i_vec[8] = _mm_loadu_ps((A + i + 16 + (k + 0) * m));

                j_vec[0] = _mm_set1_ps(A[j + (k + 0) * m + 0]);

                k_vec[0]  = _mm_add_ps(k_vec[0],  _mm_mul_ps(i_vec[0], j_vec[0]));

                k_vec[1] = _mm_add_ps(k_vec[1], _mm_mul_ps(i_vec[2], j_vec[0]));

                k_vec[2] = _mm_add_ps(k_vec[2], _mm_mul_ps(i_vec[4], j_vec[0]));

                k_vec[3] = _mm_add_ps(k_vec[3], _mm_mul_ps(i_vec[6], j_vec[0]));

                k_vec[4] = _mm_add_ps(k_vec[4], _mm_mul_ps(i_vec[8], j_vec[0]));

                i_vec[1] = _mm_loadu_ps((A + i      + (k + 1) * m));
                i_vec[3] = _mm_loadu_ps((A + i +  4 + (k + 1) * m));
                i_vec[5] = _mm_loadu_ps((A + i +  8 + (k + 1) * m));                
                i_vec[7] = _mm_loadu_ps((A + i + 12 + (k + 1) * m));
                i_vec[9] = _mm_loadu_ps((A + i + 16 + (k + 1) * m));
		
		j_vec[0] = _mm_set1_ps(A[j + (k + 1) * m + 0]);
                
                k_vec[0]  = _mm_add_ps(k_vec[0],  _mm_mul_ps(i_vec[1], j_vec[0]));

                k_vec[1] = _mm_add_ps(k_vec[1], _mm_mul_ps(i_vec[3], j_vec[0]));

                k_vec[2] = _mm_add_ps(k_vec[2], _mm_mul_ps(i_vec[5], j_vec[0]));

                k_vec[3] = _mm_add_ps(k_vec[3], _mm_mul_ps(i_vec[7], j_vec[0]));

                k_vec[4] = _mm_add_ps(k_vec[4], _mm_mul_ps(i_vec[9], j_vec[0]));

            }

            for (int k = n - n % 2; k < n; ++k) {
                i_vec[0] = _mm_loadu_ps((A + i +      (k + 0) * m));
                i_vec[2] = _mm_loadu_ps((A + i +  4 + (k + 0) * m));
		i_vec[4] = _mm_loadu_ps((A + i +  8 + (k + 0) * m));
                i_vec[6] = _mm_loadu_ps((A + i + 12 + (k + 0) * m));
                i_vec[8] = _mm_loadu_ps((A + i + 16 + (k + 0) * m));

                j_vec[0] = _mm_set1_ps(A[j + (k + 0) * m + 0]);

                k_vec[0]  = _mm_add_ps(k_vec[0],  _mm_mul_ps(i_vec[0], j_vec[0]));

                k_vec[1] = _mm_add_ps(k_vec[1], _mm_mul_ps(i_vec[2], j_vec[0]));

		k_vec[2] = _mm_add_ps(k_vec[2], _mm_mul_ps(i_vec[4], j_vec[0]));

                k_vec[3] = _mm_add_ps(k_vec[3], _mm_mul_ps(i_vec[6], j_vec[0]));

                k_vec[4] = _mm_add_ps(k_vec[4], _mm_mul_ps(i_vec[8], j_vec[0]));
            }

            _mm_storeu_ps((C + i +      (j + 0) * m), k_vec[0]);
            _mm_storeu_ps((C + i +  4 + (j + 0) * m), k_vec[1]);
            _mm_storeu_ps((C + i +  8 + (j + 0) * m), k_vec[2]);
            _mm_storeu_ps((C + i + 12 + (j + 0) * m), k_vec[3]);
            _mm_storeu_ps((C + i + 16 + (j + 0) * m), k_vec[4]);
        }
#pragma omp for nowait
        for (int i = m - m % 20; i < m; i += 1) {
            for (int k = 0; k < n - n % 16; k += 16) {
                C[i + (j + 0) * m] += A[i + (k + 0) * m] * A[(j + 0) + (k + 0) * m];
                C[i + (j + 0) * m] += A[i + (k + 1) * m] * A[(j + 0) + (k + 1) * m];
		C[i + (j + 0) * m] += A[i + (k + 2) * m] * A[(j + 0) + (k + 2) * m];
                C[i + (j + 0) * m] += A[i + (k + 3) * m] * A[(j + 0) + (k + 3) * m];
		C[i + (j + 0) * m] += A[i + (k + 4) * m] * A[(j + 0) + (k + 4) * m];
                C[i + (j + 0) * m] += A[i + (k + 5) * m] * A[(j + 0) + (k + 5) * m];
		C[i + (j + 0) * m] += A[i + (k + 6) * m] * A[(j + 0) + (k + 6) * m];
                C[i + (j + 0) * m] += A[i + (k + 7) * m] * A[(j + 0) + (k + 7) * m];
		C[i + (j + 0) * m] += A[i + (k + 8) * m] * A[(j + 0) + (k + 8) * m];
                C[i + (j + 0) * m] += A[i + (k + 9) * m] * A[(j + 0) + (k + 9) * m];
		C[i + (j + 0) * m] += A[i + (k + 10) * m] * A[(j + 0) + (k + 10) * m];
                C[i + (j + 0) * m] += A[i + (k + 11) * m] * A[(j + 0) + (k + 11) * m];
		C[i + (j + 0) * m] += A[i + (k + 12) * m] * A[(j + 0) + (k + 12) * m];
                C[i + (j + 0) * m] += A[i + (k + 13) * m] * A[(j + 0) + (k + 13) * m];
		C[i + (j + 0) * m] += A[i + (k + 14) * m] * A[(j + 0) + (k + 14) * m];
                C[i + (j + 0) * m] += A[i + (k + 15) * m] * A[(j + 0) + (k + 15) * m];
            }
            for (int k = n - n % 16; k < n - n%4; k += 4) {
                C[i + (j + 0) * m] += A[i + (k + 0) * m] * A[(j + 0) + (k + 0) * m];
                C[i + (j + 0) * m] += A[i + (k + 1) * m] * A[(j + 0) + (k + 1) * m];
		C[i + (j + 0) * m] += A[i + (k + 2) * m] * A[(j + 0) + (k + 2) * m];
                C[i + (j + 0) * m] += A[i + (k + 3) * m] * A[(j + 0) + (k + 3) * m];
            }
	    for (int k = n - n % 4; k < n; k += 1) {
                C[i + (j + 0) * m] += A[i + (k + 0) * m] * A[(j + 0) + (k + 0) * m];
            }
        }
    }
}
}
