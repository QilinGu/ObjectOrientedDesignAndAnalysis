// Bank.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Account.h"
#include "Client.h"
#include "Manager.h"
#include "Maintainer.h"
using namespace std;

void startMenu(string &username, string &password);
void validate(string &username, string &password);
void optionMenu(Member &member);

int main()
{
	string username, password;

	startMenu(username, password);

    return 0;
}

void startMenu(string &username, string &password)
{
	cout << "--------------------------------------------------------------------------\n";
	cout << "                               Welcome To PR Bank\n";
	cout << "--------------------------------------------------------------------------" << endl;
	cout << "Please login to begin." << endl;
	cout << "Username: ";
	cin >> username;
	cout << "Password: ";
	cin >> password;

	validate(username, password);
}

void validate(string &username, string &password)
{
	Client client;
	client.setFirtname("Pearson");
	client.setLastname("Radu");
	client.setUsername("pradu");
	client.setPassword("123");
	Account account("Savings", 1000);
	client.addAccount(account);

	if (password == client.getPassword() && username == client.getUsername())
	{
		cout << "We have found your account" << endl;
		optionMenu(client);
	}
	else
		cout << "We cannot find your account" << endl;
}

void optionMenu(Member &member)
{
	cout << "--------------------------------------------------------------------------\n";
	cout << "                               Welcome To PR Bank\n";
	cout << "--------------------------------------------------------------------------" << endl;

	if (Client *client = (Client*)&member)
	{
		cout << "This is a client!" << endl;
	}

	if (Manager *manager = (Manager*)&member)
	{
		cout << "This is a manager!" << endl;
	}

	if (Maintainer *maintainer = (Maintainer*)&member)
	{
		cout << "This is a maintainer!" << endl;
	}
	
	cout << "This is the end!" << endl;
}



