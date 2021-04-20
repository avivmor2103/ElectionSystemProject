#pragma once
#define MAX_SIZE 100
#define _CRT_SECURE_NO_WARNINGS
#include "FileManger.h"
using namespace std;
class District;

class Citizen {

private:
	string name;
	string id;
	int yearOfBirth;
	bool vote;
	const District* district;

public:
	Citizen();
	//This function load a citizen from file
	Citizen(ifstream& file, const District* district);
	Citizen(const string& name, const string& id,int yearOfBirth,District* district,bool vote=false);
	/**** Copy constrctur *****/
	Citizen(const Citizen& citizen);
	
	~Citizen();
	

	/********	Getters	 ***********/
	const string& getName()const;
	const string& getId()const;
	int getYearOfBirth()const;
	bool getVote()const;
	int getDisNum()const;

	/********	Setters	 ***********/
	bool setVote(bool vote);
	bool setName(const string& name);
	bool setId(const string& id);

	//this function save citizen to a file
	void saveCitizen(ofstream& file)const;


	const Citizen& operator=(const Citizen& citizen);
	friend ostream& operator<<(ostream& os, const Citizen& citizen);
};