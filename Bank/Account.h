#pragma once
#include <iostream>
#include <string>
using namespace std;

class Account
{
	private:
	string accountType;
	double balance;
	double limit;
	double creditLimit = 0;
	double loanLimit = 0;

	public:
	Account(string account, double value);
	~Account();

	string getAccountType();
	void setAccountType(string account);
	double getBalance();
	void setBalance(double value);
	double getCreditLimit();
	void setCreditLimit(double limit);
	double getLoanLimit();
	void setLoanLimit(double limit);
	void withdraw(double value);
	void deposit(double value);
	void transfer(double value, Account* account);
};
