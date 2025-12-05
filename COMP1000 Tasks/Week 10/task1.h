#pragma once
#include <iostream>


class Vehicle
{
protected:
	std::string make;
	std::string model;
public:
	Vehicle(std::string make_in, std::string model_in)
	{
		make = make_in;
		model = model_in;
	}
	virtual void displayInfo()
	{
		std::cout << "Make:" << make << " Model:" << model;
	}
};

class Car : Vehicle
{
protected:
	int number_of_doors;
public:
	Car(std::string make_in, std::string model_in, int number_of_doors_in):Vehicle
	{
	//	Vehicle(make_in, model_in);
		number_of_doors = number_of_doors_in;
	}
};

void task1()
{
	Vehicle v = Vehicle("Toyota", "Prius");
	v.displayInfo();
	Car c = Car
}