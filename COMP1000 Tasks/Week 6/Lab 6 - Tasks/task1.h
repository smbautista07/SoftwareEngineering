#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

/*
Task 1: Writing Data to Files Using ofstream
Objective: Practice using ofstream to write data to files.
Instructions:
1. Create a new file and write multiple types of data to it. Use different data types like
integers, floating points, and strings.
2. Format the output using stream manipulators (setw, setprecision).
3. Ensure to handle file opening errors using is_open() and close the file after writing
*/
void task1()
{
	string file_name = "file.txt";
	int input1 = 51551351;
	string input2 = "tyuiolkjhgfvbnm";
	float input3 = 4.0002;

	ofstream fw(file_name);
	if (fw.is_open())
	{
		fw << input1 << "\n" << input2 << "\n" << input3 << "\n";
		fw.close(); //3
	}

	string return_value[3];
	int return_value_length = sizeof(return_value) / sizeof(return_value[0]);

	ifstream fr;
	fr.open(file_name);
	if (fr.is_open())
	{
		for (int file_line = 0; file_line < return_value_length; file_line++)
		{
			getline(fr, return_value[file_line]);
		}
		fr.close();
	}

	for (int output_loop = 0; output_loop < return_value_length; output_loop++)
	{
		cout << setw(18) << return_value[output_loop] << "\n";
	}
}