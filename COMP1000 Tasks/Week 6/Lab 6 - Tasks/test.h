#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//the purpose of this was to experiment with opening and closing files.
void test()
{
	string file_name = "test.txt";
	ofstream fs;
	fs.open(file_name);
	if (fs.is_open())
	{
		fs << "Example text" << "\n";
		fs.close();
	}
	else
	{
		cout << "Unable to open file for writing:" << file_name;
	}

	string s;

	ifstream fg;
	fg.open(file_name);
	if (fg.is_open())
	{
		getline(fg, s);
		fg.close();
	}
	else
	{
		cout << "Unable to open file for reading:" << file_name << "\n";
	}
	
	cout << s;
}

void test2()
{
	string file_name = "test.txt";
	fstream f;
	f.open(file_name, fstream::app); //only works with 1 fstream parameter
	string return_text;

	if (f.is_open())
	{
		f << "xmpl txt";
		f.close();
	}

}