#pragma once
#include <string>
#include "Account.h"
#include <iostream>
#include <vector>
using namespace std;

class Member
{
	private:
	string firstname,lastname;
	string username;
	string password;
	vector<Account> accounts;

	public:
	Member();
	~Member();
	string getFirstname();
	void setFirtname(string first);
	string getLastname();
	void setLastname(string last);
	string getUsername();
	void setUsername(string user);
	string getPassword();
	void setPassword(string pass);
	void addAccount(Account account);
	void removeAccount(Account account);
	void printAccount();
};

