#include"matrix_mul.h"

/*
* @Description: This file contains function to multiply 8 sets of matrices parallely using AVX.
*                           Ai x Bi = Ci
* @param[in]: float [][][8], float [][][8], float [][][8]
* @param[out]: None (Products are stored in third input variable)
*/

void AVX_Multiply(float A[A_ROWS][A_COLS][8],float B[B_ROWS][B_COLS][8], float C[A_ROWS][B_COLS][8])
{
	/* Initialising AVX vector arrays (2D) */
	__m256 vecA[A_ROWS][A_COLS], vecB[B_ROWS][B_COLS], vecC[A_ROWS][B_COLS];

  for(int a_row = 0; a_row < A_ROWS; a_row ++)
  {
    for(int b_col = 0; b_col < B_COLS; b_col ++)
    {
      vecC[a_row][b_col] = _mm256_set1_ps(0);
      for(int a_col = 0; a_col < A_COLS; a_col ++)
      {
				/* Storing corresponding row-column elements from each matrix set */
        vecA[a_row][a_col] = _mm256_setr_ps(A[a_row][a_col][0], A[a_row][a_col][1], A[a_row][a_col][2], A[a_row][a_col][3],
          A[a_row][a_col][4], A[a_row][a_col][5], A[a_row][a_col][6], A[a_row][a_col][7]);
        vecB[a_col][b_col] = _mm256_setr_ps(B[a_col][b_col][0], B[a_col][b_col][1], B[a_col][b_col][2], B[a_col][b_col][3],
          B[a_col][b_col][4], B[a_col][b_col][5], B[a_col][b_col][6], B[a_col][b_col][7]);

				/* Computing all 8 values at once using FMA */
        vecC[a_row][b_col] = _mm256_fmadd_ps(vecA[a_row][a_col], vecB[a_col][b_col], vecC[a_row][b_col]);
      }
      _mm256_store_ps(&C[a_row][b_col][0], vecC[a_row][b_col]); /* Storing values in output float matrix */
    }
  }
}

int main()
{

  __attribute__((aligned(32))) float A[A_ROWS][A_COLS][8];
  __attribute__((aligned(32))) float B[B_ROWS][B_COLS][8];
  __attribute__((aligned(32))) float C[A_ROWS][B_COLS][8];

	/* Assigning Values to A and B*/
  for(int i = 0; i < A_ROWS; i++)
  {
    for(int j = 0; j < A_COLS; j++)
    {
      for(int n = 0; n < 8; n++)
      {
        A[i][j][n] = n*i*j + n + 2*i + 3*j;
      }
    }
  }
  for(int i = 0; i < B_ROWS; i++)
  {
    for(int j = 0; j < B_COLS; j++)
    {
      for(int n = 0; n < 8; n++)
      {
        B[i][j][n] = n + 7*i + 3*j;
      }
    }
  }

	/* Code Profiling */
  wnNrExeTimeX86Intel(0, ITER);
  for (int i =0; i < ITER; i++)
  {
    AVX_Multiply(A,B,C);
  }
  wnNrExeTimeX86Intel(1, ITER);

}
