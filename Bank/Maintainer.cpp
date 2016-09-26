/*
Created by: Pearson Radu
The Maintainer class is an inherited class from Member. This class holds a maintainers
data (like username, password and accounts). It also allows for additional maintainer
roles like turning execution trace on and off.
*/

#include "stdafx.h"
#include "Maintainer.h"

Maintainer::Maintainer()
{
}

Maintainer::Maintainer(string firstname, string lastname, string username, string password, Account account)
{
	initialize(firstname, lastname, username, password, account);
}

Maintainer::~Maintainer()
{
}
