#pragma once
#include <iostream>

class Account
{
protected:
	int account_number;
	float balance;
public:
	void deposit(float value)
	{
		balance += value;
	}
	Account()
	{

	}
	Account(int account_number_in, float balance_in)
	{
		account_number = account_number_in;
		balance = balance_in;
	}
	void displayInfo()
	{
		std::cout << account_number << "\n";
		std::cout << balance << "\n";
	}
};

class SavingsAccount :Account
{
protected:
	float interest_rate; //decimal value not a percentage
public:
	SavingsAccount(int account_number_in, float balance_in, float interest_rate_in):Account(account_number_in, balance_in)
	{
		interest_rate = interest_rate_in;
	}
	void calculate_interest()
	{
		std::cout << balance * interest_rate;
	}
};

class Customer
{
private:
	std::string name;
	Account* acc_ptr;
public:
	Customer(std::string name_in)
	{
		name = name_in;
	}
	void setAccount(Account &acc_in)
	{
		//acc_in.displayInfo();
		acc_ptr = &acc_in;
	}
	void displayInfo()
	{
		std::cout << name << "\n";
		(*acc_ptr).displayInfo();
	}
};

void task4()
{
	SavingsAccount sa = SavingsAccount(124, 0.05, 0.0005);
	//sa.calculate_interest();

	Account a = Account(142, 332.2);
	a.displayInfo();
	
	Customer c = Customer("Joghn");
	c.setAccount(a);

	c.displayInfo();
	
	a.deposit(554.23);

	a.displayInfo();
	c.displayInfo();
}