/**
 * Created by: Pearson Radu
 * The Maintainer class is an inherited class from Member. This class holds a maintainers
 * data (like username, password and accounts). It also allows for additional maintainer
 * roles like turning execution trace on and off.
*/

#include "stdafx.h"
#include "Maintainer.h"
#include "Serializable.h"

Maintainer::Maintainer()
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
Maintainer::Maintainer(string firstname, string lastname, string username, string password, Account account)
{
	initialize(firstname, lastname, username, password, account);
}

Maintainer::~Maintainer()
{
}

/**
 * \brief 
 * Print Traces Function
 * Will print all recent traces, as long as there are some
 */
void Maintainer::printTrace()
{
	Serializable objSerial;
	vector<string> traces;
	objSerial.loadTrace(traces);

	cout << "--------------------------------------------------------------------------\n";
	cout << "                           System Functions Log" << endl;
	cout << "--------------------------------------------------------------------------\n" << endl;


	if (traces.size() == 0)
		cout << " Sorry, no traces of action have been executed yet." << endl;
	else
		for (size_t i = 0; i < traces.size(); i++)
			cout << traces[i] << endl;

	cout << endl;
}
