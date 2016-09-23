#pragma once
#include <string>
#include <iostream>
using namespace std;

class Account
{
	private:
	string accountType;
	double balance;

	public:
	string getAccountType();
	void setAccountType(string account);
	double getBalance();
	void setBalance(double value);
	void withdraw(double value);
	void deposit(double value);
	void transfer(double value, Account account);
	void deleteAccount();
	
	Account(string account, double value);
	~Account();
};

