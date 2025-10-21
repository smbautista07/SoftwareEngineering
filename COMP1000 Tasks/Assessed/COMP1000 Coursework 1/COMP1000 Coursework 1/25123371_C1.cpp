//Name - Sean Bautista
//ID - 25123371

#include <iostream>
using namespace std;
const int studentID = 25123371;

int intInput(string promptMessage) //local message parameter to be output
{
	int input;
	cout << promptMessage << "\n"; //
	cin >> input;
	if (isdigit(input))
	cout << input << "\n";
	return input;
}


void task1()
{
	//initialise local integer variables
	int num1; //if last number of studentID, equal to 1
	int num2; //if second to last number of studentID, equal to 7
	cout << "Input one number\n"; //Prompts the user to enter a number
	cin >> num1; //stores input value into integer variable
	cout << "Input another number to add to it\n"; //Prompts the user to enter a second number
	cin >> num2; //

	cout << num1+num2;

	
}
int main()
{
	//task1();
	int temp;
	temp = intInput("Input an integer");
	cout << temp;
	return 0;
}