// Bank.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Account.h"
#include "Client.h"
#include "Manager.h"
#include "Maintainer.h"
#include "serializable.h"
using namespace std;

void startMenu(string &username, string &password, vector<Member> vMember);
void validate(string &username, string &password, vector<Member> vMember);
void optionMenu(Member &member);

int main()
{
	Client client;
	Account account("Savings", 1000);
	client.initialize("Pearson", "Radu", "pradu", "123", account);

	Manager manager;
	Account account2("Savings", 2000);
	manager.initialize("Delainha", "Radu", "dradu", "456", account2);

	Maintainer maintainer;
	Account account3("Savings", 3000);
	maintainer.initialize("Isabel", "Radu", "iradu", "789", account3);

	vector<Member> vMember;
	vMember.push_back(client);
	vMember.push_back(manager);
	vMember.push_back(maintainer);

	Serializable objSerial;
	objSerial.save(vMember);
	//vMember.clear();
	//vMember = objSerial.load();

	string username, password;
	startMenu(username, password, vMember);

	return 0;
}

void startMenu(string &username, string &password, vector<Member> vMember)
{
	cout << "--------------------------------------------------------------------------\n";
	cout << "                             Welcome To PR Bank\n";
	cout << "--------------------------------------------------------------------------\n" << endl;
	cout << " Please login to your account to begin." << endl;
	cout << " Username: ";
	cin >> username;
	cout << " Password: ";
	cin >> password;
	cout << endl;
	validate(username, password, vMember);
}

void validate(string &username, string &password, vector<Member> vMember)
{
	cout << "--------------------------------------------------------------------------\n";
	cout << "                            Searching for Account\n";
	cout << "--------------------------------------------------------------------------\n" << endl;
	int size = vMember.size();
	bool found = false;
	int element;
	for (int i = 0; i < size; i++)
	{
		if (vMember[i].getUsername() == username && vMember[i].getPassword() == password)
		{
			found = true;
			element = i;
			break;
		}
	}

	if (found)
	{
		cout << " We have found your account, " << vMember[element].getFirstname() << " " << vMember[element].getLastname() << "." <<endl << endl;
		vMember[element].printAccount();
	}
	else
	{
		cout << " Sorry, we were unable to find your account. Going back to main menu...\n" << endl;
		startMenu(username, password, vMember);
	}
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



