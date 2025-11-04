#pragma once

#include <stdio.h>
#include <stdlib.h>

/* cannot be done due to arrays passed in as arguments decaying to the pointer of the first item in the array.
void arrayDisplay(short arr[])
{
	int arraySize = sizeof(arr) / sizeof(arr[0]);
	printf("[");
	for (int arrIdx = 0; arrIdx < arraySize-1; arrIdx++)
	{
		printf("%hu,", arr[arrIdx]);
	}
	printf("%hu", arraySize);
	printf("]\n");
}
*/

void task2()
{
	short arr1[10]; //initialise arrays inside function since they are only for this task.
	short arr2[10];
	unsigned short arr3[10];

	for (int arrIdx = 0; arrIdx < 10; arrIdx++)
	{
		arr1[arrIdx] = rand();
		arr2[arrIdx] = rand();
	}
	

	for (int arrIdx = 0; arrIdx < 10; arrIdx++)
	{
		arr3[arrIdx] = arr1[arrIdx] + arr2[arrIdx]; 
		printf("%hu ",arr3[arrIdx]);
	}

}