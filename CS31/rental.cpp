#include<iostream>
#include<string>
using namespace std;

int main()
{
	int odoStart, odoEnd;
	int distance;
	int rentDays;
	string name;
	string type;
	int month;
	double baseCharge;
	double additionalCharge;
	double charge;
	
	//input and check the variables
	cout << "Odometer at start: ";
	cin >> odoStart;
	if (odoStart < 0)
	{
		cout << "---\n";
		cout << "The starting odometer reading must be nonnegative.";
		return 1;
	}

	cout << "Odometer at end: ";
	cin >> odoEnd;
	if (odoEnd < odoStart)
	{
		cout << "---\n";
		cout << "The final odometer reading must be at least as large as the starting reading.";
		return 1;
	}

	cout << "Rental days: ";
	cin >> rentDays;
	if (rentDays <= 0)
	{
		cout << "---\n";
		cout << "The number of rental days must be positive.";
		return 1;
	}

	cout << "Customer name: ";
	cin.ignore(10000,'\n');
	getline(cin, name);
	if (name == "")
	{
		cout << "---\n";
		cout << "You must enter a customer name.";
		return 1;
	}
	
	cout << "Luxury car?(y/n): ";
	cin >> type;
	if (type != "y" && type != "n")
	{
		cout << "---\n";
		cout << "You must enter y or n.";
		return 1;
	}

	cout << "Month(1=Jan, 2=Feb, etc.): ";
	cin >> month;
	if (month < 1 || month > 12)
	{
		cout << "---\n";
		cout << "The month number must be in the range 1 through 12.";
		return 1;
	}

	//calculate the basic charge
	if (type == "n")
		baseCharge = 33.0 * rentDays;
	else
		baseCharge = 61.0 * rentDays;

	//calculate the additional charge
	distance = odoEnd - odoStart;
	if (distance <= 100)
		additionalCharge = 0.27 * distance;
	else if (distance <= 400 && month > 3 && month < 12)
		additionalCharge = 27.0 + 0.21 * (distance - 100);
	else if (distance <= 400)
		additionalCharge = 27.0 + 0.27 * (distance - 100);
	else if (month > 3 && month < 12)
		additionalCharge = 27.0 + 0.21 * 300 + 0.19 * (distance - 400);
	else
		additionalCharge = 27.0 + 0.27 * 300 + 0.19 * (distance - 400);

	charge = baseCharge + additionalCharge;
	cout.setf(ios::fixed);
	cout.precision(2);
	cout << "---\n";
	cout << "The rental charge for " << name << " is $" << charge << endl;
}