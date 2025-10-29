//Name - Sean Bautista
//ID - 25123371

#include <iostream>
using namespace std;
const int studentID = 25123371;

bool negativeStringCheck(string stringNumber)
{
	return stringNumber[0] == '-'; //compares the first character to the negative sign. Returns true if it is equal (thus negative), and false if it isn't
}

bool stringIntCheck(string stringNumber) //checks whether the string value stores an integer
{
	
	//if user input is too large - max 32 bit integer length as a string is 10 (+ 1 if negative sign), the input is invalid
	/*if (stringNumber.length() > 10 + negativeStringCheck(stringNumber)) //bools can be implicity converted to integer values 0 or 1, so 11 character inputs are accepted as long as the input is negative
	{
		cout << "input is too long" << "\n"; //informs the user of the error
		return false;
	}*/
	
	//checks if the string any characters which isn't a negative sign or digit.
	for (int i = negativeStringCheck(stringNumber); i < stringNumber.length(); i++) //loops through entire string, ignoring the first character if it's a negative sign
	{
		if (isdigit(stringNumber[i]) == false) 
		{
			cout << "input contains a character which is neither a digit nor negative sign."; //informs the user what's wrong with the input
			return false; 
		}
	}
	return true; // if both checks haven't found anything wrong, return true
}

int stringToInt(string stringNumber)
{
	int number = 0;
	for (int i = negativeStringCheck(stringNumber);i < stringNumber.length();i++)
	{
		number *= 10;
		int digit = stringNumber[i] - '0'; //difference between the ASCII code for a digit and the ASCII code for 0 is equal to its value as a digit
		number += digit;
	}
	if (negativeStringCheck(stringNumber)) //if the number is negative
	{
		number = -number; //multiply by -1
	}
	return number;
}

bool stringInt32Check(string stringNumber)
{
	bool isNegative = negativeStringCheck(stringNumber);
	if (stringNumber.length() > 10 + isNegative) //checks if the input is too long (>10 when excluding negative sign). Addressed first in case of absurdly long input
	{
		cout << "Input is too large to be a 32 bit integer (up to 10 characters long, or 11 for negative numbers)" <<"\n";
		return false;
	}

	if (stringIntCheck(stringNumber) == false) 
	{
		return false;
	}

	//if the string is less than 10 digits long (excluding the negative sign) it is always valid. Most inputs are this
	if (stringNumber.length() < 10 + isNegative)
	{
		return true;
	}

	//the only remaining inputs are exactly 10 digits long when excluding the negative sign.
	//check if the value is below the maximum 32 bit integer absolute value ((-1 ))
	//Comparing 9 of the 10 digits to prevent possibility of overflow
	string highest9Digits = stringNumber.substr(isNegative, 9); //substring which starts at the first digit which is 9 digits long
	if (stringToInt(highest9Digits) > INT_MAX / 10) 
	{
		cout << "The integer you input is too large" << "\n";
		return false; 
	}

	if (stringToInt(highest9Digits) == INT_MAX / 10)//if the first 9 digits are equal,
	{
		//compare the final digits
		char lowestDigit = stringNumber[stringNumber.length()-1]; //highest digit

		if (lowestDigit > '7'+isNegative) //does not need to be converted into integer for coomparison
		{
			cout << "The integer you input is too large" << "\n"; //final digit of INT_MAX
			return false;
		}
	}
	//the only remaining numbers are smaller or equal to the maximum value
	return true;
}

int int32Input(string promptMessage)	//ensures a 32 bit integer is input without crashing from invalid data types
{
	cout << promptMessage << "\n"; //lets the user know that they have to input something, starts a new line for input

	//store user input as a string to avoid type error
	string input;
	//loops until an input is valid
	do
	{
		//reset loop flag
		bool validInput = true; //initialises flag which informs the program to loop if nothing wrong is found with the input

		//user input
		cin >> input;	

		//checks if an integer is stored in string
	} while (stringInt32Check(input) == false);
	
	return stringToInt(input);

	
	return 0;
}


void task1()
{
	//Initialises two integer variables using user integer input twice.
	int num1 = int32Input("Input one number");  //Second to last digit of studentID = 7
	int num2 = int32Input("Input another"); //Last digit of studentID = 1

	//outputs the sum of the two inputs. 
	cout << num1+num2; //Would output 8 (7+1) using studentID
}
int main()
{
	
	cout << int32Input("test");
	
	return 0;
}