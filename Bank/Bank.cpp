// Bank.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Account.h"
using namespace std;

int main()
{
	Account account("Checking", 6000);

	account.deposit(-50);
	cout << account.getBalance() << endl;
	
	
    return 0;
}

