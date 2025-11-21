#include <stdlib.h>]
#include <immintrin.h>

void ADD_SSE(float *arr1, float *arr2, float *result_arr) 
{
	__m128 add_set_1, add_set_2, result_set; //can store 4 floats (32 bit each) 
	add_set_1 = _mm_load_ps(arr1);
	add_set_2 = _mm_load_ps(arr2);
	result_set = _mm_add_ps(add_set_1, add_set_2);
	_mm_storeu_ps(result_arr, result_set);
}

void ADD_AVX(float* arr1, float* arr2, float* result_arr)
{
	__m256 add_set_1, add_set_2, result_set; //can store 8 floats (32 bit each) 
	add_set_1 = _mm256_load_ps(arr1);
	add_set_2 = _mm256_load_ps(arr2);
	result_set = _mm256_add_ps(add_set_1, add_set_2);
	_mm256_storeu_ps(result_arr, result_set);
}