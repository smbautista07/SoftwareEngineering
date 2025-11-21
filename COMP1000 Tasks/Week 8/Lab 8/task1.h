#include <iostream>
using namespace std;
class Book
{
public:
	Book(string title_in, string author_in, float price_in)
	{
		title = title_in;
		author = author_in;
		price = price_in;
	}
	void displayInfo()
	{
		cout << "Title: ["<< title<< "] Author: ["<< author<< "] Price ["<< price<< "]\n";
	}
	
private:
	string title;
	string author;
	float price;
};

void task1()
{
	Book Witcher = Book("Witcher", "Guy", 324.3);
	Witcher.displayInfo();
}