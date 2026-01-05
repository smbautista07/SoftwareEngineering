#include <stdlib.h>
#include <stdio.h>
//#include "task1.h"
//#include "test.h"
#include <omp.h>
#include <stdio.h>
#include <immintrin.h>
using namespace std;


void add_to_total(double *total_pointer, double num)
{
	*(total_pointer) += num;
}
int main() {
	

		
		// Write C code here
		float B[3];
		__m128 set1, set2, set3;
		set1 = _mm_set_ps(2,4,6,8);
		set2 = _mm_set1_ps(3);
		set3 = _mm_set1_ps(4);
		set1 = _mm_hadd_ps(set1, set1);
		set1 = _mm_hadd_ps(set1, set1);
		B[0] = _mm_cvtss_f32(set3);

		return 0;
		


	// Write C++ code here
	/*double start, middle, stop;
	double total = 0;
	double total2 = 0;

	time_function(add_to_total, 100);
	*/
	
	/*
	for (int i = 0; i < 100000000; i++)
	{
		start = omp_get_wtime();
		middle = omp_get_wtime();
		stop = omp_get_wtime();
		add_to_total(&total, middle-start);
		add_to_total(&total2, stop -middle);
		if (i % 1000000 == 0)
		{
			printf("%f, %f, %f\n", total, total2, (total-total2)*100/total);
			total = 0;
			total2 = 0;
		}
	}
	*/

	return 0;
}
/*
int main()
{
	float arr1[array_size];
	float arr2[array_size];
	float arr3[array_size];
	//ADD_SSE(arr1, arr2, arr3);
	
	for (int i = 0; i < array_size; i ++)
	{
		arr1[i] = rand()%10000;
		arr2[i] = rand()%4713;
	}
	
	double start = omp_get_wtime();

	for (int i = 0; i < array_size; i++)
	{
		arr3[i] = arr1[i] + arr2[i];
	}
	double stop = omp_get_wtime();
	printf("%f", stop-start);

	//for (int i = 0; i < repeats; i+=4)
	//{
		//printf("%f\n",arr3[i]);
	//}

	return 0;
}*/