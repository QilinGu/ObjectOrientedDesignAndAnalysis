// Bank.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Account.h"
#include "Client.h"
using namespace std;

int main()
{
	Client client;
	cout << client.getFirstname() << endl;
	cout << client.getLastname() << endl;
	cout << client.getUsername() << endl;
	cout << client.getPassword() << endl;
    return 0;
}

