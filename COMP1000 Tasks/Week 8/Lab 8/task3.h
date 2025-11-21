#include <iostream>
using namespace std;

class Car
{
private:
	string make;
	int year;
public:
	Car()
	{
		make = "Unknown";
		year = 0;
	}
	Car(string make_in, int year_in)
	{
		make = make_in;
		year = year_in;
	}
	~Car()
	{
		cout << make << "deleted" << "\n";
	}
	void display_info()
	{
		cout << "Make: " << make << ", Year: " << year << "\n";
	}
};

void task3()
{	
	Car unc = Car();
	unc.display_info();
	Car bsd = Car("Toyota", 2021);
	bsd.display_info();

}