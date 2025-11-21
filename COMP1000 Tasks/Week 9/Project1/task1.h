#include <iostream>
using namespace std;

template <typename dataType>
class Box
{
public:
	Box(dataType val)
	{
		string value = val;
	}

	string get_value()
	{
		return value;
	}
private:
	string value;
};

void task1()
{
	Box<string> object = Box<string>("43232");
	//Box<string>* new object_on_heapBox<string>("this is for very large objects (more memory but slower)");
	cout << object.get_value() << "\n";

	//cout << object_on_heap->get_value() << "\n"; // -> can access methods through object pointers
}