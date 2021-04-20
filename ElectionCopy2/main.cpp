#include "Menu.h"
 #include <map>

int main() {
	
	homePage();
}

void homePage() {
	int choise;
	printHomeChoise();
	cin >> choise;
	system("cls");
	switch (choise)
	{
	case One:
		newElection();
		break;
	case Two:
		loadElection();
		break;
	default:
		cout << "Good bye" << endl;
		break;
	}
}

void printHomeChoise()
{
	cout << "* * * * * * * * * * * * * * * * * *" << endl;
	cout << "* Please choose :                 *" << endl;
	cout << "* 1.New Election.                 *" << endl;
	cout << "* 2.Load Election.                *" << endl;
	cout << "* For exit(press 3-9).            *" << endl;
	cout << "* * * * * * * * * * * * * * * * * *" << endl;
}

void loadElection() {
	char path[MAX_SIZE];
	ifstream file;
	cin.ignore();
	cout << "Please enter File path:  ";
	cin.getline(path, MAX_SIZE);
	try{
	file.open(path, ios::binary);
	if (!file.is_open()) {
		throw "File couldn't be open";
		exit(1);
	}
	Menu m1(file);
	m1.ElectionMenu();				 
	}
	catch (const char* msg)
	{
		cout << "ERROR :" << msg << endl;
	}
	catch (const std::exception& e)
	{
		cout << "Error :" << e.what();
	}
	catch (...)
	{
		cout << "Unexpected Error occurred";
	}
	file.close();
}

void newElection() {
	int choise;
	int day, month, year;
	bool isGood = false;
	do {
		cout << "Please enter election Date(Day/Month/year): ";
		cin >> day >> month >> year;
		try {
			checkDate(day, month, year); 
			isGood = true;
		}
		catch (const char* exception)
		{
			cout << "ERROR :" << exception << endl;
			isGood = false;
		}
	} while (!isGood);
	chooseRound();
	cin >> choise;
	if (choise == Simple)
	{
		int repNum;
		cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl;
		cout << "* Choose number of representatives in all election round :  *" << endl;
		cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl;
		try
		{
		cin >> repNum;
		if (repNum <= Zero)
			throw "The District number of Representatives must be bigger then zero";
			Menu m1(repNum);
			m1.SetDate(day, month, year);
			m1.ElectionMenu();
		}
		catch (const char* exception)
		{
			cout << "ERROR :" << exception << endl;
			Sleep(5000);
		}
		catch (const std::exception& ex)
		{
			cout << ex.what() << endl;
			Sleep(5000);
		}
	}
	else
	{
		try
		{
			Menu m1;
			m1.SetDate(day, month, year);
			m1.ElectionMenu();
		}
		catch (const char* error)
		{
			cout << "ERROR :" << error << endl;
			Sleep(5000);
		}
	}
}

void chooseRound()
{
	system("cls");
	cout << "* * * * * * * * * * * * * * * * * *" << endl;
	cout << "* Please choose election round :  *" << endl;
	cout << "* 1.Simple round.                 *" << endl;
	cout << "* 2.Regular round.                *" << endl;
	cout << "* * * * * * * * * * * * * * * * * *" << endl;
}

void checkDate(int day, int month, int year) {
	if (year <= 0)
		throw "You entered illegal year number!";
	switch (month)
	{
	case January:
		if (day < 0 || day>31)
			throw "Number of day in January must be between between 1 to 31";
		break;
	case February:
		if (day < 0 || day>28)
			throw "Number of day in February must be between between 1 to 28";
		break;	
	case March:
		if (day < 0 || day>31)
			throw "Number of day in March must be between between 1 to 31";
		break;
	case April:
		if (day < 0 || day>30)
			throw "Number of day in April must be between between 1 to 30";
		break;
	case May:
		if (day < 0 || day>31)
			throw "Number of day in May must be between between 1 to 31";
		break;
	case June:
		if (day < 0 || day>30)
			throw "Number of day in June must be between between 1 to 30";
		break;
	case July:
		if (day < 0 || day>31)
			throw "Number of day in July must be between between 1 to 31";
		break;
	case August:
		if (day < 0 || day>31)
			throw "Number of day in August must be between between 1 to 31";
		break;
	case September:
		if (day < 0 || day>30)
			throw "Number of day in September must be between between 1 to 30";
		break;
	case October:
		if (day < 0 || day>31)
			throw "Number of day in October must be between between 1 to 31";
		break;
	case November:
		if (day < 0 || day>30)
			throw "Number of day in November must be between between 1 to 30";
		break;
	case December:
		if (day < 0 || day>31)
			throw "Number of day in December must be between between 1 to 31";
		break;
	default:
		throw "Illegel month number";
		break;
	}
}