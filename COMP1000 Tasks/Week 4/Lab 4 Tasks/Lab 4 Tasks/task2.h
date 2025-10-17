#pragma once
#include <iostream>
using namespace std;

void task2() //Define a function inside a header file which can be used in the main program
{
	string text1 = "Hamburger";
	string text2 = "Whopper";
	string text3 = text1 + text2;
	cout << text3;
}
