#include "shareDistrict.h"

shareDistrict::shareDistrict(string disName, int disId, int numOfRep, bool isShared) :
    District(disName,disId,numOfRep,isShared){  
}

shareDistrict::shareDistrict(ifstream& file, bool isShared):District(file,isShared){
}

shareDistrict::~shareDistrict(){}

void shareDistrict::setElectors()
{
    int size = electionResult.getLSize();
    Party* p1;
    for (int i = 0; i < size; i++) {
        p1 = const_cast<Party*>(electionResult[i].party);
        p1->addElectors(electionResult[i].numOfReps);
  }
    p1 = nullptr;
}

void shareDistrict::printMySelf(ostream& os, const District& district)const {
    os << endl;
    os << "District Number: " << district.getIdNum() << endl;
    os << "District Name: " << district.getName() << endl;
    os << "Number of Representatives: " << district.getNumOfRep() << endl;
    os << "District Type: " << "Shared District" << endl;
}

