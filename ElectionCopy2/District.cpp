#include "District.h"

District::District()
{
    idNumber = -1;
    representatives = 0;
    numOfpeople = 0;
    numOfVotes = 0;
    isShared = false;
    votedPrecent = 0;
}

District::District(string& disName, int disId, int numOfRep, bool isShared):idNumber(disId),representatives(numOfRep),
numOfpeople(0),numOfVotes(0),votedPrecent(0),isShared(isShared)
{
    setName(disName);
}                             

District::District(ifstream& file, bool isShared)
{
    int sizeName;
    char* disname;
    int id, reps, people, votesNum;
    float votePrec;
    this->isShared = isShared;
    file.read(rcastc(&sizeName), sizeof(int));
    if (!file.good()) {
        throw "problem occurred while loading data from the file";
    }
    try
    {
        disname = new char[sizeName + 1];
    }
    catch (std::bad_alloc& ex)
    {
        cout << ex.what() << endl;
        exit(1);
    }
    file.read(disname, sizeName);
    disname[sizeName] = '\0';
    file.read(rcastc(&id), sizeof(int));
    file.read(rcastc(&reps), sizeof(int));
    file.read(rcastc(&people), sizeof(int));
    file.read(rcastc(&votesNum), sizeof(int));
    file.read(rcastc(&votePrec), sizeof(float));
    if (!file.good()) {
        throw "problem occurred while loading data from the file";
    }
    setName(disname);
    setID(id);
    setRepresentatives(reps);
    setNumOfPeople(people);
    setnumOfVoters(votesNum);
    setVotesPrecent(votePrec);
}

District::District(const District& district)
{
    *this = district;
}

District::~District(){}

const string& District::getName() const
{
    return this->name;
}

int District::getIdNum() const
{
    return this->idNumber;
}

int District::getNumOfRep() const
{
    return this->representatives;
}

int District::getNumOfPeople() const
{
    return this->numOfpeople;
}

int District::getNumberOfVoters() const
{
    return this->numOfVotes;
}

float District::getVotePrecent() const
{
    return this->votedPrecent;
}

bool District::setName(const string name)
{
    this->name.erase(this->name.begin(),this->name.end());
    this->name = name;
    return true;
}

bool District::setRepresentatives(int representatives)
{
    this->representatives = representatives;
    return true;
}

bool District::setID(int id)
{
    this->idNumber = id;
    return true;
}

bool District::setNumOfPeople(int numOfPeople)
{
    this->numOfpeople = numOfPeople;
    return true;
}

bool District::setnumOfVoters(int numOfVoters)
{
    this->numOfVotes = numOfVoters;
    return true;
}

bool District::setVotesPrecent(float votesPrecent)
{
    this->votedPrecent = votesPrecent;
    return true;
}

void District::calculateElectionResults()
{
    float  votingRatio;
    votingRatio = static_cast<float>(numOfVotes) / static_cast<float>(representatives);
    checkNumOfRepresentativesNum(votingRatio);
}

void District::loadCitizenArr(ifstream& file)
{
    citizenArr.loadCitizens(file,this); 
}

void District::checkNumOfRepresentativesNum(float vtingRatio)
{
    int maxInd = 0, sum = 0;
    int size=electionResult.getLSize();
    float* left = new float[size];

    for (int i = 0; i < size; i++) {
        electionResult[i].numOfReps = static_cast<int>(electionResult[i].numberOfVoters / vtingRatio);
        sum += electionResult[i].numOfReps;
        left[i] = electionResult[i].numberOfVoters - electionResult[i].numOfReps * vtingRatio;
        if (left[i] > left[maxInd])
            maxInd = i;
    }
    int i = 0;
    while (sum < representatives && i < size) {
        electionResult[maxInd].numOfReps += 1;
        left[maxInd] = 0;
        sum += 1;
        i++;
        maxInd = findMaxInArr(left, size);
    }

    setElectors();

}

int District::getWinParty()const
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

void District::addParty(const Party* party)
{
    this->electionResult.addParty(party);
}

void District::addVote(const Party* party)
{
    for (int i = 0; i < electionResult.getLSize();i++) {
        if (electionResult[i].party->getPartyName()== party->getPartyName())
        {
            electionResult[i].numberOfVoters += 1;
            this->numOfVotes += 1;
            votedPrecent = ((static_cast<float>(numOfpeople)) / numOfpeople)*100;
            return;
        }
    }
    electionResult.addParty(party);
    electionResult[electionResult.getLSize()].numberOfVoters += 1;
    this->numOfVotes += 1;
    votedPrecent = ((static_cast<float>(numOfpeople)) / numOfpeople) * 100;
    return;

}

void District::addCitizen(string name, string id, int yearOfBirth, int disId)
{
    citizenArr.addCitizen(name, id, yearOfBirth, this);
    this->numOfpeople += 1;
}

void District::saveDistrict(ofstream& file)const
{
    int size = name.size();
    file.write(rcastcc (&isShared), sizeof(bool));
    file.write(rcastcc (&size), sizeof(int));
    file.write(name.c_str(), size);
    file.write(rcastcc(&idNumber), sizeof(int));
    file.write(rcastcc(&representatives), sizeof(int));
    file.write(rcastcc(&numOfpeople), sizeof(int));
    file.write(rcastcc(&numOfVotes), sizeof(int));
    file.write(rcastcc(&votedPrecent), sizeof(float));
    size = citizenArr.getlSize();
    file.write(rcastcc(&size), sizeof(int));
    citizenArr.saveCitizenArr(file);
    if (!file.good())
        throw "problem occurred while loading data from the file";
    
}

void District::saveResults(ofstream& file)const {
    int size;
    size = electionResult.getLSize();
    file.write(rcastcc(&size), sizeof(int));
    electionResult.saveResults(file);
    if (!file.good())
        throw "problem occurred while loading data from the file";
}

void District::loadDistrictResults(ifstream& file, const PartyArr& partList)
{
    electionResult.loadDistricResults(file, partList);
}

const District& District::operator=(const District& district)
{
    setName(district.name);
    this->idNumber = district.idNumber;
    this->representatives = district.representatives;
    this->numOfpeople = district.numOfpeople;
    this->numOfVotes = district.numOfVotes;
    this->votedPrecent = district.votedPrecent;
    this->electionResult = district.electionResult;
    return *this;
}

ostream& operator<<(ostream& os, const District& district)
{
     district.printMySelf(os,district);
     return os;
}
