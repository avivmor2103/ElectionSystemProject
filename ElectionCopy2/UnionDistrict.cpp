#include "UnionDistrict.h"

UnionDistrict::UnionDistrict(string disName, int disId, int numOfRep, bool isShared ):
    District(disName, disId, numOfRep, isShared) {
}

UnionDistrict::UnionDistrict(ifstream& file, bool isShared) : District(file,isShared){
}

UnionDistrict::~UnionDistrict() {}

void UnionDistrict::setElectors() {
    int winParyIndex = getWinParty();
    Party* p1 = const_cast<Party*>(electionResult[winParyIndex].party);
    p1->addElectors(representatives);
    p1 = nullptr;
 }

int UnionDistrict::getWinParty()const
{
    int maxVoters = 0;
    int idxHolder = 0;
    for (int i = 0; i < electionResult.getLSize(); i++)
    {
        if (electionResult[i].numberOfVoters > maxVoters)
        {
            maxVoters = electionResult[i].numberOfVoters;
            idxHolder = i;
        }
    }
    return idxHolder;
}
void UnionDistrict::printMySelf(ostream& os, const District& district)const{
    os << endl;
    os << "District Number: " << district.getIdNum() << endl;
    os << "District Name: " << district.getName() << endl;
    os << "Number of Representatives: " << district.getNumOfRep() << endl;
    os << "District Type: " << "Union District" << endl;  
}
