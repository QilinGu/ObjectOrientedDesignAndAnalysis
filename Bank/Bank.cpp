// Bank.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Account.h"
#include "Client.h"
#include "Manager.h"
#include "Maintainer.h"
using namespace std;

int main()
{
	Client client;
	cout << client.getFirstname() << endl;
	cout << client.getLastname() << endl;
	cout << client.getUsername() << endl;
	cout << client.getPassword() << endl;

	Manager manager;
	cout << manager.getFirstname() << endl;
	cout << manager.getLastname() << endl;
	cout << manager.getUsername() << endl;
	cout << manager.getPassword() << endl;

	Maintainer maintainer;
	cout << maintainer.getFirstname() << endl;
	cout << maintainer.getLastname() << endl;
	cout << maintainer.getUsername() << endl;
	cout << maintainer.getPassword() << endl;

    return 0;
}

