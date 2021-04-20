#include"Citizen.h"
#include "District.h"

Citizen::Citizen() {
	this->district = nullptr;
	this->yearOfBirth = -1;
	this->vote = false;
}

Citizen::Citizen(ifstream& file,const District* district)
{
	int nameSize,yearOfBirth;
	bool vote;
	char* name;
	char* id;
	int idSize;
	file.read(rcastc(&nameSize), sizeof(int));
	if (!file.good()) {
		throw "Cann't read from the file that is given";
	}
	name = new char[nameSize];
	file.read(name, nameSize );
	name[nameSize] = '\0';
	file.read(rcastc(&idSize), sizeof(int));
	id = new char[idSize];
	file.read(id, idSize);
	id[idSize] = '\0';
	file.read(rcastc(&yearOfBirth), sizeof(int));
	file.read(rcastc(&vote), sizeof(bool));
	if (!file.good()) {
		throw "Cann't read from the file that is given";
	}							 
	setName(name);
	setVote(vote);
	this->yearOfBirth = yearOfBirth;
	this->id = id;
	this->district = district;
	
}

Citizen::Citizen(const string& name, const string& id, int yearOfBirth, District* district, bool vote) : yearOfBirth(yearOfBirth), vote(vote) {
	this->district = district;
	setName(name);
	setId(id);
}

Citizen::~Citizen(){}

Citizen::Citizen(const Citizen& citizen) {
	name.erase(name.begin(), name.end());
	setName(citizen.name);
	setId(citizen.id);
	this->yearOfBirth = citizen.yearOfBirth;
	this->vote = citizen.vote;
	this->district = citizen.district;
}

const string& Citizen::getName() const
{
	return this->name;
}

const string& Citizen::getId() const
{
	return this->id;
}

int Citizen::getYearOfBirth() const
{
	return this->yearOfBirth;
}

bool Citizen::getVote() const
{
	if (this->vote)
		throw "This Citizen already voted!";
	return false;
}

int Citizen::getDisNum() const
{
	return this->district->getIdNum();
}

bool Citizen::setVote(bool vote)
{
	this->vote = vote;
	return true;
}

bool Citizen::setName(const string& name)
{
	this->name.erase(this->name.begin(),this->name.end());
	this->name = name;
	return true;
}
bool Citizen::setId(const string& Id)
{
	this->id.erase(this->id.begin(), this->id.end());
	this->id =Id;
	return true;
}

void Citizen::saveCitizen(ofstream& file)const
{
	int nameSize = name.size();
	int idSize = id.size();
	file.write(rcastcc(&nameSize), sizeof(int));
	file.write(name.c_str(), nameSize);
	file.write(rcastcc(&idSize), sizeof(int));
	file.write(id.c_str(), idSize);
	file.write(rcastcc(&yearOfBirth), sizeof(int));
	file.write(rcastcc(&vote), sizeof(bool));
}

const Citizen& Citizen::operator=(const Citizen& citizen)
{
	setName(citizen.name);
	setId(citizen.id);
	this->yearOfBirth = citizen.yearOfBirth;
	this->vote = citizen.vote;
	this->district = citizen.district;
	return *this;
}

ostream& operator<<(ostream& os,  const Citizen& citizen)
{
	os << "Name:" << citizen.getName() << endl;
	os << "ID:" << citizen.getId() << endl;
	os << "Year of birth:" << citizen.getYearOfBirth() << endl;
	os << "District number:" << citizen.district->getIdNum()<< endl;
	return os;
}
