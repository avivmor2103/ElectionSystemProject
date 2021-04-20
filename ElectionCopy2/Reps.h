#pragma once
 #include "Citizen.h"
class District;
class DistrictArr;

class Reps
{
private:
	const District* dis;
	const Citizen** repArr;
	int lSize;
	int phSize;
	void reSizeRepresentative();

public:

    Reps(const District* district = nullptr, int phSize = 1, int lsize = 0);
    Reps(const Reps& origin)=delete;
   	//this function reas reps arr from file
	Reps(ifstream& file, const DistrictArr& disList);
	~Reps();

	/*************Getters****************/
	int getlSize()const;
	int getDisNum()const;
	const District* getDistrict()const;
	const string& getRepName(int ind)const;
	const string& getRepId(int ind)const;
	
	//this function add a pointer to citizen (who is a Representative)
	void addRepresentative(const Citizen* rep);

	//this function save a reps arr to a file
	void saveReps(ofstream& file)const;

	const Citizen& operator[](int i);
	const Reps& operator=(const Reps& reps);

};

