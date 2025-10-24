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
	if (stringNumber.length() > 10 + negativeStringCheck(stringNumber)) //checks if the input is too long (>10 when excluding negative sign). Addressed first in case of absurdly long input
	{
		cout << "Input is too large to be a 32 bit integer (up to 10 characters long, or 11 for negative numbers)";
		return false;
	}

	if (stringIntCheck(stringNumber) == false) 
	{
		return false;
	}

	//if the string is less than 10 digits long (excluding the negative sign) it is always valid. Most inputs are this
	if (stringNumber.length() < 10 + negativeStringCheck(stringNumber))
	{
		return true;
	}

	//the only remaining inputs are exactly 10 digits long when excluding the negative sign.
	//check if the value is below the maximum 32 bit integer absolute value ((-1 ))
	//Comparing 9 of the 10 digits to prevent possibility of overflow
	string first9Digits = stringNumber.substr(negativeStringCheck(stringNumber)+1, stringNumber.length());
	if (stringToInt(first9Digits) > INT_MAX / 10) 
	{
		cout << "The integer you input is too large"; 
		return false; 
	}

	if (stringToInt(first9Digits) == INT_MAX / 10)//if the first 9 digits are equal,
	{
		//compare the final digits
		/*if (stringToInt(stringNumber[stringNumber.length()]) > '7' + negativeStringCheck(stringNumber)) //does not need to be converted into integer
		{
			cout << "The integer you input is too large"; //final digit of INT_MAX
		}*/
	}
	//the only remaining numbers are smaller than the maximum
}


int int32Input(string promptMessage)	//ensures a 32 bit integer is input without crashing from invalid data types
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

		//checks if an integer is stored in string
		
		
		
		
		

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
	//int32Input("test");
	cout << stringToInt("2");
	
	return 0;
}