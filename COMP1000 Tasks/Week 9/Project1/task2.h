#include <iostream>
using namespace std;



string word_to_upper(string val)
{
	string val_out = "";
	for (int i = 0; i < val.length(); i++)
	{
		val_out += (char)toupper(val[i]);
	}
	return val_out;
}

class Printer
{
//private:
public:
	void print(int val)
	{
		cout << val * 2;
	}
	void print(string val)
	{
		val = word_to_upper(val);
		cout << val;
	}
	
};


void task2()
{
	Printer p;
	p.print("mmya2321a");
	

}