#pragma once
#include "FileManger.h"
#include "Election.h"
#include "simpleElection.h"

class Menu {
protected:
	Election* election;

public:
	Menu();
	Menu(const Menu& origin)=delete;
	Menu(ifstream& file);
	Menu(int numOfReps);
	~Menu() {
		delete election;
	} 

	 //this function sets the election date
	bool SetDate(int day, int month, int year);
	
	//this function responable of the interactive menu
	void ElectionMenu();
	//this function prints the menu
	void printMenu();
	//this function gets ther user choise and sent to the suitable function
	void navigator(int choise);
	
	//this function gets data of an new district and adds it to the district list 
	void addDistrict();
	//this function gets data of an new citizen and add him to the citizen list 
	void addCitizen();
	//this function gets data of an new party and add him to the party list 
	void addParty();
	//this function gets data of an new Representative and add him to the Representative list in his party 
	void addRepresentative();

	//this function responable of showing all the districts
	void showAllDistricts();
	//this function responable of showing all the citizen
	void showAllCitizens();
	//this function responable of showing all the parties
	void showAllParties();

	//this function responable of the voting process
	void vote();
	
	//this fucntion search for a party by name(return true if found, false otherwise)
	bool findParty(const string& name);
	//this fucntion search for a Representative by id(return true if found, false otherwise)
	bool findRep(const string& id);
	//this fucntion check if the district number is big(or not) to the size of the district list
	//if it is it means that that distict doesn't exist
	bool checkDis(int disNumber);
	
	//this function responable of saving the election to a file(user input: file path)
	void saveElectionRound()const;
	//this function responable of loading the election from a file(user input: file path)
	void loadElectionRound();
	
	const Menu& operator=(const Menu& origin) = delete;
};
									  
