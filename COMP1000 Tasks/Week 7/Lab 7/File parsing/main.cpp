#include <fstream>
#include <string>
#include <sstream>
#include "functions.h"
using namespace std;

int main()
{
	ifstream fr;
	fr.open("data.csv");
	string data_types[3] = { "Name","Age","City" };

	if (fr.is_open())
	{
		string current_line;
		int column = 0;
		while (getline(fr, current_line))
		{	
			string output;
			stringstream ss(current_line);
			while (getline(ss, output, ','))
			{
				column_conditional_output(output, data_types, sizeof(data_types) / sizeof(data_types[0]));
			}
		}
	}
	fr.close();


	return 0;
}
