#include "Party.h"
#include "DistrictArr.h"

Party::Party()
{
	partyID=-1;
    numberOfVoters = 0;
    numOfElectors=0;
	president=nullptr;
}

Party::Party(ifstream& file,  const DistrictArr& disList)
{
    int nameSize,preIdSize, pId, numOfvotes, numOfElec;
    char* name;
    char* preIdNum;
    string preId;
    file.read(rcastc(&nameSize), sizeof(int));
    if (!file.good()) {
        throw "problem occurred while loading data from the file";      
    }
    else {
        try
        {
            name = new char[nameSize + 1];
        }
        catch (std::bad_alloc& ex)
        {
            cout << ex.what() << endl;
            exit(1);
        }
        file.read(name, nameSize );
        file.read(rcastc(&pId), sizeof(int));
        file.read(rcastc(&preIdSize), sizeof(int));
        try
        {
            preIdNum = new char[preIdSize + 1];
        }
        catch (std::bad_alloc& ex)
        {
            cout << ex.what() << endl;
            exit(1);
        }
        file.read(preIdNum, preIdSize);
        file.read(rcastc(&numOfvotes), sizeof(int));
        file.read(rcastc(&numOfElec), sizeof(int));
        if (!file.good()) {
            throw "problem occurred while loading data from the file";
        }
    name[nameSize] = '\0';
    preIdNum[preIdSize] = '\0';
    setName(name);
    partyID = pId;
    preId = preIdNum;
    numberOfVoters = numOfvotes;
    numOfElectors = numOfElec;
    president =disList.findCitizen(preId);
    }
}

Party::Party(const string& name, const Citizen* president, int partyID)
{
        setName(name);
        this->president = president;
        this->partyID = partyID;
        numberOfVoters = 0;
        numOfElectors = 0;
}

Party::~Party(){}

const Reps& Party::getRepsByDis(int disId) const
{
    return repsByDis.getRepsArrByDis(disId);
}     

bool Party::setName(const string name)
{
    this->partyName.erase(partyName.begin(), partyName.end());
    this->partyName = name;
    return true;
}

bool Party::resetVoters()
{
    this->numberOfVoters = 0;
    this->numOfElectors = 0;
    return true;
}

void Party::addRep(const Citizen* rep, int disId)
{
    this->repsByDis.addRep(rep, disId);
}

void Party::addDistrict(const District* district)
{
    this->repsByDis.addDistrict(district);
}

void Party::addElectors(int numOfElectors)
{
    this->numOfElectors += numOfElectors;
}

void Party::addVotes(int numOfVotes)
{
    this->numberOfVoters += numberOfVoters;
}

void Party::saveParty(ofstream& file)const
{
    int size = partyName.size();
    string id = president->getId();
    int idSize = id.size();
    file.write(rcastcc(&size), sizeof(int));
    file.write(partyName.c_str(), size);
    file.write(rcastcc(&partyID), sizeof(int));
    file.write(rcastcc(&idSize), sizeof(int));
    file.write(id.c_str(), idSize);
    file.write(rcastcc(&numberOfVoters), sizeof(int));
    file.write(rcastcc(&numOfElectors), sizeof(int));
    if (!file.good())
        throw "problem occurred while loading data from the file";
    repsByDis.saveRepsArr(file);
    if (!file.good())
        throw "problem occurred while loading data from the file";
}

void Party::loadReps(ifstream& file, const DistrictArr& disList)
{
    repsByDis.loadReps(file,disList);
    if (!file.good())
        throw "problem occurred while loading data from the file";;
}

bool Party::operator>(const Party& origin)
{
    if (this->numOfElectors >= origin.numOfElectors)
        return true;
    return false;
}

ostream& operator<<(ostream& os, Party& party)
{
    os << "***********************************" << endl;
    os <<"Party Name: " << party.partyName << endl;
    os <<"Party ID: "<<party.partyID  << endl;
    os <<"Candidate for Head of State:" << endl;
    os << party.president->getName();
   
    for (int i = 0; i < party.repsByDis.getlSize(); i++) {
        os << "List of Representatives for District Number  "<< party.repsByDis[i].getDisNum()<<":"<< endl;
        for (int j = 0; j < party.repsByDis[i].getlSize(); j++) {
            os << j + 1 << ". " << party.repsByDis[i].getRepName(j) << endl;
        }
    }
    os << "***********************************" << endl;
    return os;
}

ostream& operator<<(ostream& os, const Party& party)
{
    os << "***********************************" << endl;
    os << "Party Name: " << party.partyName << endl;
    os << "Party ID: " << party.partyID << endl;
    os << "Candidate for Head of State:" << endl;
    os << party.president->getName();

    for (int i = 0; i < party.repsByDis.getlSize(); i++) {
        int disNum = party.repsByDis[i].getDisNum();
        os << "List of Representatives for District Number  " << disNum << ":" << endl;
        for (int j = 0; j < party.repsByDis[i].getlSize(); j++) {
            os << j + 1 << ". " << party.repsByDis[i].getRepName(j) << endl;
        }
    }
    os << "***********************************" << endl;
    return os;
}
