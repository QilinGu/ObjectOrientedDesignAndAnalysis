#pragma once
#include "Account.h"
#include <vector>
using namespace std;

class Member
{
	private:
	string firstname, lastname;
	string username;
	string password;
	vector<Account> accounts;

	public:
	Member();
	~Member();
	void initialize(string first, string last, string user, string pass, Account account);
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
	Account *selectAccount();
	vector<Account> getAccounts();
	void printAccount();
};
