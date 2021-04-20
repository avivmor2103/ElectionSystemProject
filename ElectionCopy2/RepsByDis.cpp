#include "RepsByDis.h"

RepsByDis::RepsByDis(){}

RepsByDis::~RepsByDis(){}

int RepsByDis::getlSize()const
{
	return repsByDis2.size();
}

const Reps& RepsByDis::getRepsArrByDis(int disId) const 
{
	for (int i = 0; i < repsByDis2.size();i++) {
		if (repsByDis2[i].getDisNum() == disId)
			return repsByDis2[i];
	}
}

void RepsByDis::addDistrict(const District* district)
{
	repsByDis2.push_back(*(new Reps(district, 1, 0)));
}

void RepsByDis::addRep(const Citizen* rep, int disId)
{
	for (int i = 0; i < repsByDis2.size(); i++) {
		if (repsByDis2[i].getDisNum() == disId) {
			repsByDis2[i].addRepresentative(rep);
		}
	}
}

void RepsByDis::saveRepsArr(ofstream& file)const
{
	int size = repsByDis2.size();
	file.write(rcastcc(&size), sizeof(int));
	for (int i = 0; i < size; i++) {
		repsByDis2[i].saveReps(file);
	}
}

void RepsByDis::loadReps(ifstream& file, const DistrictArr& disList)
{
	int size;
	Reps* newReps = nullptr;
	file.read(rcastc(&size), sizeof(int));
	if (!file.good())
		throw "problem occurred while loading data from the file";

	repsByDis2.erase(repsByDis2.begin(), repsByDis2.end());
	for (int i = 0; i < size; i++) {
		try
		{
			newReps = new Reps(file, disList);
		}
		catch (std::bad_alloc& ex)
		{
			cout << ex.what() << endl;
			exit(1);
		}
		repsByDis2.push_back(*newReps);
		newReps = nullptr;
	}
	newReps = nullptr;
	delete newReps;
}

const Reps& RepsByDis::operator[](int i) const
{
	return repsByDis2[i];
}