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
	vector<Account> payments;
	vector<Account*> linkedPayments;
	vector<string> transactions;

	public:
	Member();
	~Member();
	void initialize(string first, string last, string user, string pass, Account account);
	void checkPayment();
	void addPayment(string payment, double value);
	bool cancelPayment(string payment);
	void addAccount(Account account);
	bool deleteAccount(Account &account);
	Account *selectAccount(string option);
	vector<Account> getAccounts();
	vector<Account> getPayments();
	void setPayments(vector<Account> pays);
	vector<Account*> getLinkedPayments();
	void setLinkedPayments(vector<Account*> linkedPays);
	void printAccount();
	string getFirstname();
	void setFirtname(string first);
	string getLastname();
	void setLastname(string last);
	string getUsername();
	void setUsername(string user);
	string getPassword();
	void setPassword(string pass);
	vector<string> getTransactions();
	void addTransaction(string transaction);
};
