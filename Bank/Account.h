#pragma once
#pragma warning(disable : 4996)
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
	struct tm creditTime = { 0,0,0,0,0,0 };
	double loanLimit = 0;
	struct tm loanTime = { 0,0,0,0,0,0 };
	struct tm getTime();

	public:
	Account(string account, double value);
	~Account();
	void checkPayment();
	string getAccountType();
	void setAccountType(string account);
	double getBalance();
	void setBalance(double value);
	double getCreditLimit();
	void setCreditLimit(double limit);
	struct tm getCreditTime();
	void setCreditTime();
	void setCreditTime(tm time);
	double getLoanLimit();
	void setLoanLimit(double limit);
	struct tm getLoanTime();
	void setLoanTime();
	void setLoanTime(tm time);
	void withdraw(double value);
	void deposit(double value);
	void transfer(double value, Account* account);
};
