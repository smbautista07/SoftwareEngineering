//Name - Sean Bautista
//ID - 25123371

#include <iostream>
#include <string>
using namespace std;
const int studentID = 25123371;

bool negativeStringCheck(string stringNumber)
{
	return stringNumber[0] == '-'; //compares the first character to the negative sign. Returns true if it is equal (thus negative), and false if it isn't
}

bool stringIntCheck(string input) //checks whether the string value stores an integer
{
	for (int i = negativeStringCheck(input); i < input.length(); i++) //loops through entire string, ignoring the first character if it's a negative sign
	{
		if (isdigit(input[i]) == false)
		{
			cout << "Input contains a character which is neither a digit nor negative sign." << "\n"; //informs the user what's wrong with the input
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

bool stringInt32Check(string input)
{
	bool isNegative = negativeStringCheck(input);

	//must all be true until the end
	bool validInput = true; //flag for if the input can be turned into an integer 10 digits or less
	bool validInteger = true; //flag for if the input is within the range of values for a 32 bit integer
	
	if (input.length() > 10 + isNegative) //checks if the input is too long (>10 when excluding negative sign). Addressed first in case of absurdly long input
	{
		cout << "Input is too large to be a 32 bit integer (up to 10 characters long, or 11 for negative numbers)" <<"\n";
		validInput = false;
	}

	if (stringIntCheck(input) == false)
	{
		validInput = false;
	}

	//if the inputs are invalid, stop checking. The remaining checks require an string integer which is 10 or less characters long.
	if (validInput == false)
	{
		return false;
	}

	//if the string is less than 10 digits long (excluding the negative sign) it is always valid. Most inputs are this
	if (input.length() < 10 + isNegative)
	{
		return true;
	}

	//The only remaining inputs are exactly 10 digits long when excluding the negative sign.
	//Check if the value is below the maximum 32 bit integer absolute value ((-1 ))
	//Comparing 9 of the 10 digits to prevent possibility of overflow
	string highest9Digits = input.substr(isNegative, 9); //substring which starts at the first digit which is 9 digits long
	if (stringToInt(highest9Digits) > INT_MAX / 10) 
	{
		validInteger = false;
	}

	if (stringToInt(highest9Digits) == INT_MAX / 10)//if the first 9 digits are equal,
	{
		//compare the final digits
		char lowestDigit = input[input.length()-1]; //highest digit

		if (lowestDigit > '7'+isNegative) //does not need to be converted into integer for coomparison
		{
			validInteger = false;
		}
	}

	if (validInteger == false) 
	{
		cout << "The integer you input is too large" << "\n"; 
		return false;
	}

	//the only remaining numbers are smaller or equal to the maximum value
	return true;
}

string trim(string input) //Removes the spaces before and after an input
{
	//declare two variables which determine the start and end of the input. 
	int start;
	int end;

	//iterate from the start of the input
	for (int x = 0; x < input.length(); x++)
	{
		if (isspace(input[x]) == false)
		{
			start = x; //start variable is set to the index of the first non-space character
			break;
		}
	}
	//iterate from end of input to the start. 
	for (int y = input.length()-1; y > start-1; y--)
	{
		if (isspace(input[y]) == false)
		{
			end = y; //end variable is set to the index of the last non-space character.
			break;
		}
	}
	int length = end - start + 1; //length of the string which will be returned
	return input.substr(start, length);
}

int int32Input(string promptMessage)	//ensures a 32 bit integer is input without crashing from invalid data types
{
	cout << promptMessage << "\n"; //lets the user know that they have to input something, starts a new line for input

	//store user input as a string to avoid type error
	string input;

	//loops until an input is valid
	do
	{
		//user input
		getline(cin, input); //input method which, unlike cin with an extraction operator, does not use the space as a delimiter.
		
		if (input.length() == 0) //prevent empty inputs
		{
			cout << "Empty input. Try again" <<"\n";
			continue;
		}

		input = trim(input); //removes leading and trailing spaces
	} while (stringInt32Check(input) == false);
	return stringToInt(input);
}


void task1()
{
	//Initialises two integer variables using user integer input twice.
	int num1 = int32Input("Input one number");  //Second to last digit of studentID = 7
	int num2 = int32Input("Input another"); //Last digit of studentID = 1

	//outputs the sum of the two inputs. 
	cout << num1 << " + " << num2 << " = " << num1 + num2; //Would output 8 (7+1) using studentID
}

void task2()
{
	int num1 = int32Input("Input one number");
}


int main()
{
	task1();
	
	return 0;
}