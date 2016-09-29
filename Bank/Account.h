#pragma once
#include <iostream>
#include <string>
using namespace std;

class Account
{
	private:
	string accountType;
	double balance;

	public:
	Account(string account, double value);
	~Account();

	string getAccountType();
	void setAccountType(string account);
	double getBalance();
	void setBalance(double value);
	void withdraw(double value);
	void deposit(double value);
	void transfer(double value, Account* account);
};
