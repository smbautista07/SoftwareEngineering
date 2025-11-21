#include <iostream>
using namespace std;
class Student
{
private:
	string name;
	int age;
	char grade;
public:
	Student()
	{
	}
	void setName(string name_in)
	{
		name = name_in;
	}
	string getName()
	{
		return name;
	}
	void setAge(int age_in)
	{
		age = age_in;
	}
	int getAge()
	{
		return age;
	}
	void setGrade(char grade_in)
	{
		grade = grade_in;
	}
	char getGrade()
	{
		return grade;
	}
	
};

void task2()
{

	Student Jimmy = Student();
	Jimmy.setAge(4939);
	Jimmy.setGrade('F');
	Jimmy.setName("Jimmy");
	cout << "Name: " << Jimmy.getName() << "\n";
	cout << "Age: " << Jimmy.getAge()<< "\n";
		cout << "Grade: " << Jimmy.getGrade() << "\n";
}