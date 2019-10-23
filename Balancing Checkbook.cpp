// kk4036_hw12_using_Overload_Op.cpp
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

class Money
{
	double moneyAmount;

public:
	// Default Constructor
//	Money (): moneyAmount (0.00) {}
//	Money (double newAmount): moneyAmount(newAmount) {}

	// Overload Constructor w/ parameters
	Money(double newAmount = 0.00) : moneyAmount(newAmount) {}

	// setter functions
	void set_moneyAmount(double newAmount) { moneyAmount = newAmount; }

	// getter functions
	double get_moneyAmount() const { return moneyAmount; }

	friend class Check;

	// OVERLOADING OPERATORS
	// overloading << operator so it can be used to output values of type Money
	friend ostream &operator<<(ostream &out, const Money &amount);

	// overloading >> operator so it can be used to input values of type Money
	friend istream &operator>>(istream &in, Money &amount);

	// overloading += operator 
	Money operator+=(const Money &rhs);

	// overloading == opeartor
	friend bool operator==(const Money &lhs, const Money &rhs);

	// overloading + operator
	friend Money operator+(const Money &lhs, const Money &rhs);

	// overloading - operator
	friend Money operator-(const Money &lhs, const Money &rhs);

};

ostream &operator<<(ostream &out, const Money &amount) {
	out << '$' << fixed << setprecision(2) << amount.moneyAmount;
	// if not a friend function
	//out << '$' << fixed << setprecision(2) << amount.get_moneyAmount;
	return out;
}

istream &operator>>(istream &in, Money &amount) {
	in >> amount.moneyAmount;
	// if not a friend function
	//in >> amount.get_moneyAmount;
	return in;
}

Money Money::operator+=(const Money &rhs) {
	this->moneyAmount += rhs.moneyAmount;
	return *this;
}

bool operator==(const Money &lhs, const Money &rhs) {
	return (lhs.moneyAmount == rhs.moneyAmount);
}

Money operator+(const Money &lhs, const Money &rhs) {
	return (lhs.moneyAmount + rhs.moneyAmount);
	// if not a friend function
	// return (lhs.get_moneyAmount + rhs.get_moneyAmount);
}

Money operator-(const Money &lhs, const Money &rhs) {
	return (lhs.moneyAmount - rhs.moneyAmount); 
	// if not a friend function
	// return (lhs.get_moneyAmount - rhs.get_moneyAmount);
}

class Check
{
	int checkNum;
	Money checkAmount;
	bool checkCashed;

public:
	// Defalut Constructor
//	Check() : checkNum(0), checkAmount(Money(0.00)), checkCashed(false) {}
//	Check(int newCheckNum, Money newCheckAmount, bool newCheckCashed) :
//		checkNum(newCheckNum), checkAmount(newCheckAmount), checkCashed(newCheckCashed) {}

	// Overload Constructor w/ parameters
	Check(int newCheckNum = 0, Money newCheckAmount = 0.00, bool newCheckCashed = false) :
		checkNum(newCheckNum), checkAmount(newCheckAmount), checkCashed(newCheckCashed) {}

	// setter functions
	void set_checkNum(int newCheckNum) { checkNum = newCheckNum; }
	void set_checkAmount(Money newCheckAmount) { checkAmount = newCheckAmount; }
	void set_checkCashed(bool newCheckCashed) { checkCashed = newCheckCashed; }

	// getter functions
	int get_checkNum() const { return checkNum; }
	Money get_checkAmount() const { return checkAmount; }
	bool get_checkCashed() const { return checkCashed; }

	// overloading < operator for the std::sort function
	friend bool operator<(const Check &check1, const Check &check2);

	// additional print check function
	void print_check() const;

	/*// Swap Check function for Sorting - must pass objects as references
	friend void swap(Check& a, Check& b) {
		Check temp = a;
		a = b;
		b = temp;
	}

	// Bubble Sorting member function - must pass the vector as a reference
	friend void bubbleSort(vector<Check> &checkVec) {
		bool swapped = false;
		for (unsigned int i = 0; i < checkVec.size(); i++) {
			for (unsigned int j = 0; j < checkVec.size()-i-1; j++) {
				if (checkVec[j].get_checkNum() > checkVec[j + 1].get_checkNum()) {
					swap(checkVec[j], checkVec[j + 1]);
					//Check temp = checkVec[j + 1];
					//checkVec[j + 1] = checkVec[j];
					//checkVec[j] = temp;
					swapped = true;
				}
			}
			if (swapped == false)
				break;
		}
	}*/
};

bool operator<(const Check &check1, const Check &check2) {
	return (check1.checkNum < check2.checkNum);
}

void Check::print_check() const {
	cout << "Check #" << checkNum << ":\t\t$" << fixed << setprecision(2) << checkAmount.get_moneyAmount();
	if (checkCashed) { cout << " (cashed)" << endl; }
	else { cout << " (not cashed)" << endl; }
}

int main()
{
	Money oldBal;
	cout << "Please input your old account balance (e.g. $510.90): $";
	cin >> oldBal;							// need to overload >> operator
	cout << endl;							


	bool noMore = false;
	int i = 1;
	int checkNum;
	Money checkAmount;
	char yesOrNo;
	bool checkCashed;
	Money sumCashedChecks = 0.00;
	Money sumUncashedChecks = 0.00;
	vector<Check> checkVec;

	while (!noMore) {
		cout << "Check # " << i++ << ": " << endl;
		cout << "Enter the number of the check: #";
		cin >> checkNum;
		cout << "Enter the amount of the check: $";
		cin >> checkAmount;						// using the overloaded >> operator
		cout << "Was the check cashed (y/n)? ";
		cin >> yesOrNo;
		if (yesOrNo == 'Y' || yesOrNo == 'y') {
			sumCashedChecks += checkAmount;     // need to overload += operator
			checkCashed = true;
		}
		else {
			sumUncashedChecks += checkAmount;   // using the overloaded += operator
			checkCashed = false;
		}

		checkVec.push_back(Check(checkNum, checkAmount, checkCashed));
		cout << endl;

		cout << "Would you like to add another check (y/n): ";
		cin >> yesOrNo;
		if (yesOrNo == 'N' || yesOrNo == 'n') {
			noMore = true;
		}
		cout << endl;
	}

	cout << "Please add your bank deposits.  Enter each deposit on a separate line, \n";
	cout << "followed by a deposit of '0.00' or '0' to stop. \n";

	Money deposit;
	Money sumDeposits = 0.00;				// using default overloaded = operator
	noMore = false;
	while (!noMore) {
		cin >> deposit;
		if (deposit == 0.00 || deposit == 0)	// need to overload == operator
			noMore = true;
		else
			sumDeposits += deposit;			// using overloaded += operator
	}
	cout << endl;

	cout << "====================================================================" << endl;

	Money newBal = oldBal + sumDeposits - sumCashedChecks;	// must overload + & - operators
	Money pendBal = newBal - sumUncashedChecks;		// using overloaded + and - operators
	Money balDiff = newBal - pendBal;				// using overloaded + and - operators
	cout << "Old Balance: \t\t" << oldBal << endl;	// using overloaded << operator
	cout << "New Balance: \t\t" << newBal << endl;
	cout << "Pending Balance: \t" << pendBal << endl;
	cout << "Balance Difference: \t" << balDiff << endl;
	cout << "Total Amount Cashed: \t" << sumCashedChecks << endl;
	cout << "Total Amount Deposited: " << sumDeposits << endl;
	cout << endl;

	// bubble sorting checks by checkNum
	// bubbleSort(checkVec);

	// Sorting
	sort(checkVec.begin(), checkVec.end());
	//sort(checkVec.begin(), checkVec.end(), [](const Check& lhs, const Check& rhs) {
	//	return lhs.get_checkNum() < rhs.get_checkNum(); });

	cout << "Cashed Checks: \n";
	for (unsigned int i = 0; i < checkVec.size(); i++) {
		if (checkVec[i].get_checkCashed() == true)
			checkVec[i].print_check();
	}
	cout << endl;

	cout << "Uncashed Checks: \n";
	for (unsigned int i = 0; i < checkVec.size(); i++) {
		if (checkVec[i].get_checkCashed() == false)
			checkVec[i].print_check();
	}

	return 0;
}
