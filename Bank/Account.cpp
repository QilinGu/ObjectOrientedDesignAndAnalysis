/*
	Created by: Pearson Radu
	The Account class will be an instance of an account for each member of the bank
	It will allow the member to execute balance modifications and changes to their account
*/

#include "stdafx.h"
#include "Account.h"

/*
	Account constructer
	Takes two parameters, one is the name of the account, the other is the balance of the account
*/
Account::Account(string account, double value)
{
	accountType = account;
	balance = value;
}

/* Account deconstructor*/
Account::~Account()
{
}

/*
	Delete function for account
	Deletes this Account if the balance is equal to 0
*/
void Account::deleteAccount()
{
	if (balance == 0)
	{
		cout << "This account has been deleted." << endl;
		delete this;
	}
	else
		cout << "Sorry, this account cannot be deleted since it's balance is not zero." << endl;
}

/*
	Withdraw function for account
	Takes a parameter value that is deducted from the account (if suitable)
*/
void Account::withdraw(double value)
{
	if ((balance - value) < 0)
	{
		cout << "Sorry, this transaction cannot be completed since this it will result in a negative balance in your account." << endl;
	}
	else if ((balance - value) == 1)
	{
		cout << "Sorry, this transaction cannot be completed since this will result in a negative balance in your account if you accept the charges." << endl;
	}
	else if ((balance - value) < 1000)
	{
		cout << "If you make this transaction your " << getAccountType() << " account will have less than $1000 in it." << endl;
		cout << "If you continue, we will deduct $2 from your " << getAccountType() << " account." << endl;
		cout << "Press 1 to proceed, anything else will stop this process" << endl;

		int answer;
		cin >> answer;

		if (answer == 1)
		{
			balance -= 2;
			balance -= value;
		}
	}
	else
		balance -= value;
}

/*
Deposit function for account
Takes parameter value that is added to the account
*/
void Account::deposit(double value)
{
	if (value > 0)
		balance += value;
	else
		cout << "Sorry, the value " << value << " cannot be deposited." << endl;
}

/*
Transfer function for account
Takes parameter value, which is deducted from the account and moved to another account
*/
void Account::transfer(double value, Account account)
{
	/*
		N
		E
		E
		D
		S

		T
		O

		B
		E

		I
		M
		P
		L
		E
		M
		E
		N
		T
		E
		D
	*/
}

/*Getter for account type*/
string Account::getAccountType()
{
	return accountType;
}

/*Setter for account type*/
void Account::setAccountType(string account)
{
	accountType = account;
}

/*Getter for account balance*/
double Account::getBalance()
{
	return balance;
}

/*Setter for account balance*/
void Account::setBalance(double value)
{
	balance = value;
}

