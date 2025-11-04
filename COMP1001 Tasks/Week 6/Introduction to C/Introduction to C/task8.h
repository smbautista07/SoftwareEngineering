#pragma once
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

void task8()
{
	short randShortArr[64];

	short arrLen = sizeof(randShortArr) / sizeof(randShortArr[0]);
	for (short arrIdx = 0; arrIdx < arrLen; arrIdx++)
	{
		randShortArr[arrIdx] = rand();
		printf("%hu ", randShortArr[arrIdx]);
	}


	int highestNum = SHRT_MIN;
	int lowestNum = SHRT_MAX;	
	

	for (short arrIdx = 0; arrIdx < arrLen; arrIdx++)
	{
		if (highestNum < randShortArr[arrIdx])
		{
			highestNum = randShortArr[arrIdx];
		}
		if (lowestNum > randShortArr[arrIdx])
		{
			lowestNum = randShortArr[arrIdx];
		}
	}



	printf("Highest value: %hu \nLowest value: %hu\n", highestNum, lowestNum);

}