/**
 * Created by: Pearson Radu
 * The Client class is an inherited class from Member. This class holds a clients data
 * (like username, passwords and accounts).
 */

#include "stdafx.h"
#include "Client.h"

Client::Client()
{
}

/**
 * \brief
 * Constructor that will call initializer from Member parent class
 * \param firstname
 * \param lastname
 * \param username
 * \param password
 * \param account
 */
Client::Client(string firstname, string lastname, string username, string password, Account account)
{
	initialize(firstname, lastname, username, password, account);
}

Client::~Client()
{
}
