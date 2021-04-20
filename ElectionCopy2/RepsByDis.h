#pragma once
#include "FileManger.h"
#include "Reps.h"
class District;
class DistrictArr;

class RepsByDis
{
private:
	DynamicArray<Reps> repsByDis2;

public:
	RepsByDis();
	RepsByDis(const RepsByDis& origin)=delete;
	~RepsByDis();

	/************Getters***************/
	int getlSize()const;
	const Reps& getRepsArrByDis(int disId)const;

	//this function adds a pointer to district in the repByDis arr
	void addDistrict(const District* district);
	//this function add representative in repbyDis arr in the suitable district(by disId)
	void addRep(const Citizen* rep, int disId);

	//this function saves the repbyDis arr to a file 
	void saveRepsArr(ofstream& file)const;

	//this function loads the repbyDis arr from a file 
	void loadReps(ifstream& file, const DistrictArr& disList);

	const Reps& operator[](int i)const;

	const RepsByDis& operator=(const RepsByDis &origin) = delete;

};

