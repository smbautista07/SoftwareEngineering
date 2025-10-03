#include <iostream>
using namespace std;

void task1() //For loop which outputs numbers
{
	for (int x = 0; x < 11; x++) 
	{
		cout << x << "\n";
	}
}

void task2() //Output inputted integers until negative
{
	int input = 0;

	while (input >= 0)
	{
		cout << "input a number vro\n";
		cin >> input;
		cout << input;
	}
}

void task3() //Loop for pattern
{
	for (int x = 0; x < 6; x++)
	{
		for (int y = 0; y < x; y++)
		{
			cout << "*";
		}
		cout << "\n";
	}
}

void task4() //Do-while input validation
{
	int input2 = 0;
	do {
		cout << "input a positive number vro\n";
		cin >> input2;
	} while (input2 < 0 );
}

void task5() 
{
	for (int a = 1; a <= 10; a++)
	{
		for (int b = 1; b <= 10; b++)
		{
			cout << a * b << "\t";
		}
		cout << "\n\n";
	}
}

int main() 
{
	task5();
	return 0;
}