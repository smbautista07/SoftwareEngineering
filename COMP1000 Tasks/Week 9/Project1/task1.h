#include <iostream>
using namespace std;

template <typename T>
class Box
{
private:
	T value;
	string data_type;
public:
	Box(string value_in)
	{
		value = value_in;
		data_type = "string";
	}
	Box(int value_in)
	{
		value = value_in;
		data_type = "int";

	}
	Box(double value_in)
	{
		value = value_in;
		data_type = "double";
	}


	T getValue()
	{
		cout << "Box value (" << data_type << "): " << value <<"\n";
		return value;
	}
};


void task1()
{
	Box<string> b = Box<string>("Hi");
	Box<int> i = Box<int>(23);
	Box<double> d = Box<double>(23.232);
	b.getValue();
	i.getValue();
	d.getValue();
}