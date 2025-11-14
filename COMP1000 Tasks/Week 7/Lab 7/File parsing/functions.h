#include <iostream>
#include <iomanip>
using namespace std;

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
	for (int y = input.length() - 1; y > start - 1; y--)
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

void column_conditional_output(string data, string* message_to_column_array, int number_of_columns, int column_width = 10, char seperator_char = ':')
{
	if (sizeof(data) == 0)
	{
		return;
	}
	static int current_column = 0;
	number_of_columns -= 1;
	string current_message;
	if (current_column > number_of_columns)
	{
		cout << "hello";
		cout << "The current column number has exceeded the number of columns. Have you changed it?" << "\n";
		current_column = 0;
		return;
	}
	current_message = *(message_to_column_array + current_column);
	cout << current_message << seperator_char <<  data << setw(column_width);
	if (current_column == number_of_columns)
	{
		current_column = 0;
		cout << "\n";
	}
	else
	{
		current_column+= 1;
	}
}