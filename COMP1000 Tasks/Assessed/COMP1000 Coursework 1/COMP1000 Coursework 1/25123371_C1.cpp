//Name - Sean Bautista
//ID - 25123371

#include <iostream>
using namespace std;
const int studentID = 25123371;

bool negativeStringCheck(string stringNumber)
{
	return stringNumber[0] == '-'; //compares the first character to the negative sign. Returns true if it is equal (thus negative), and false if it isn't
}

int intInput(string promptMessage)	//ensures a 32 bit integer is input without crashing from invalid data types
{
	cout << promptMessage << "\n"; //lets the user know that they have to input something, starts a new line for input

	//loops until an input is valid
	do
	{
		//reset loop flag
		bool validInput = true; //initialises flag which informs the program to loop if nothing wrong is found with the input

		//user input
		string input;	//store user input as a string to avoid type error
		cin >> input;	

		bool isNegative = negativeStringCheck(input); /*declare boolean to tell if the number is negative.
	Since this loop iterates by each character in the string to ensure only digits, the numbers are assumed positive, so operations
	will be done assuming the number is positive before converting the number to negative at the end this value is true.*/

		//if user input is too large - max integer length as a string is 10 (+ 1 if negative), the input is invalid
		if (input.length() > 10+isNegative) //isNegative can be implicity converted to integer values 0 or 1, so 11 character inputs are accepted as long as the input is negative
		{
			cout << "input is too long" << "\n"; //informs the user of the error
			validInput = false;
		}
		
		
		
		//loops through every character in the input to check if any are non-numeric (exclude first if negative)
		for (int i = isNegative; i < input.length(); i++) 
		{
			if (isdigit(input[i])) //if the 
			{

			}   
		}
		

	} while (true);

	//Iterates for every character in the string.


	//if (isdigit(ch))
	//cout << input << "\n";
	//return input;
	return 0;
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
	intInput("test");

	return 0;
}