#pragma once
#include <iostream>

class Animal
{
public:
	virtual void speak()
	{
		std::cout << "Animal sound" << "\n";
	}
};

class Cat:Animal
{
public:
	void speak()
	{
		std::cout << "Meow" << "\n";
	}
	Cat()
	{

	}
};

class Dog:Animal
{
public:
	void speak()
	{
		std::cout << "Woof" << "\n";
	}
};

void task2()
{
	Cat c = Cat();
	Dog d = Dog();
	c.speak();
	d.speak();
}