#pragma once
#include <string>
#include "Account.h"
#include <iostream>
using namespace std;

class Member
{
	private:
	string firstname,lastname;
	string username;
	string password;

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
};

