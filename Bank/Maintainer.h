#pragma once
#include "Member.h"

class Maintainer : public Member
{
	public:
	Maintainer();
	Maintainer(string firstname, string lastname, string username, string password, Account account);
	~Maintainer();
	void printTrace();
};
