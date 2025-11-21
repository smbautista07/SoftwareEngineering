#include <iostream>
using namespace std;

class Counter
{
private:
	static int count;
public:
	
	Counter()
	{
		count ++;
	}
	void displayCount()
	{
		cout << "Count " << count<<"\n";	
	}
	~Counter()
	{
		count += -1;
	}
	
};


int Counter::count = 0;

void task4()
{
	
	Counter count1, count2, count3;
	count1.displayCount();
	if (true)
	{
		Counter count4;
		count4.displayCount();
	}
	count2.displayCount();
}
