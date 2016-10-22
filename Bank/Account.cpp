/**
 * Created by: Pearson Radu
 * The Account class will be an instance of an account for each member of the bank
 * It will allow the member to execute balance modifications and changes to their account
 */

#include "stdafx.h"
#include "Account.h"
#include <time.h>

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

// Got help from here to calculate difference between dates http://stackoverflow.com/questions/14218894/number-of-days-between-two-dates-c
int Account::payment()
{
	double difference = 0;
	struct tm currentTime = getTime();
	time_t y = mktime(&currentTime);
	time_t x;

	// If it is a credit account, get the credit date, else if it is a loan account get the loan date
	if (accountType == "Credit")
		x = mktime(&creditTime);
	else if (accountType == "Loan")
		x = mktime(&loanTime);
	else if (accountType != "Savings" && accountType != "Chequing")
		x = mktime(&creditTime);

	if (x != (time_t)(-1) && y != (time_t)(-1))
	{
		difference = difftime(y, x) / (60 * 60 * 24); // To test use only / 60 to calculate the minutes and change difference > 1 to test every minute
		//cout << ctime(&x);
		//cout << ctime(&y);
		//cout << "difference = " << difference << " days" << endl;
	}

	// Charge the credit account 10% x how every many monthly payments missed
	// Once the payment is charged the charge date is updated
	if ((difference / 30) >= 1 && accountType == "Credit")
	{
		if (balance != 0)
		{
			for (int i = 1; i <= floor(difference / 30); i++)
				balance *= 0.10;
		}

		creditTime = currentTime;
	}
	// Charge the loan account 15% if the balance once the year is up
	else if (accountType == "Loan")
	{
		if (balance != 0 && difference >= 365)
		{
			balance += (balance * 0.15);
			loanTime = currentTime;
		}
		//else if (balance != 0 && difference > 30)
			//balance += (balance * 0.5);
	}
	// Return how many missed payments there are and update the date
	else if ((difference / 30) >= 1 && accountType != "empty")
	{
		creditTime = currentTime;
		return floor(difference / 30);
	}

	return 0;
}

struct tm Account::getTime()
{
	struct tm newtime;
	__time64_t long_time;
	// Get time as 64-bit integer.
	_time64(&long_time);
	// Convert to local time.
	errno_t err = _localtime64_s(&newtime, &long_time);

	return newtime;
}

/**
 * \brief
 * Withdraw function for account
 * Takes a parameter value that is deducted (or added if the account is a loan or credit) from the account (if suitable)
 * \param value
 */
void Account::withdraw(double value)
{
	// Proceed with operations as long as the value is a positive number
	if (value > 0)
	{
		if (accountType == "Loan")
		{
			// If the value added to the balance is less than or equal to the original limit of the loan, proceed
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
			// If the value added to the balance is less than or equal to the original credit limit, proceed
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
			// If the withdrawn amount produces a negative balance, do not proceed
			if ((balance - value) < 0)
			{
				cout << "\n Sorry, this transaction could not be completed since this it will result\n in a negative balance in your account." << endl;
			}
			// If the value being withdrawn is taken from the chequing account, and the balance breaks the $1000 barrier, charge the user $2
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
			// Otherwise withdraw the money
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
 * Takes a parameter value that is added (or subtractred if the account is a loan or credit) to the account balance
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

/*Getter for credit limit*/
double Account::getCreditLimit()
{
	return creditLimit;
}

/*Setter for credit limit*/
void Account::setCreditLimit(double limit)
{
	creditLimit = limit;
}

/*Getter for credit time*/
struct tm Account::getCreditTime()
{
	return creditTime;
}

/*Setter for credit time*/
void Account::setCreditTime()
{
	creditTime = getTime();
}

/*Setter for credit time with parameter time*/
void Account::setCreditTime(struct tm time)
{
	creditTime = time;
}

/*Getter for loan limit*/
double Account::getLoanLimit()
{
	return loanLimit;
}

/*Setter for loan limit*/
void Account::setLoanLimit(double limit)
{
	loanLimit = limit;
}

/*Getter for loan time*/
struct tm Account::getLoanTime()
{
	return loanTime;
}

/*Setter for loan time*/
void Account::setLoanTime()
{
	loanTime = getTime();
}

/*Setter for loan time with parameter time*/
void Account::setLoanTime(struct tm time)
{
	loanTime = time;
}
