#pragma once
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <omp.h>

#define arrSize 10000000

int executionTimes = 10;
static short shortArr[arrSize];




void initArr()
{
	for (int i = 0; i < arrSize; i++)
	{
		shortArr[i] = rand();
	}
}

int returnMax()
{
	int max = shortArr[0];
	int i;
	for (i = 1; i < arrSize; i++)
	{
		if (shortArr[i] > max)
		{
			max = shortArr[i];
		}
	}
	return max;
}

int returnMin()
{
	int min = shortArr[0];
	int i;
	for (i = 1; i < arrSize; i++)
	{
		if (shortArr[i] < min)
		{
			min = shortArr[i];
		}
	}
	return min;
}

double task1Amended()
{
	double startTime, endTime;
	startTime = omp_get_wtime();
	for (int i = 0; i < executionTimes; i++)
	{
		int highestNum = returnMin();
		int lowestNum = returnMax();
	}
	endTime = omp_get_wtime();
	//printf("%f\n", endTime - startTime);
	return endTime - startTime;
}
