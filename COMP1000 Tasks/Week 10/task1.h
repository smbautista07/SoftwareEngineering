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
		std::cout << "Make:" << make << "\n";
		std::cout << "Model:" << model << "\n";
	}
};

class Car : Vehicle
{
protected:
	int number_of_doors;
public:
	Car(std::string make_in, std::string model_in, int number_of_doors_in):Vehicle(make_in, model_in)
	{
	//	Vehicle(make_in, model_in);
		number_of_doors = number_of_doors_in;
	}
	void displayInfo()
	{
		Vehicle::displayInfo();
		std::cout << "Number of Doors: " << number_of_doors << "\n";
	}
};

class Bike :Vehicle
{
protected:
	bool has_carrier;
public:
	Bike(std::string make_in, std::string model_in, bool has_carrier_in):Vehicle(make_in, model_in)
	{
		has_carrier = has_carrier_in;
	}
	void displayInfo()
	{
		Vehicle::displayInfo();
		std::cout << ((has_carrier) ? "It has a carrier" : "It does not have a carrier");
	}
};



void task1()
{
	/*Vehicle v = Vehicle("Toyota", "Prius");
	v.displayInfo();*/
	Car c = Car("Toyota", "Prius", 4);
	c.displayInfo();
	Bike b = Bike("Hi", "Test", true);
	b.displayInfo();
}