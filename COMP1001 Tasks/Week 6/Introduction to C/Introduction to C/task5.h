#pragma once
#include <stdio.h>

void task5()
{
	char input[1024];
	scanf_s("%1024s", input, sizeof(input));
	short stringIndex = 0;

	char emptyChar = 0;
		

	while (input[stringIndex] != emptyChar)
	{
		stringIndex++;
	}
	printf("%s is %hu characters long \n", input, stringIndex);
}