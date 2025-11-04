#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void task7()
{
	short randShortArr[64];

	short arrLen = sizeof(randShortArr) / sizeof(randShortArr[0]);
	for (short arrIdx = 0; arrIdx < arrLen; arrIdx++)
	{
		randShortArr[arrIdx] = rand();
	}


	short highestNum = -INFINITY;

	for (short arrIdx = 0; arrIdx < arrLen; arrIdx++)
	{
		if (highestNum < randShortArr[arrIdx])
		{
			highestNum = randShortArr[arrIdx];
		}
	}

	printf("%hu \n", highestNum);
}