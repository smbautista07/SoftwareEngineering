#pragma once
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

void csv_access()
{
	ifstream fr;
	fr.open("tast.txt");
	string output_string;
	if (fr.is_open())
	{
		while (getline(fr, output_string, ','))
		{
			cout << output_string << "\n";
		}
	}
}