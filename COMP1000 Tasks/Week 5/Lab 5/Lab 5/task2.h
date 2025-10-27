#pragma once
#include <iostream>
using namespace std;

void swapNumbers(int &a, int& b)
{
	cout << a << "\n";
	cout << &a << "\n";
	cout << *&a << "\n";
	cout << b << "\n";
	cout << &b << "\n";
	int* temp = &a;
	a = b;
	//b = temp;
	cout << a << "\n";
	cout << b << "\n";
}