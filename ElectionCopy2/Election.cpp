#include "Election.h"


Election::Election(){}

Election::Election(const Date& date)
{
    this->elecDate = date;
}

Election::Election(const Election& election){}

Election::~Election(){}

bool Election::SetDate(int day, int month, int year)
{  
	elecDate.setDay(day);
	elecDate.setDay(month);
	elecDate.setDay(year);
    return true;
}

void Election::addParty(const string& name, const Citizen* president)
{
    Party* newP = partyList.addParty(name, president);
    disList.addParty(newP);
    for (int i = 0; i < disList.getlSize(); i++) {
        newP->addDistrict(&disList[i]);
    }
}

void Election::addDistrict(const string& name, int repNumber,bool isShared)
{
    District* newDis = disList.addDistrict(name, repNumber, isShared);
    partyList.addDistrict(newDis);
}

void Election::addCitizen(const string& name, const string& id, int yearOfBirth,int disId)
{
    for (int i = 0; i < disList.getlSize(); i++)
    {
        if (disList[i].getIdNum() == disId) {
            disList[i].addCitizen(name, id, yearOfBirth, disId);
			return;
		}
    }
}

void Election::addRep(int partyId,const Citizen* rep, int disId)
{
    partyList.addRep(partyId, disId, rep);
}

void Election::addVote(int disId, const Party* party)
{
    disList.addVote(party, disId);
}

void Election::printDistrictList()
{
    for (int i = 0; i < disList.getlSize(); i++) {
        cout << "* * * * * * * * * * * * * ";
        cout << disList.getDistrict(i+1);
    }
	char choise[MAX_SIZE];
	do
	{
		cout << "\nFor exit please press 1: ";
		cin >> choise;
	} while (strcmp(choise, "1") != 0);
}

Citizen* Election::findCitizen(const string& idNumber)
{  
	Citizen* c1;
    for (int i = 0; i < disList.getlSize(); i++)
    {
        c1 = disList[i].getCitizen(idNumber);
        if (c1 != nullptr)
            return c1;
	}
    return nullptr;
}

void Election::printPartyList()
{
    for (int i = 0; i < partyList.getlSize(); i++) {
        cout << partyList.getParty(i+1);
    }
	char choise[MAX_SIZE];
	do
	{
		cout << "\nfor exit please press 1: ";
		cin >> choise;
	} while (strcmp(choise, "1") != 0);
}

void Election::printCitizenList()
{
    for (int i = 0; i < disList.getlSize(); i++) {
        for (int j = 0; j < disList.getDistrict(i+1).getCitizenArr().getlSize(); j++)
        {
            cout << disList.getDistrict(i+1).getCitizenArr()[j] << endl;
            cout << "* * * * * * * * * * * * * * * " << endl;
        }
    }
	char choise[MAX_SIZE];
	do
	{
		cout << "\nfor exit please press 1: ";
		cin >> choise;
	} while (strcmp(choise, "1") != 0);
}

void Election::showElectionResults()
{
	if (disList.getlSize() == 0 ||partyList.getlSize()==0) {
		throw "there is no data, please enter a data first";
	}
	
	string presedent ;
	int partyindex;
	int numOfParties = partyList.getlSize();
	float* arrVotesPrecents=nullptr;
	int* arrayOfRepresentativesNum = nullptr;
	int* RepSize = nullptr;
	int* arrayOfPartyVotes = nullptr;
	try
	{
		arrayOfRepresentativesNum = new int[numOfParties] {0};
		RepSize = new int[numOfParties] {0};
		arrayOfPartyVotes = new int[numOfParties] {0};
	}
	catch (std::bad_alloc& exc)
	{
		cout << "ERROR :" << exc.what() << endl;
	}
	catch (const std::exception& e)
	{
		cout << "ERROR :" << e.what() << endl;
	}
	for (int i = 0; i < disList.getlSize(); i++)
	{
		if (disList[i].getNumberOfVoters() == 0) {
			delete[]arrayOfRepresentativesNum;
			delete[]RepSize;
			delete[]arrayOfPartyVotes;
			throw "No one voted yet, please vote";
		}
		printDistrictStatistics(disList[i]);
		disList[i].calculateElectionResults();
		arrVotesPrecents= getArrayOfVotesPrecent(disList[i].getDisResults(), disList[i].getNumberOfVoters(), disList[i].getDisResults().getLSize());

		if(!(disList[i].isSharedDis()))
			printWinnerInDis(disList[i], partyList, &partyindex);
		for (int j = 0; j < disList[i].getDisResults().getLSize(); j++)
		{
			if (disList[i].getDisResults()[j].numOfReps > partyList[j].getRepsArr()[i].getlSize()) {
				delete[]arrayOfRepresentativesNum;
				delete[]RepSize;
				delete[]arrayOfPartyVotes;
				delete[]arrVotesPrecents;
				string msg = "Party: " + partyList[j].getPartyName() + " does not enough RepresentativeList in district: ";
				msg.append(to_string(i + 1));
				throw msg;
				
			}
			arrayOfRepresentativesNum[j] += disList[i].getDisResults()[j].numOfReps;
			
			printSelectedReps(disList[i].getDisResults()[j].party->getPartyName(), partyList.getParty(j+1).getRepsByDis(i + 1), 
				disList[i].getDisResults()[j].numOfReps,disList[i].getDisResults()[j].numberOfVoters, arrVotesPrecents[j]);

		}
		delete[]arrVotesPrecents;
	}
	showCandidateParty(partyList, numOfParties, arrayOfRepresentativesNum);

	delete[] arrayOfPartyVotes;
	delete[] arrayOfRepresentativesNum;
	delete[] RepSize;
	
	char choise[MAX_SIZE];
	do
	{
		cout << "\nfor exit please press 1: ";
		cin >> choise;
	} while (strcmp(choise, "1") != 0);
}

void Election::showCandidateParty(PartyArr& pList, int size, int* arrRep)
{
	int maxInd = findMaxInArr(pList, size);																												  
	for (int i = 0; i < size; i++)
	{
		cout << "The candidate of " << pList[maxInd].getPartyName() << " is: " << pList[maxInd].getPresident().getName() << endl;
		cout << "There are " << arrRep[maxInd] << " representatives for " << pList[maxInd].getPartyName() << endl;
		cout << "Totatl Electors for " << pList[maxInd].getPresident().getName() << " is: " << pList[maxInd].getnumOfElectors() << "\n" << endl;

		pList[maxInd].resetVoters();
		arrRep[maxInd] = 0;
		if(pList[i].getnumOfElectors()==0){
			maxInd = findMaxInArr((float*)arrRep, size);
		}
		else {
	
			maxInd = findMaxInArr(pList, size);
		}
		cout << "* * * * * * * * * * * *" << endl;
	}
}

void Election::printRepByVotePrecent(int size, const Reps& repList)const
{
	for (int i = 0; i < size; i++)
	{
		cout << i + 1 << "." << repList.getRepName(i) << endl;
	}
}

float* Election::getArrayOfVotesPrecent(const DistrictResult& votePerParty, int totalVotes, int numOfParties)const
{

	float* arr = nullptr;
	try {
		arr = new float[numOfParties];
		for (int i = 0; i < numOfParties; i++)
		{
			arr[i] = (static_cast<float>(votePerParty[i].numberOfVoters / static_cast<float>(totalVotes))) * 100;
		}
	}
	catch (std::bad_alloc& e)
	{
		cout << "ERROR:" << e.what() << endl;
	}
	catch (...)
	{
		cout << "There is another problem." << endl;
	}
	return arr;
}

const string Election::getPresByPartyName(PartyArr pL, string partyName)const
{
	for (int i = 0; i < pL.getlSize(); i++)
	{
		if (pL[i].getPartyName()== partyName)
		{
			return pL[i].getPresident().getName();
		}
	}
}

void Election::printSelectedReps(const string partyName, const Reps& repList, int repSize, int numOfvoters, float votePrecent)
{
	cout << "The representatives from " << partyName << " are :" << endl;
	printRepByVotePrecent(repSize, repList);
	cout << endl << "Number of votes: " << numOfvoters << endl;
	cout << "Votes precent: " << votePrecent << "%\n" << endl;
	cout << "* * * * * * * * * * * *" << endl;
}

void Election::loadParties(ifstream& file)
{
	 partyList.loadPartyArr(file,disList);
}

void Election::loadDistricts(ifstream& file)
{
	disList.loadDistricts(file);
}

void Election::loadResults(ifstream& file) {
	disList.loadDistrictResults(file, partyList);
}

void Election::printDistrictStatistics(const District& dis)
{
	cout << dis << endl;
	cout << "District's votes precent: " << dis.getVotePrecent() << "%" << endl;
	cout << "* * * * * * * * * * * *" << endl;
}

void Election::printWinnerInDis(const District& dis,const PartyArr& partyList, int* partyIndex)
{
	*partyIndex = dis.getWinParty();
	 cout << dis.getName() << " Belongs to: " << partyList[*partyIndex].getPresident().getName() << endl;
}

void Election::saveElection(ofstream& file)const
{
	disList.saveDistrictArr(file);
	partyList.savePartyArr(file);
	disList.saveResultsArr(file);
}



