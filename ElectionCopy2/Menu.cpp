#include "Menu.h"


Menu::Menu()
{
	try
	{
		election = new Election();
	}
	catch (std::bad_alloc& ex)
	{
		cout << ex.what() << endl;
		exit(1);
	}
}

Menu::Menu(ifstream& file)
{
	int type,repNum;
	delete election;
	Date date(file);
	file.read(rcastc(&type), sizeof(ElectionType));
	if (type == Simple)
	{
		file.read(rcastc(&repNum), sizeof(int));
		try
		{
			election = new simpleElection(date,repNum);
		}
		catch (std::bad_alloc& ex)
		{
			cout << ex.what() << endl;
			exit(1);
		}
	}
	else{
		try
		{
		election = new Election();
		}
		catch (std::bad_alloc& ex)
		{
		cout << ex.what() << endl;
		exit(1);
		}
	}

	election->loadDistricts(file);
	election->loadParties(file);
	election->loadResults(file);
}

Menu::Menu(int numOfReps)
{
	if (numOfReps < 1)
		throw "Number of representatives is not possible";
	try
	{
		election = new simpleElection(numOfReps);
	}
	catch (std::bad_alloc& ex)
	{
		cout << ex.what() << endl;
		exit(1);
	}
}

bool Menu::SetDate(int day, int month, int year)
{
	election->getDateOfElection().setDay(day);
	election->getDateOfElection().setMonth(month);
	election->getDateOfElection().setYear(year);
    return true;
}

void Menu::navigator(int choise)
{
	switch (choise)
	{
	case One:
		if (typeid(*election) == typeid(simpleElection)) {
			throw "You can't add District because it is a simple Election";
		}
		else addDistrict();
		break;
	case Two:
		addCitizen();
		break;
	case Three:
		addParty();
		break;
	case Four:
		addRepresentative();
		break;
	case Five:
		showAllDistricts();
		break;
	case Six:
		showAllCitizens();
		break;
	case Seven:
		showAllParties();
		break;
	case Eight:
		vote();
		break;
	case Nine:
		election->showElectionResults();
		break;													 
	case Ten:
		cout << "Thank you, goodbye" << endl;
		break;
	case Eleven:
		saveElectionRound();
		break;
	case Twelve:
		loadElectionRound();
		break;
	default:
		cout << "Wrong input! Please enter a number between 1 - 12" << endl;
		Sleep(2000);
		break;
	}
}

void Menu::printMenu()
{
	cout << "* * * * * * * * * * * * * * *" << endl;
	cout << "* Please choose action:     *" << endl;
	cout << "* 1.Add New District        *" << endl;
	cout << "* 2.Add new Citizen         *" << endl;
	cout << "* 3.Add new Party           *" << endl;
	cout << "* 4.Add new Representative  *" << endl;
	cout << "* 5.Show all Districts      *" << endl;
	cout << "* 6.Show all Citizens       *" << endl;
	cout << "* 7.Show all Parties        *" << endl;
	cout << "* 8.Vote                    *" << endl;
	cout << "* 9.Election Results        *" << endl;
	cout << "* 10.Exit                   *" << endl;
	cout << "* 11.Save Election          *" << endl;
	cout << "* 12.Load Election          *" << endl;
	cout << "* * * * * * * * * * * * * * *" << endl;
}

void Menu::ElectionMenu()
{
	int choise;
	do {
		system("cls");
		printMenu();
		cin >> choise;
		system("cls");
		try { 
			navigator(choise); 
		}
		catch (const char* error)
		{
			cout << "ERROR :" << error << endl;
			Sleep(2000);
		}
		catch (const string error)
		{
			cout << "ERROR :" << error << endl;
			Sleep(2000);
		}
	} while (choise != 10 && !cin.fail());
	if (cin.fail())
		throw "You put worng input";
}

bool Menu::checkDis(int disNumber)
{
	if (disNumber > election->getDistrictList().getlSize())
		throw "This District is not exists";
	return true;
}

void Menu::addDistrict()
{
	char name[MAX_SIZE];
	int repNumber;
	bool isShared;
	cin.ignore();
	cout << "Please enter the name of the district: ";
	cin.getline(name, MAX_SIZE);
	cout << "Please enter the number of Representatives : ";
	cin >> repNumber;
	cout << "Is this District is Union or shared District(Select 0 for Union,1 for shared): ";
	cin >> isShared;//0 is false,1 is true
	if (repNumber <= Zero)
		throw "The District number of Representatives must be bigger then zero";
	election->addDistrict(name, repNumber,isShared);
}

void Menu::addCitizen()
{
	char name[MAX_SIZE];
	string id;
	int yearOfBirth, disNumber;
	const Citizen* citilocation;
	cin.ignore();
	cout << "Please enter citizen name: ";
	cin.getline(name, MAX_SIZE);
	cout << "Please enter citizen ID (10 digits MAX) : ";
	cin >> id;
	if (id.size() != 9) 
		throw "Id number has to be 9 digits";
	cout << "Please enter citizen Year of Birth: ";
	cin >> yearOfBirth;
	cout << "Please enter citizen district number: ";
	cin >> disNumber;
	if ((election->getDateOfElection().getYear() - yearOfBirth) < 18)
		throw "This Citizen is not allowed to vote, too young";

	if (typeid(*election) == typeid(simpleElection))
	{
		citilocation = election->findCitizen(id);
		if (citilocation != nullptr)
			throw "This Citizen is already exists";

		election->addCitizen(name, id, yearOfBirth, One);
	}
	else
	{
		(checkDis(disNumber));
		citilocation = election->findCitizen(id);
		if (citilocation != nullptr)
			throw "This Citizen is already exists";

		election->addCitizen(name, id, yearOfBirth, disNumber);
	}
}

void Menu::addParty()
{
	string name;
	string presidentId;
	cin.ignore();
	cout << "Please Enter the Party Name:";
	cin >> name;
	cout << "Please Entere the ID:";
	cin >> presidentId;
	findParty(name);
	const Citizen* president = election->findCitizen(presidentId);
	if (president == nullptr)
		throw "This citizen was not found";
	findRep(presidentId);
	election->addParty(name, president);
}

void Menu::addRepresentative()
{
	string id;
	int partyNumber;
	int disNumber;
	cin.ignore();
	cout << "Please enter Representative ID: ";
	cin >> id;
	cout << "Please entere Representative party number: ";
	cin >> partyNumber;
	cout << "Please enter Representative district number: ";
	cin >> disNumber;
	if (partyNumber > election->getPartyList().getlSize())
		throw "This party does not exist";

	const Citizen* rep = election->findCitizen(id);
	if (rep == nullptr)
		throw "This citizen was not found";

	findRep(id);
	if (typeid(*election) == typeid(simpleElection))
	{
		election->addRep(partyNumber, rep, One);
	}
	else
	{
		election->addRep(partyNumber, rep, disNumber);
	}

}

void Menu::showAllDistricts()
{
	election->printDistrictList();
}

void Menu::showAllCitizens()
{
	election->printCitizenList();
}

void Menu::showAllParties()
{
	election->printPartyList();
}

void Menu::vote()
{
	int partyNumber;
	string idNumber;
	Citizen* citizen;
	cout << "Please Enter your ID number:";
	cin >> idNumber;
	cout << "Please Enter Party number you vote for:";
	cin >> partyNumber;
	citizen = election->findCitizen(idNumber);
	if (citizen == nullptr)
		throw "This Citizen was not found!";

	citizen->getVote();

	if (partyNumber > election->getPartyList().getlSize())
		throw "This party is not exist";

	election->addVote(citizen->getDisNum(), &election->getPartyList()[partyNumber - 1]);
	citizen->setVote(true);
}

bool Menu::findParty(const string& name)
{
	for (int i = 0; i < election->getPartyList().getlSize(); i++) {
		if (name== election->getPartyList()[i].getPartyName())
			throw "This party already exist";
	}
    return false;
}

bool Menu::findRep(const string& id)
{
	return election->getPartyList().CheckRep(id);

}

void Menu::saveElectionRound()const
{
	int type;
	char path[MAX_SIZE];
	cin.ignore();
	cout << "Please enter File path:  ";
	cin.getline(path, MAX_SIZE);
	ofstream file(path, ios::binary);
	if (!file) {
		exit(1);
	}
	election->getDateOfElection().saveDate(file);
	if(!file.good())
		throw "problem occurred while loading data from the file";

	else if (typeid(*election) == typeid(simpleElection)) {
		int sizeOfReps = election->getDistrict(One).getNumOfRep();
		type = Simple;
		file.write(rcastcc(&type), sizeof(Simple));
		file.write(rcastcc(&sizeOfReps), sizeof(int));
		}
		else {
		type = Regular;
		file.write(rcastcc(&type), sizeof(Regular));
		}
		election->saveElection(file);

	file.close();
}

void Menu::loadElectionRound()
{
	char path[MAX_SIZE];
	int type,repNum;
	cin.ignore();
	cout << "Please enter File path:  ";
	cin.getline(path, MAX_SIZE);
	ifstream file(path, ios::binary);
	delete election;
	Date date(file);
	file.read(rcastc(&type), sizeof(ElectionType));
	if (type == Simple){
		file.read(rcastc(&repNum), sizeof(int));
		try
		{
			election = new simpleElection(date,repNum);
		}
		catch (std::bad_alloc& ex)
		{
			cout << ex.what() << endl;
			exit(1);
		}
	}
	
	else {
		try
		{
			election = new Election(date);
		}
		catch (std::bad_alloc& ex)
		{
			cout << ex.what() << endl;
			exit(1);
		}
	}

	//throw "problem occurred while loading data from the file";
	election->loadDistricts(file);

	//throw "problem occurred while loading data from the file";
	election->loadParties(file);

	//throw "problem occurred while loading data from the file";
	election->loadResults(file);
	
	file.close();
}