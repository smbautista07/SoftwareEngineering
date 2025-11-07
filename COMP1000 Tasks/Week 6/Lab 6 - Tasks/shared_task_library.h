#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void file_error_message(string file_name, string access_type)
{
	cout << "Unable to " << access_type << " " << file_name;
}

void file_append_line(string file_name, string data)
{
	ofstream fa;
	fa.open(file_name, ofstream::app);
	bool successful;
	if (fa.is_open())
	{
		fa << data << "\n";
		fa.close();
	}
	else
	{
		file_error_message(file_name, "append");
	}
}

void file_reset(string file_name)
{
	ofstream fo;
	fo.open(file_name);
	if (fo.is_open())
	{

		fo.close();
	}
	else
	{
		file_error_message(file_name, "reset");
	}
}

int count_lines(string file_name)
{
	ifstream fr;
	fr.open(file_name);
	string dump;
	int line_count = 0;
	if (fr.is_open())
	{
		while (getline(fr, dump))
		{
			line_count++;
		}
	}
	return line_count;
}


void file_read_lines(string file_name)
{
	ifstream fr;
	string output_line;

	int line_count = count_lines(file_name);


	fr.open(file_name);
	if (fr.is_open())
	{
		while (getline(fr, output_line))
		{
			
		}
		fr.close();
	}
	else
	{
		file_error_message(file_name, "read");
	}
}

