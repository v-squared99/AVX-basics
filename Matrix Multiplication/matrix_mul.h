#ifndef MATMUL
#define MATMUL

#include<immintrin.h>
#include<stdio.h>
#include"cprofiler.h"
#define A_ROWS 10
#define A_COLS 20
#define B_ROWS 20
#define B_COLS 5

void AVX_Multiply(float A[A_ROWS][A_COLS][8],float B[B_ROWS][B_COLS][8], float C[A_ROWS][B_COLS][8]);

#endif
