#include <iostream>
using namespace std;

template <typename val1, typename val2>

class Pair
{
private:
	val1 first;
	val2 second;
public:
	Pair(val1 value1_in, val2 value2_in)
	{
		first = value1_in;
		second = value2_in;
	}
	void display_pair()
	{
		cout << "First: " << first << ", Second: " << second << "\n";
	}
};

void task3()
{
	Pair<int, string> is = Pair<int, string>(322, "hihaia");
	Pair<double, char> dc = Pair<double, char>(323.32, '2');
	is.display_pair();
	dc.display_pair();
}