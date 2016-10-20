/**
 * Created by: Pearson Radu
 * The Account class will be an instance of an account for each member of the bank
 * It will allow the member to execute balance modifications and changes to their account
 */

#include "stdafx.h"
#include "Account.h"

 /**
  * \brief
  * Account constructer
  * takes two parameters, one is the name of the account, the other is the balance of the account
  * \param account
  * \param value
  */
Account::Account(string account, double value)
{
	accountType = account;
	balance = value;
}

/* Account deconstructor*/
Account::~Account()
{
}

/**
 * \brief
 * Withdraw function for account
 * takes a parameter value that is deducted from the account (if suitable)
 * \param value
 */
void Account::withdraw(double value)
{
	if (value > 0)
	{
		if (accountType == "Loan")
		{
			if ((balance + value) <= loanLimit)
			{
				balance += value;
				cout << "\n Successfully withdrew $" << value << " from " << accountType << ".\n";
			}
			else
				cout << "\n Sorry, the deposit could not be processed because the balance of a loan\n account cannot be greater than the orignal loan limit." << endl;
		}
		else if (accountType == "Credit")
		{
			if ((balance + value) <= creditLimit)
			{
				balance += value;
				cout << "\n Successfully withdrew $" << value << " from " << accountType << ".\n";
			}
			else
				cout << "\n Sorry, the deposit could not be processed because the balance of a credit\n account cannot be greater than the orignal credit limit." << endl;
		}
		else
		{
			if ((balance - value) < 0)
			{
				cout << "\n Sorry, this transaction could not be completed since this it will result\n in a negative balance in your account." << endl;
			}
			else if ((balance - value) < 1000 && balance >= 1000 && accountType == "Chequing")
			{
				cout << "\n If you continue your " << getAccountType() << " account will have less than $1000 in it." << endl;
				cout << " If you proceed, we will deduct $2 from your " << getAccountType() << " account." << endl;
				cout << " Press 1 to proceed, anything else will stop this process: ";

				int answer;
				cin >> answer;

				if (answer == 1)
				{
					if ((balance - value) == 1)
					{
						cout << "\n Sorry, this transaction cannot be completed since this will result in a \n negative balance in your account if you accept the charges." << endl;
					}
					else
					{
						balance -= 2;
						balance -= value;
						cout << "\n Successfully withdrew $" << value << " from " << accountType << ".\n";
					}
				}
			}
			else
			{
				balance -= value;
				cout << "\n Successfully withdrew $" << value << " from " << accountType << ".\n";
			}
		}
	}
	else
		cout << "\n Sorry, the value $" << value << " cannot be withdrawn." << endl;

}

/**
 * \brief
 * Deposit function for account
 * takes parameter value that is added to the account balance or subtracted (if the account is a loan or credit)
 * \param value
 */
void Account::deposit(double value)
{
	if (value > 0)
	{
		if ((accountType == "Loan" || accountType == "Credit") && (balance - value) >= 0)
		{
			balance -= value;
			cout << "\n Successfully deposited $" << value << " to " << accountType << ".\n";
		}
		else
			cout << "\n Sorry, the value $" << value << " cannot be deposited.\n Payments to this account cannot go below $0." << endl;

		if (accountType == "Savings" || accountType == "Chequing")
		{
			balance += value;
			cout << "\n Successfully deposited $" << value << " to " << accountType << ".\n";
		}
	}
	else
		cout << "\n Sorry, the value $" << value << " cannot be deposited." << endl;
}

/**
 * \brief
 * Transfer function for account
 * Takes parameter value, which is deducted from the account and moved to another account
 * \param value
 * \param account
 */
void Account::transfer(double value, Account *account)
{
	if (this == account)
		cout << "\n Sorry, you are unable to transfer funds to the same account." << endl;
	else
	{
		withdraw(value);
		account->deposit(value);
	}
}

/*Getter for account type*/
string Account::getAccountType()
{
	return accountType;
}

/*Setter for account type*/
void Account::setAccountType(string account)
{
	accountType = account;
}

/*Getter for account balance*/
double Account::getBalance()
{
	return balance;
}

/*Setter for account balance*/
void Account::setBalance(double value)
{
	balance = value;
}

double Account::getCreditLimit()
{
	return creditLimit;
}

void Account::setCreditLimit(double limit)
{
	creditLimit = limit;
}

double Account::getLoanLimit()
{
	return loanLimit;
}

void Account::setLoanLimit(double limit)
{
	loanLimit = limit;
}
