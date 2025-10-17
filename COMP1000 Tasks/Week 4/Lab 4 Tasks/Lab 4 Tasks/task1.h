#pragma once
#include <iostream>
using namespace std;

void task1() //Define a function inside a header file which can be used in the main program
{
	int array[10];
	for (int x = 1; x < 11; x++)
	{
		cout << x << "\n";
	}
}