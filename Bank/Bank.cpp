// Bank.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

bool login();

int main()
{
	bool entry = login();
	cout << entry << endl;

	return 0;
}

bool login()
{
	ifstream readFile("userdata.txt");
	string username, password;
	string userEnter, passEnter;
	bool found = false;

	while (!found)
	{
		cout << "Enter username: ";
		cin >> username;

		cout << "Enter password: ";
		cin >> password;

		if (!readFile.is_open())
			readFile.open("userdata.txt");

		string line = " ";
		while (getline(readFile, line))
		{

			stringstream readLine(line);
			readLine >> userEnter >> passEnter;

			if (username == userEnter && password == passEnter)
			{
				cout << "Login Successfully!" << endl;
				found = true;
				break;
			}
		}

		readFile.close();
	}

	if (found)
		return true;
	else
		return false;
}

