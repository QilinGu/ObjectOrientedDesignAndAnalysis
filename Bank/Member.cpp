#include "stdafx.h"
#include "Member.h"

	/*
		Member Constructor
		This will ask the user for their first and last name, username and password
	*/
	Member::Member()
	{
		cout << "Please enter the member's first name: ";
		cin >> firstname;
		cout << "Please enter the member's last name: ";
		cin >> lastname;
		cout << "Please enter the member's username: ";
		cin >> username;
		cout << "Please enter the member's password: ";
		cin >> password;
	}

	Member::~Member()
	{
	}

	/*Getter for firstname*/
	string Member::getFirstname()
	{
		return firstname;
	}

	/*Setter for firstname*/
	void Member::setFirtname(string first)
	{
		firstname = first;
	}

	/*Getter for lastname*/
	string Member::getLastname()
	{
		return lastname;
	}

	/*Setter for lastname*/
	void Member::setLastname(string last)
	{
		lastname = last;
	}

	/*Getter for username*/
	string Member::getUsername()
	{
		return username;
	}

	/*Setter for username*/
	void Member::setUsername(string user)
	{
		username = user;
	}

	/*Getter for password*/
	string Member::getPassword()
	{
		return password;
	}

	/*Setter for password*/
	void Member::setPassword(string pass)
	{
		password = pass;
	}
