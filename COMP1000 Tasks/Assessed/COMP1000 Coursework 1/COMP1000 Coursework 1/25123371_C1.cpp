//Name - Sean Bautista
//ID - 25123371

#include <string>
#include <iostream>
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

int timesCalled() //function containing static variable defined for task 8
{
	static int calls = 0; //initialise a static variable with the value of 0. This does not affect it again since a static variable does not need to be initialised again.
	calls++; //every time this function is called, the value increments. 
	return calls; //return value stored in the static variable.
}

double averagePositive() {
	// Debugging task 9
	// Function: Computes average of positive numbers until -1 is entered
	// Note: Code contains multiple logical errors for you to fix

	double sum = 0.0;
	int count = 0;
	int num = 0;

	do {
		cin >> num;

		//Bug 1: Negative numbers are added to the sum when only positive numbers should be accepted into the average.
		//Fix: Use an if statement to ensure the number is above 0 before making any changes.
		//Bug 2: Negative numbers increase the count despite being invalid.
		//Fix: Include the count increment in the (if num > 0) statement.
		if (num > 0) //Note: 0 is not a positive number so it is not included in the tally.	
		{
			sum = sum + num;
			count = count + 1;  
		}
	} while (num != -1);

	//Bug 3: Integer division used, which removes any decimal part of the number.
	//Fix: Change sum data type into double. This results in double/integer calculation so that no data is lost
	return sum / count;

	//I tested inputs by outputting value stored by sum after every input and average at the end.
	//All positive: the sum updated every input, the output was the average of all numbers.
	/*	All negative : The sum and average did not change after any input
		The value returned is 0.0 since the value in sum hasn't changed since initialisation.*/
	//Mixed: The positive numbers affected the sum value while the negatives (and 0) had no effect on the average.
}	

void task1() //add two inputs
{
	//Initialises two integer variables using user integer input twice.
	int num1 = int32Input("Input one number");  //Second to last digit of studentID = 7
	int num2 = int32Input("Input another"); //Last digit of studentID = 1

	//outputs the sum of the two inputs. 
	cout << num1 << " + " << num2 << " = " << num1 + num2; //Would output 8 (7+1) using studentID
}

void task2() //multilply input by digit in studentID
{
	int num1 = int32Input("Input one number"); //prompts the user for an integer input
	int num2 = 7; //second to last number of studentID
	cout << num1 << " x " << num2 << " = " << num1 * num2; //returns a message showing the multiplication process and result.
}

void task3()
{
	int loopCount = max(10, studentID % 20); //initialises an integer variable with the higher value between 10 and studentID%20
	//loops from 1 to that value inclusive since the assignment brief specifically said that the end value is either 10 or studentID%20
	for (int i = 1;i <= loopCount; i++)
	{
		cout << i << "\n";  //outputs the current number and starts a new line for clarity.
	}
}

void task4() //odd or even check
{
	int num = studentID; //variable for maintenance
	if (num % 2 == 0) //if studentID mod 2 operator ressults in 0, the number is even
	{
		cout << num << " is even"; //output number and result
	}
	else //otherwise it's odd
	{
		cout << num << " is odd";
	}
}

void task5() //switch case statements
{
	int num = studentID % 7 + 1; //initialises integer variable with studentID mod 7 + 1 
	switch (num) //outputs a different result based on the value stored in the variable
	{
	case 1: //if the value stored in the variable is 1:
		cout << "Monday"; //output Monday, which is the first day of the week
		break;
	case 2: //do the same for the remaining days 2-7
		cout << "Tuesday";
		break;
	case 3:
		cout << "Wednesday";
		break;
	case 4:
		cout << "Thursday";
		break;
	case 5:
		cout << "Friday";
		break;
	case 6:
		cout << "Saturday";
		break;
	case 7:
		cout << "Sunday";
		break;
	default: //if the value stored isn't associated with a day of the week,
		cout << "Not a day of the week"; //tell the user it isn't associated with a day
	}
}

void task6()
{
	int arr[5] = {51,3,studentID % 50,23,44}; //initialise an array with 5 values
	cout << arr[2]; //outputs the third element in the array
}

void task7()
{
	float distance; //initialise a float variable to store result, since it's unlikely to be an integer
	int point1[2]{51, 634};
	int point2[2] = {7, 1};

	//calculates euclidean distance pythagorean theorem: root(a^2 + b^2) = c, where a is the difference in x-coordinates, b is the difference in y-coordinates, and c is the euclidean distance
	distance = sqrt((point1[0] - point2[0]) ^ 2 + (point1[1] - point2[1]) ^ 2);
	
	//tells the user the points and results
	cout <<"Euclidean distance between "<< "(" << point1[0] << "," << point1[1] << ")" << " and " "(" << point2[0] << "," << point2[1] << ")" " = " << distance; 
}

void task8()
{
	for (int i = 0; i < studentID%5; i++) //calls the function studentID%5 times using a loop
	{
		timesCalled();
	}

	//outputs the value of the static variable studentID%5 + 1 when including the call below
	cout << timesCalled();
}

void task9()
{
	cout << averagePositive(); //check averagePositive() function for debugging task changes.
	cin.ignore(); //Clears input stream to prevent issues with task 10, which uses getline.
}

int demonstration = studentID;
void globalOutputDemonstration()
{

	cout << "value of this variable from another function" << demonstration << "\n";
}

void task10() //unsure if this is comparing global with static global or global with local. For now it is just comparing global with local. Needs clarification.
{
	cout << "A global variable with the value " <<demonstration<<"has been declared."<<"\n";
	cout << "Try to overwrite it: ";
	cin >> demonstration;
	cout << "Value you output: " << demonstration;
	globalOutputDemonstration(); //shows accessibility to other functions
	cout << demonstration;
	
}

int main()
{
	//task1();
	//task2();
	//task3();
	//task4();
	//task5();
	//task6();
	//task8();
	//task9();
	//task10();
	return 0;
}