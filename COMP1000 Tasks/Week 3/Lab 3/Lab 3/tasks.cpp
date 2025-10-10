#include <iostream>
#include "example.h"
using namespace std;

int input;

void task1() //simple if else comparison
{
	
	cout << "what age?\n";
	cin >> input;
	if (input >= 18)
	{
		cout << "You are elegible to vote";
	}
	else 
	{
		cout << "You are not elegible to vote";
	}
}

void task2()
{
	int marks;
	cout << "Exam score?\n";
	cin >> marks;
	if (marks >= 90)
	{
		cout << "Grade A";
	}
	else if (marks >= 80)
	{
		cout << "Grade B";
	}
	else if (marks >= 70)
	{
		cout << "Grade C";
	}
	else if (marks >= 60)
	{
		cout << "Grade D";
	}
	else if (marks < 60)
	{
		cout << "Grade F";
	}
}

void task3()
{
	float num1;
	float num2;
	int choice;
	cout << "Pick a number\n";
	cin >> num1;
	cout << "Pick another number\n";
	cin >> num2;
	cout << "Choose what to do:\n" << "1 - Add\n" << "2 - Subtract\n" << "3 - Multiply\n" << "4 - Divide\n";
	cin >> choice;
	
	switch (choice)
	{
	case 1:
		cout << num1 + num2;
		break;
	case 2:
		cout << num1 - num2;
		break;
	case 3:
		cout << num1 * num2;
		break;
	case 4:
		cout << num1 / num2;
		break;
	}
}

void task4() //simple menu screen
{
	int choice;
	cout << "Pick an Option\n" << "1 - Start Game\n" << "2 - Load Game\n" << "3 - Quit\n";
	cin >> choice;
	switch (choice)
	{
	case 1:
		cout << "Starting!";
		break;

	case 2:
		cout << "Loading...";
		break;
	case 3:
		cout << "Quitting...";
		break;
	default:
		cout << "That's not an option!";
	}

}

void task5()
{
	int temperature;
	cout << "What's the temperature?\n";
	cin >> temperature;
	if (temperature < 0)
	{
		cout << "It's freezing";
	}
	else
	{
		if (temperature <= 15)
		{
			cout << "It's cold";
		}
		else
		{
			if (temperature <= 30)
			{
				cout << "It's warm";
			}
			else
			{
				if (temperature > 30)
				{
					cout << "It's hot";
				}
			}
		}

	}
}

int main() 
{
	task5();
	return 0;
}