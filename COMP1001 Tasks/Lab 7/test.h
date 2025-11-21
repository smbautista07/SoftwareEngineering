#pragma once
#include <omp.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
#define time_function_repeats 100
#define array_size 10000

double time_function(void(*callback)(), int repeat_count)
{
	double start_time, stop_time, time_delta;
	start_time = omp_get_wtime();

	for (int current_loop; current_loop < repeat_count; current_loop++)
	{
		callback();
	}
	stop_time = omp_get_wtime();
	time_delta = stop_time - start_time;
	printf("%f", time_delta);

}


float* initialise_random_float_array()
{
	float arr[array_size];
	for (int i = 0; i < array_size; i++)
	{
		arr[i] = (float)rand()*(float)rand() / (float)rand();
	}
	return arr;
}