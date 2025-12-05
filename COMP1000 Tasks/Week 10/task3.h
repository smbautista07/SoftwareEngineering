#pragma once
#include <iostream>


class Address
{
public:
	std::string street;
	std::string city;
	std::string zip_code;

};

class Person
{
protected:
	std::string name;
	int age = 0;
	Address a;
public:
	Person(std::string name_in, int age_in, std::string street_in, std::string city_in, std::string zip_code_in)
	{
		name = name_in;
		age = age_in;
		a.street = street_in;
		a.city = city_in;
		a.zip_code = zip_code_in;
	}
	void display_info()
	{
		std::cout << "Name: "		<< name			<< "\n";
		std::cout << "Age: "		<< age			<< "\n";
		std::cout << "Street: "		<< a.street		<< "\n";
		std::cout << "City: "		<< a.city		<< "\n";
		std::cout << "Zip_code: "	<< a.zip_code	<< "\n";
	}
};

void task3()
{
	Person j = Person("John", 35, "Street 2", "City city", "Zipa");
	j.display_info();
}