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
	Manager manager;
	cout << manager.getFirstname() << endl;
	cout << manager.getLastname() << endl;
	cout << manager.getUsername() << endl;
	cout << manager.getPassword() << endl;

    return 0;
}

