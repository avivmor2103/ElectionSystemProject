#pragma once
#include "District.h"
class shareDistrict : public District
{
public :
	shareDistrict(string disName, int disId, int numOfRep, bool isShared = false);
	
	//this function loads a shareDistrict from a file
	shareDistrict(ifstream& file, bool isShared = false);
	
	virtual ~shareDistrict();
	
	//this function adds electors to all parties(each party gets the sum of elected electors)
	virtual void setElectors();
	virtual void printMySelf(ostream& os, const District& district)const;


};

