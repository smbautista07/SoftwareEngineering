#pragma once
#pragma once
#include <iostream>
using namespace std;

void task5() //Define a function inside a header file which can be used in the main program
{
	char* strArray = new char[20];
	//cout << strArray;
	string userInput;
	cout << "Input up to 20 character string:\n";
	cin >> userInput;
	int stringLength = userInput.length();
	int loops = stringLength;
	if (stringLength > 20)
	{
		loops = 20;
	}

	for (int x = 0; x < loops; x++)
	{
		*(strArray + x) = userInput[x];
		cout << *(strArray + x) <<"\n";
	}
	//cout << *strArray;
	
}