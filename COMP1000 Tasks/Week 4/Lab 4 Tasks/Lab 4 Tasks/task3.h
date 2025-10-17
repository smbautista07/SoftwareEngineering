#pragma once
#include <iostream>
using namespace std;

void task3() //Define a function inside a header file which can be used in the main program
{
	int hundo = 100;
	int *hundoPointer = &hundo;
	//cout << hundoPointer << "\n"; //outputs the memory address itself
	cout << *hundoPointer << "\n"; //outputs the value stored at the address
	*hundoPointer = 101; //modify via address
	cout << hundo << "\n"; //affects the value called by variable
}
