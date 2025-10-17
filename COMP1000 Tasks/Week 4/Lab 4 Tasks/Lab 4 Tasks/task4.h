#pragma once
#include <iostream>
using namespace std;

void task4() //Define a function inside a header file which can be used in the main program
{
	int numArray[5] = { 1, 7, 4, 7, 3 };
	int *startPointer = &numArray[0];
	for (int x = 0; x<5;x++)
	{
		cout << *(startPointer+x) << "\n";
	} //outputs normal array

	for (int x = 0; x < 5; x++)
	{
		*(startPointer+x) += 2;
		cout << *(startPointer + x) << "\n";

	} //increments each array value by 2 via memory address and outputs it.

}