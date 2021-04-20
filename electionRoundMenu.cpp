#include <iostream>
#include <ostream>
#include <fstream>
#include "electionRoundMenu.h"

using namespace std;
#define rcastc reinterpret_cast<char*>


const int ERROR = -1;
const int LEGALITY_AGE = 19;
const int ID_LEN = 9;

enum OptionManageElectionRound { OAddDistrict = 1, OAddCitizen = 2, OAddParty, OAddCitizenAsPartyDelegate, ODisplayAllDistricts, ODisplayAllCitizens, ODisplayAllParties, OVote, OShoeElectionResults, OExit, OSave, OLoad };
enum MainMenuOption { OCreateElectionRound = 1, OLoadExistsElectionRound = 2,OMExit=3};
enum DistrictType {TDividedDistrict = 0, TUnionDistric = 1};
enum ElectionRoundType { TRegularElectionRound = 0, TSimpleElectionRound = 1 };

void MainMenu() {
	int optionInput;
	ElectionRound* electionRound = nullptr;
	do {
		try {
			displayMainMenu();
			cin >> optionInput;
			if (optionInput < 1 || optionInput >3) {
				throw invalid_argument("There is no such option , please Try again!");
			}
			switch (optionInput)
			{
				case OCreateElectionRound:
				{
					AddNewElectionRound(electionRound);
					cout << "Election Round was added successfully!" << endl;
					break;
				}
				case OLoadExistsElectionRound:
				{
					LoadExistsElectionRound(electionRound);
					break;
				}
				case OMExit:
				{
					cout << "Bye Bye..";
					return;
				}
				default:
				{
				}
			}
			break;
		}
		catch (invalid_argument ie) {
			cout << ie.what() << endl;
		}
		catch (bad_alloc& badAllocEx) {
			cout << badAllocEx.what() << endl;
		}
		catch (ios_base::failure& iosFailureEx) {
			cout << iosFailureEx.what() << endl;
		}
		catch (...) {
			cout << "Unknown error" << endl;
		}
	} while (true);

	if (electionRound) {
		electionRoundMenu(electionRound);
		delete electionRound;
	}	
}

void displayMainMenu() {
	cout << "Please choose a preferrd option: " << endl
		<< "1. Create New Election Round" << endl
		<< "2. Load Exists Election Round" << endl
		<< "3. Exit" << endl;
}

void AddNewElectionRound(ElectionRound*& electionRound) noexcept(false) {
	int electionRoundType, totalNumrepresentatives;

	Date* electionRDate = GetElectionRoundDateFromUserInput();
	cout << "please enter type of election round: 0 for regular election round, 1 for simple election round" << endl;
	cin >> electionRoundType;

	if ((electionRoundType != TSimpleElectionRound) && (electionRoundType != TRegularElectionRound)) {
		throw invalid_argument("invalid election round type");
	}
	switch (electionRoundType)
	{
		case TRegularElectionRound: {
			electionRound = new RegularElectionRound(*electionRDate);
			break;
		}
		case TSimpleElectionRound: {
			cout << "please enter total number of representatives: ";
			cin >> totalNumrepresentatives;
			DividedDistrict dividedDistrict("Divided District", 1, totalNumrepresentatives);
			electionRound = new SimpleElectionRound(*electionRDate, dividedDistrict);
			break;
		}
		default:
			break;
	}
}

void SaveElectionRound(const ElectionRound& electionRound) {
	string fileName;
	cout << "Please enter fila name: ";
	cin >> fileName;
	ofstream outFile(fileName, ios::binary);
	SimpleElectionRound* simpleElectionRound = dynamic_cast<SimpleElectionRound*>(&const_cast<ElectionRound&>(electionRound));
	if (simpleElectionRound) {
		simpleElectionRound->saveBin(outFile);
	}
	else
	{
		RegularElectionRound* regularElectionRound = dynamic_cast<RegularElectionRound*>(&const_cast<ElectionRound&>(electionRound));
		if (regularElectionRound)
			regularElectionRound->saveBin(outFile);
	}
	outFile.close();
}

void LoadExistsElectionRound(ElectionRound*& electionRound) noexcept(false) {
	string fileName;
	ifstream inFile;

	cout << "please enter file name: " << endl;
	cin >> fileName;
	
	inFile.open(fileName, ios::binary);
	if (!inFile) {
		throw ios_base::failure("File was not Found");
	}
	else {
		int type = 0;
		inFile.read(rcastc(&type), sizeof(type));
		if (!inFile.good()) {
			throw ios_base::failure("error reading");
		}
		if (type == TRegularElectionRound) {
			DistrictListHanlder* districtList = new DistrictListHanlder(inFile);
			electionRound = new RegularElectionRound(inFile, *districtList);
		}
		else {
			int  numOfRep;
			DistrictListHanlder* districtList = new DistrictListHanlder();
			inFile.read(rcastc(&numOfRep), sizeof(numOfRep));
			District* dividedDistrict = new DividedDistrict("Divided District", 1, numOfRep);
			const_cast<LinkedList<District>&>(districtList->getDistrictList()).add(*dividedDistrict);
			electionRound = new SimpleElectionRound(inFile, *districtList);
		}
		inFile.close();
	}
}

void electionRoundMenu(ElectionRound*& electionRound) {
	int optionInput;
	introduce(*electionRound);
	do {
		try {
			displayManageMainMenu();
			cin >> optionInput;
			if (optionInput < 1 || optionInput >12) {
				throw invalid_argument("There is no such option , please Try again!");
			}
			else {
				Menu(electionRound, optionInput);
				if (optionInput == 10) {
					return;
				}
				if (optionInput == 12) {
					electionRoundMenu(electionRound);
					return;
				}
				returnToMainMenu();
			}
		}
		catch (invalid_argument e) {
			cout << e.what() << endl;
		}
	} while (true);
}

void introduce(ElectionRound& electionRound) {
	cout << "Welcome To Election Round " << electionRound.getDate().getDay() << "/" << electionRound.getDate().getMonth() << "/" << electionRound.getDate().getYear() << endl
		<< "------------------------------------" << endl << endl;
}

void displayManageMainMenu() {
	cout << "Please choose a preferrd option: " << endl
		<< "1. Add District" << endl
		<< "2. Add Citizen"<< endl
		<< "3. Add Party" << endl
		<< "4. Add citizen as party delegate" << endl
		<< "5. Display all districts " << endl
		<< "6. Display all citizens " << endl
		<< "7. Display all parties " << endl
		<< "8. Add vote" << endl
		<< "9. Show Election Results" << endl
		<< "10. Exit" << endl 
		<< "11. Save Election Round" << endl
		<< "12. Load Exists Election Round" << endl << endl;
}

void returnToMainMenu() {
	int input;
	cout << "0. Back to the Main Menu" << endl;
	cin >> input;
	while (input) {
		cout << "0. Back to the Main Menu" << endl;
		cin >> input;
	}
}

void Menu(ElectionRound*& electionRound, int& optionInput) {
	try {
		switch (optionInput)
		{
		case OAddDistrict:
		{
			AddDistrict(*electionRound);
			cout << "District was added successfully!" << endl;
			break;
		}
		case OAddCitizen:
		{
			AddCitizen(*electionRound);
			cout << "Citizen was added successfully!" << endl;
			break;
		}
		case OAddParty:
		{
			AddParty(*electionRound);
			cout << "Party was added successfully!" << endl;
			break;
		}
		case OAddCitizenAsPartyDelegate:
		{
			addRepresentAsAPartyCitizen(*electionRound);
			cout << "Represent as a party citizen was added successfully!" << endl;
			break;
		}
		case ODisplayAllDistricts:
		{
			DisplayAllDisticts(*electionRound);
			break;
		}
		case ODisplayAllCitizens:
		{
			DisplayAllCitizens(*electionRound);
			break;
		}
		case ODisplayAllParties:
		{
			DisplayAllParties(*electionRound);
			break;
		}
		case OVote:
		{
			AddVote(*electionRound);
			cout << "Vote was taken successfully!" << endl;
			break;
		}
		case OShoeElectionResults:
		{
			ShowElectionResults(*electionRound);
			break;
		}
		case OSave:
		{
			SaveElectionRound(*electionRound);
			cout << "Election Round was saved successfully!" << endl;
			break;
		}
		case OLoad:
		{
			LoadExistsElectionRound(electionRound);
			break;
		}
		case OExit:
		{
			cout << "Bye Bye.." << endl;
			break;
		}
		default:
			break;
		}
	}
	catch (invalid_argument e) {
		cout << e.what() << endl;
	}
	catch (length_error le) {
		cout << le.what() << endl;
	}
	catch (ios_base::failure& iosFailureEx) {
		cout << iosFailureEx.what() << endl;
	}
}

Date* GetElectionRoundDateFromUserInput() {
	int day, month, year;
	while (true)
	{
		cout << "please enter date(day,month,year) of the election round: ";
		cin >> day >> month >> year;
		try {
			Date* date = new Date(day, month, year);
			return date;
		}
		catch (invalid_argument e) {
			cout << e.what() << endl;
		}
	}
}

void AddDistrict(ElectionRound& electionRound) noexcept(false) {
	RegularElectionRound* regularElectionRound = dynamic_cast<RegularElectionRound*>(&electionRound);
	if (!regularElectionRound) {
		throw invalid_argument("There are no districts to simple election round");
	}
	string name;
	District* newDistrict = nullptr;
	int numOfDelegates;
	int districtType;
	getDistrictInputFromUser(name, numOfDelegates, districtType);
	switch (districtType)
	{
		case TDividedDistrict:
			newDistrict = new DividedDistrict(name, regularElectionRound->getDistricts().getDistrictList().getlListSize() + 1, numOfDelegates);
			break;
		case TUnionDistric:
			newDistrict = new UnionDistrict(name, regularElectionRound->getDistricts().getDistrictList().getlListSize() + 1, numOfDelegates);
			break;
		default:
			break;
		}
	regularElectionRound->addDistrict(newDistrict);
	if (newDistrict) {
		for (int i = 0; i < regularElectionRound->getParties().getPartyList().getlListSize(); i++) {
			const_cast<Party&>(regularElectionRound->getParties().getPartyList().getDataByIndex(i)).addDistrictToRepresentListByDistrictArr(newDistrict->getSerialNumber() - 1);
		}
	}
}

void getDistrictInputFromUser(string& name, int& numOfDelegates, int& districtType) noexcept(false) {
	cout << "Please enter: district name, num of delegats and distict type" << endl
		<< "-----------------------------------------------" << endl
		<< "District Name: " << endl;
	(void)getchar();
	getline(cin, name);
	cout << "Num Of Delegats: " << endl;
	cin >> numOfDelegates;
	cout << "District Type: 0 for divided district, 1 for union district (bool)" << endl;
	cin >> districtType;
	if ((districtType != 0) && (districtType != 1))
		throw invalid_argument("Invalid district type");
}

void AddCitizen(ElectionRound& electionRound) noexcept(false) {
	string name, Id;
	int birthYear, srialNumberDistrict;
	const District* CitizenDistrict;
	getCitizenInputFromUser(electionRound, name, Id, birthYear, srialNumberDistrict);
	RegularElectionRound* regularElectionRound = dynamic_cast<RegularElectionRound*>(&electionRound);
	if (regularElectionRound) {
		CitizenDistrict = &regularElectionRound->getDistricts().getDistrictList().getDataByIndex(srialNumberDistrict - 1);
	}
	else {
		SimpleElectionRound* simpleElectionRound = dynamic_cast<SimpleElectionRound*>(&electionRound);
		CitizenDistrict = &simpleElectionRound->getDividedDistrict();
	}
	if (electionRound.getDate().getYear() - birthYear < LEGALITY_AGE) {
		throw invalid_argument("Illegal citizen to vote (Under the age of 19)");
	}
	Citizen* newCitizen = new Citizen(name, Id, birthYear, CitizenDistrict);
	electionRound.addCitizen(*newCitizen);
	delete newCitizen;
}

void getCitizenInputFromUser(const ElectionRound& electionRound,string& name, string& Id, int& birthYear,int& SrialNumberDistrict) noexcept(false) {
	cout << "Please enter: citizen name, Id , birth year and district serial number" << endl
		<< "-----------------------------------------------------------------------" << endl
		<< "Citizen Name: " << endl;
	(void)getchar();
	getline(cin, name);
	cout << "Citizen Id: " << endl;
	getline(cin, Id);
	cout << "Citizen Birth Year: " << endl;
	cin >> birthYear;
	cout << "District Serial Number: " << endl;
	cin >> SrialNumberDistrict;
	if (electionRound.getVoterRegister().IsCitizenExist(Id)) {
		throw invalid_argument("Id is already exists");
	}
	RegularElectionRound* regularElectionRound = dynamic_cast<RegularElectionRound*>(&(const_cast<ElectionRound&>(electionRound)));
	if (regularElectionRound) {
		if (SrialNumberDistrict > regularElectionRound->getDistricts().getDistrictList().getlListSize() || SrialNumberDistrict == 0) {
			throw invalid_argument("Serial Number District doesn't exists");	
		}
	}
}

void AddParty(ElectionRound& electionRound) {
	string name, candidateId;
	getPartyInputFromUser(electionRound, name, candidateId);
	const Citizen& candidate = electionRound.getVoterRegister().getCitizenByID(candidateId);
	Party* newParty = new Party(name, electionRound.getParties().getPartyList().getlListSize() + 1, &candidate);
	RegularElectionRound* regularElectionRound = dynamic_cast<RegularElectionRound*>(&electionRound);
	if (regularElectionRound) {
		for (int i = 0; i < regularElectionRound->getDistricts().getDistrictList().getlListSize(); i++) {
			newParty->addDistrictToRepresentListByDistrictArr(regularElectionRound->getDistricts().getDistrictList().getDataByIndex(i).getSerialNumber() - 1);
		}
	}
	else {
		newParty->addDistrictToRepresentListByDistrictArr(0);
	}
	electionRound.addParty(*newParty);
}

void getPartyInputFromUser(ElectionRound& electionRound, string& name, string& candidateId) noexcept(false) {
	cout << "Please enter: party name and Candidate ID" << endl
		<< "------------------------------------------" << endl
		<< "Party Name: " << endl;
	(void)getchar();
	getline(cin, name);
	cout << "Candidate Id: " << endl;
	cin >> candidateId;
	if (candidateId.length() != ID_LEN)
		throw invalid_argument("Invalid Id");
	if (!electionRound.getVoterRegister().IsCitizenExist(candidateId)) {
		throw invalid_argument("Candidate doesn't exists");
	}
	if (isDoubleCandidate(electionRound, candidateId)) {
		throw invalid_argument("The citizen is already a candidate for another party");
	}
	if (isDoubleRepresentative(electionRound, candidateId))
		throw invalid_argument("The citizen already exists as a representative");
}

bool isDoubleCandidate(const ElectionRound& electionRound, string& represenId) {
	for (int i = 0; i < electionRound.getParties().getPartyList().getlListSize(); i++) {
		if (electionRound.getParties().getPartyList().getDataByIndex(i).getCandidate().getId().compare(represenId) == 0)
			return true;
	}
	return false;
}

void AddVote(ElectionRound& electionRound) {
	int PartySrialNumber;
	string Id;
	getVoteInputFromUser(electionRound, Id, PartySrialNumber);
	const Citizen& CitizenVoter = electionRound.getVoterRegister().getCitizenByID(Id);
	const Party& PartyVoter = electionRound.getParties().getPartyList().getDataByIndex(PartySrialNumber - 1);
	Vote* newVote = new Vote(CitizenVoter, PartyVoter);
	electionRound.addVote(*newVote);
}

void getVoteInputFromUser(const ElectionRound& electionRound, string& Id, int& PartySrialNumber) noexcept(false) {
	cout << "Please enter: citizen Id and party Serial Number" << endl
		<< "-------------------------------------------------" << endl
		<< "Citizen Id: " << endl;
	(void)getchar();
	cin >> Id;
	cout << "Party Serial Number: " << endl;
	cin >> PartySrialNumber;
	if (Id.length() != ID_LEN)
		throw invalid_argument("Invalid Id");
	if (!electionRound.getVoterRegister().IsCitizenExist(Id))
		throw invalid_argument("Citizen Id is not exists");
	if (PartySrialNumber > electionRound.getParties().getPartyList().getlListSize() || PartySrialNumber==0)
		throw invalid_argument("Serial Number District doesn't exists");
	if (electionRound.getVotes().isDoubleVote(Id))
		throw invalid_argument("Double vote, a citizen may not vote more than once");
}

void addRepresentAsAPartyCitizen(ElectionRound& electionRound) {
	int PartySrialNumber, DistrictSrialNumber;
	string Id;
	getCitizenAsAPartyRepresentFromUserInput(electionRound, Id, PartySrialNumber, DistrictSrialNumber);
	const Citizen& PartyRepresent = electionRound.getVoterRegister().getCitizenByID(Id); RegularElectionRound* regularElectionRound = dynamic_cast<RegularElectionRound*>(&(const_cast<ElectionRound&>(electionRound)));
	if (regularElectionRound) {
		const_cast<Party&>(electionRound.getParties().getPartyList().getDataByIndex(PartySrialNumber - 1)).addCitizenAsAPartyRepresent(PartyRepresent, DistrictSrialNumber - 1);
	}
	else {
		const_cast<Party&>(electionRound.getParties().getPartyList().getDataByIndex(PartySrialNumber - 1)).addCitizenAsAPartyRepresent(PartyRepresent, 0);
	}
}

void getCitizenAsAPartyRepresentFromUserInput(const ElectionRound& electionRound, string& represenId, int& PartySrialNumber, int& SrialNumberDistrict) noexcept(false) {
	cout << "Please enter: representative Id , party Serial Number and district serial number" << endl
		<< "---------------------------------------------------------------------------------" << endl
		<< "Representative Id: " << endl;
	(void)getchar();
	cin >> represenId;
	cout << "Party Serial Number: " << endl;
	cin >> PartySrialNumber;
	cout << "District Serial Number: " << endl;
	cin >> SrialNumberDistrict;
	if (represenId.length() != ID_LEN)
		throw invalid_argument("Invalid Id");
	if (!electionRound.getVoterRegister().IsCitizenExist(represenId))
		throw invalid_argument("Citizen Id is not exists");
	if (PartySrialNumber > electionRound.getParties().getPartyList().getlListSize() || PartySrialNumber==0)
		throw invalid_argument("Serial Number Party doesn't exists");

	RegularElectionRound* regularElectionRound = dynamic_cast<RegularElectionRound*>(&(const_cast<ElectionRound&>(electionRound)));
	if (regularElectionRound) {
		if (SrialNumberDistrict > regularElectionRound->getDistricts().getDistrictList().getlListSize() || SrialNumberDistrict == 0)
			throw invalid_argument("Serial Number District doesn't exists");
	}
	if (isDoubleRepresentative(electionRound, represenId))
		throw invalid_argument("The citizen already exists as a representative");
	if (isDoubleCandidate(electionRound, represenId))
		throw invalid_argument("The citizen already exists as a candidate");
}

bool isDoubleRepresentative(const ElectionRound& electionRound, string& represenId) {
	for (int i = 0; i < electionRound.getParties().getPartyList().getlListSize(); i++) {
		const Party& party = electionRound.getParties().getPartyList().getDataByIndex(i);
		for (int j = 0; j < electionRound.getParties().getPartyList().getDataByIndex(i).getRepresentListByDistrictArr().size(); j++) {
			if (electionRound.getParties().getPartyList().getDataByIndex(i).getRepresentListByDistrictArr()[j].getCitizenList().getlListSize())
				if (electionRound.getParties().getPartyList().getDataByIndex(i).getRepresentListByDistrictArr()[j].IsCitizenExist(represenId))
					return true;
		}
	}
	return false;
}

void DisplayAllDisticts(const ElectionRound& electionRound) {
	RegularElectionRound* regularElectionRound = dynamic_cast<RegularElectionRound*>(&(const_cast<ElectionRound&>(electionRound)));
	if (!regularElectionRound) {
		cout<< "There are no districts to simple election round" << endl;
	}
	else
		cout << "Districts: " << endl << "---------" << endl << regularElectionRound->getDistricts().getDistrictList() << endl;
}

void DisplayAllCitizens(const ElectionRound& electionRound) {
	cout << "Citizens: " << endl << "---------" << endl << electionRound.getVoterRegister().getCitizenList() << endl;
}

void DisplayAllParties(const ElectionRound& electionRound) {
	cout << "Parties: " << endl << "---------" << endl << electionRound.getParties().getPartyList() << endl;
}

void ShowElectionResults(const ElectionRound& electionRound) noexcept(false) {
	
	if (!electionRound.getVotes().getVoteList().getlListSize()) {
		throw length_error("No votes for show election results");
	}

	introduce(const_cast<ElectionRound&>(electionRound));
	RegularElectionRound* regularElectionRound = dynamic_cast<RegularElectionRound*>(&(const_cast<ElectionRound&>(electionRound)));
	int numOfParties = electionRound.getParties().getPartyList().getlListSize();
	int numOfDistricts = 1;
	if (regularElectionRound) {
		numOfDistricts = regularElectionRound->getDistricts().getDistrictList().getlListSize();
	}
	vector<vector<int>> votesArr = initVotesArr(numOfParties, numOfDistricts);
	fillVotesInVotesArrByDistrictAndParty(electionRound, votesArr);
	vector<int> totalDeligatesByParty(numOfParties,0);
	for (int i = 0; i < numOfParties; i++) {
		totalDeligatesByParty[i] = 0;
	}
	if (regularElectionRound)
		ShowRegularElectionRoundResults(electionRound, numOfParties, numOfDistricts, votesArr, totalDeligatesByParty);
	else
		ShowSimpleElectionRoundResults(electionRound, numOfParties, votesArr, totalDeligatesByParty);
}

void ShowRegularElectionRoundResults(const ElectionRound& electionRound, int numOfParties, int numOfDistricts, vector<vector<int>>& votesArr, vector<int>& totalDeligatesByParty) {
	cout << " Regular Election Result" << endl << "-------------------" << endl;
	ShowDistrictsResults(electionRound, numOfParties, numOfDistricts, votesArr, totalDeligatesByParty);
	cout << endl;
	showPartiesResults(electionRound, totalDeligatesByParty, numOfParties, numOfDistricts, votesArr);
}

void ShowSimpleElectionRoundResults(const ElectionRound& electionRound, int numOfParties, vector<vector<int>>& votesArr, vector<int>& totalDeligatesByParty) {
	int i, winnerIndexParty = 0;
	bool districtType = TDividedDistrict;
	SimpleElectionRound* simpleElectionRound = dynamic_cast<SimpleElectionRound*>(&(const_cast<ElectionRound&>(electionRound)));
	vector<int>& districtVotesByPartyArr = votesArr[0];
	winnerIndexParty = getWinnerPartyIndexInDistrict(districtVotesByPartyArr, numOfParties, districtType);
	int numOfDelegates = simpleElectionRound->getNumOfRepresentatives();
	
	cout << " Simple Election Result" << endl << "-------------------" << endl;

	if (!numOfDelegates) {
		throw length_error("There are no representatives and cannot calculate results");
	}
	else if (winnerIndexParty >= 0) {
		int sumOfVotes = getSumOfVotesInDistrict(districtVotesByPartyArr, numOfParties);
		int numOfCitizens = simpleElectionRound->getVoterRegister().getCitizenList().getlListSize();
		float percentage = 0.0;
		cout << "Vote Percent: " << (static_cast<float>(sumOfVotes) / static_cast<float>(numOfCitizens)) * 100 << " %" << endl;
		vector<int> numOfDelegatesForParty(numOfParties,0);
		calulateNumOfDelegatesForParty(numOfDelegates, sumOfVotes, numOfParties, districtVotesByPartyArr, numOfDelegatesForParty);
		vector<int> paritesNSerialNumbersArr(numOfParties,0);
		for (i = 0; i < numOfParties; i++) {
			paritesNSerialNumbersArr[i] = i;
		}
		SortPartyArrByDeligates(districtVotesByPartyArr, paritesNSerialNumbersArr, numOfParties);
		for (i = 0; i < numOfParties; i++) {
			totalDeligatesByParty[i] += numOfDelegatesForParty[i];
		}
		for (i = 0; i < numOfParties; i++) {
			int indexParty = paritesNSerialNumbersArr[i];
			cout << "Party " << indexParty + 1 << "-->" << endl
				<< "Candidate: " << electionRound.getParties().getPartyList().getDataByIndex(indexParty).getCandidate() << endl
				<< "Sum of representatives: " << totalDeligatesByParty[indexParty] << endl
				<< "Sum of votes: " << districtVotesByPartyArr[indexParty] << endl;
			
			percentage = (static_cast<float>(votesArr[0][indexParty]) / static_cast<float>(sumOfVotes)) * 100;
			cout << "received " << districtVotesByPartyArr[indexParty] << " Votes and percentages of " << percentage << " % from all votes" << endl
				<< "Delegates List of Party: " << endl;
			if (!numOfDelegatesForParty[indexParty]) {
				cout << "No representatives were given to the party" << endl << endl;
			}
			else if (numOfDelegatesForParty[indexParty] > electionRound.getParties().getPartyList().getDataByIndex(indexParty).getRepresentListByDistrictArr()[0].getCitizenList().getlListSize()) {
				cout << "There are not enough representatives for the party in the district to be given the representatives it has received" << endl;
			}
			else {
				for (int k = 0; k < numOfDelegatesForParty[indexParty]; k++) {
					cout << electionRound.getParties().getPartyList().getDataByIndex(indexParty).getRepresentListByDistrictArr()[0].getCitizenList().getDataByIndex(k) << endl;
				}
			}
			cout << endl;
		}
	}
	else
		cout << "There are no votes " << endl;
}

void ShowDistrictsResults(const ElectionRound& electionRound, int numOfParties, int numOfDistricts, vector<vector<int>>& votesArr, vector<int>& totalDeligatesByParty) {
	int i,j, winnerIndexParty=0;
	int districtType;
	RegularElectionRound* regularElectionRound = dynamic_cast<RegularElectionRound*>(&(const_cast<ElectionRound&>(electionRound)));
	cout << "results By District" << endl << "-------------------" << endl;
	for (j = 0; j < numOfDistricts; j++) {
		vector<int>& districtVotesByPartyArr = votesArr[j];
		if (typeid(regularElectionRound->getDistricts().getDistrictList().getDataByIndex(j)) == typeid(UnionDistrict))
			districtType = TUnionDistric;
		else
			districtType = TDividedDistrict;
		winnerIndexParty = getWinnerPartyIndexInDistrict(districtVotesByPartyArr, numOfParties, districtType);
		int districtnumOfDelegates = regularElectionRound->getDistricts().getDistrictList().getDataByIndex(j).getNumOfRepresentatives();
		cout << "District " << j + 1 << endl << "----------" << endl << "District Name: " << regularElectionRound->getDistricts().getDistrictList().getDataByIndex(j).getName() << " , "
			<< "Num Of Represatatives: " << districtnumOfDelegates << " , ";
		if (!districtnumOfDelegates) {
			//There is no exception here beacuse it is possible to continue to present election results for the other districts
			cout << "The district does not have representatives and cannot calculate results for the district" << endl;
		}
		else if (winnerIndexParty >= 0) {
			int sumOfVotes = getSumOfVotesInDistrict(districtVotesByPartyArr, numOfParties);
			int numOfCitizensInDistrict = getNumOfCitizensInDistrict(electionRound, j + 1);
			float percentage = 0.0;
			cout << "Vote Percent District: " << (static_cast<float>(sumOfVotes) / static_cast<float>(numOfCitizensInDistrict)) * 100 << " %" << endl;
			vector<int> numOfDelegatesForParty(numOfParties,0);
			calulateNumOfDelegatesForParty(districtnumOfDelegates, sumOfVotes, numOfParties, districtVotesByPartyArr, numOfDelegatesForParty);
			if (districtType) {
				totalDeligatesByParty[winnerIndexParty] += districtnumOfDelegates;
				cout << "Party Candidate: " << electionRound.getParties().getPartyList().getDataByIndex(winnerIndexParty).getCandidate() << endl;
			}	
			else {
				vector<int> paritesNSerialNumbersArr(numOfParties,0);
				for (i = 0; i < numOfParties; i++) {
					paritesNSerialNumbersArr[i] = i;
				}
				SortPartyArrByDeligates(numOfDelegatesForParty, paritesNSerialNumbersArr, numOfParties);
				for (int k = 0; k < numOfParties; k++) {
					totalDeligatesByParty[k] += numOfDelegatesForParty[k];
					if(numOfDelegatesForParty[paritesNSerialNumbersArr[k]]>0)
						cout << "Party Candidate: " << electionRound.getParties().getPartyList().getDataByIndex(paritesNSerialNumbersArr[k]).getCandidate() << "num of delegates: " << numOfDelegatesForParty[paritesNSerialNumbersArr[k]] << endl;
				}
			}
			for (i = 0; i < numOfParties; i++) {
				percentage = (static_cast<float>(votesArr[j][i]) / static_cast<float>(sumOfVotes)) * 100;
				cout << "Party " << i + 1 << "-->" << " has received " << districtVotesByPartyArr[i] << " Votes and percentages of " << percentage << " % from all votes in the district" << endl
					<< "Delegates List of Party: " << endl;
				if (!numOfDelegatesForParty[i]) {
					cout << "No representatives were given to the party" << endl << endl;
				}
				else if (numOfDelegatesForParty[i] > electionRound.getParties().getPartyList().getDataByIndex(i).getRepresentListByDistrictArr()[j].getCitizenList().getlListSize()) {
					cout << "There are not enough representatives for the party in the district to be given the representatives it has received" << endl;
				}
				else {
					for (int k = 0; k < numOfDelegatesForParty[i]; k++) {
						cout << electionRound.getParties().getPartyList().getDataByIndex(i).getRepresentListByDistrictArr()[j].getCitizenList().getDataByIndex(k) << endl;
					}
				}
			}
		}
		else
			cout << "No Votes for this district" << endl;
	}
}

void calulateNumOfDelegatesForParty(int DistrictnumOfDelegates, int sumOfVotes, int NumOfParties, vector<int>& districtVotesByPartyArr, vector<int>& numOfDelegatesForParty) {
	int i;
	int remainingNumOfDelegates = DistrictnumOfDelegates;
	int numOfVotesNeededForDelegate = sumOfVotes / DistrictnumOfDelegates;
	vector<int> remainingVotesForParty(NumOfParties,0);
	int temp = 0;
	for (i = 0; i < NumOfParties && remainingNumOfDelegates > 0; i++) {
		if (numOfVotesNeededForDelegate == 0) {
			remainingVotesForParty[i] = districtVotesByPartyArr[i];
		}
		else {
			temp = districtVotesByPartyArr[i] / numOfVotesNeededForDelegate;
			if (temp > remainingNumOfDelegates) {
				temp = remainingNumOfDelegates;
			}
			numOfDelegatesForParty[i] = temp;
			remainingVotesForParty[i] = districtVotesByPartyArr[i] % numOfVotesNeededForDelegate;
			remainingNumOfDelegates -= numOfDelegatesForParty[i];
		}
	}
	int firstMaxIndex;
	while (remainingNumOfDelegates > 0) {
		firstMaxIndex = Utilities<int>::getFirstMaxIndex(remainingVotesForParty, NumOfParties);
		numOfDelegatesForParty[firstMaxIndex]++;
		remainingVotesForParty[firstMaxIndex] = 0;
		remainingNumOfDelegates--;
	}
}

void showPartiesResults(const ElectionRound& electionRound, vector<int>& totalDeligatesByParty, int numOfParties, int numOfDistricts, vector<vector<int>> votesArr) {
	int i,j;
	vector<int> totalVotesByParty(numOfParties,0);
	vector<int> paritesNSerialNumbersArr(numOfParties,0);
	for (i = 0; i < numOfParties; i++) {
		totalVotesByParty[i] = 0;
	}
	for (i = 0; i < numOfParties; i++) {
		paritesNSerialNumbersArr[i] = i;
	}
	for (i = 0; i < numOfParties; i++) {
		for (j = 0; j < numOfDistricts; j++) {
			totalVotesByParty[i] += votesArr[j][i];
		}
	}
	SortPartyArrByDeligates(totalDeligatesByParty, paritesNSerialNumbersArr, numOfParties);
	cout << "results By Parties" << endl << "-------------------" << endl;
	for (i = 0; i < numOfParties; i++) {
		int ind = paritesNSerialNumbersArr[i];
		cout << "Party " << ind + 1 << ": " << endl
			<< "Candidate: " << electionRound.getParties().getPartyList().getDataByIndex(ind).getCandidate() << endl
			<< "Sum of representatives: " << totalDeligatesByParty[ind] << endl
			<< "Sum of votes: " << totalVotesByParty[ind] << endl;
		cout << endl;
	}
}

vector<vector<int>> initVotesArr(int numOfParties, int numOfDistricts) {
	vector<vector<int>> votesArr (numOfDistricts, vector<int>(numOfParties, 0));
	return votesArr;
}

void fillVotesInVotesArrByDistrictAndParty(const ElectionRound& electionRound, vector<vector<int>>& votesArr) {
	for (int i = 0; i < electionRound.getVotes().getVoteList().getlListSize(); i++) {
		votesArr[electionRound.getVotes().getVoteList().getDataByIndex(i).getCitizen().getDistrict()->getSerialNumber() - 1][electionRound.getVotes().getVoteList().getDataByIndex(i).getParty().getSerialNumber() - 1] ++;
	}
}

int getWinnerPartyIndexInDistrict(vector<int>& districtVotesByPartyArr, const int numOfParties, int districtType) {
	int i, winnerIndexParty = 0;
	int max = *(districtVotesByPartyArr.begin());
	for (i = 1; i < numOfParties; i++) {
		if (districtVotesByPartyArr[i] > max) {
			max = districtVotesByPartyArr[i];
			winnerIndexParty = i;
		}
	}
	if (max == 0)
		return -1;
	return winnerIndexParty;
}

int getSumOfVotesInDistrict(vector<int>& districtVotesByPartyArr, const int numOfParties) {
	int sumOfVotes = 0;
	for (int i = 0; i < numOfParties; i++) {
		sumOfVotes += districtVotesByPartyArr[i];
	}
	return sumOfVotes;
}

int getNumOfCitizensInDistrict(const ElectionRound& electionRound, const int districtNumber) {
	int numOfCitizensInDistrict=0;
	for (int i = 0; i < electionRound.getVoterRegister().getCitizenList().getlListSize(); i++) {
		if (electionRound.getVoterRegister().getCitizenList().getDataByIndex(i).getDistrict()->getSerialNumber() == districtNumber) {
			numOfCitizensInDistrict++;
		}
	}
	return numOfCitizensInDistrict;
}

void SortPartyArrByDeligates(vector<int>& totalDeligatesByParty, vector<int>& paritesNSerialNumbersArr, int len)
{
	int i, j;
	for (i = 0; i < len - 1; i++)
		for (j = 0; j < len - i - 1; j++)
			if (totalDeligatesByParty[j] < totalDeligatesByParty[j + 1])
				Utilities<int>::swap(paritesNSerialNumbersArr[j], paritesNSerialNumbersArr[j + 1]);
}
