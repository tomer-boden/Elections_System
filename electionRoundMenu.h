#pragma once
#include "regularelectionround.h"
#include "simpleelectionround.h"
#include "utilities.h"
#include <typeinfo>
#include <vector>
#include <string>


const extern int ERROR;
const extern int LEGALITY_AGE;
const extern int ID_LEN;

void MainMenu(); // main menu
void displayMainMenu(); // display main nenu
void AddNewElectionRound(ElectionRound*& electionRound) noexcept(false);  // add new election round
void SaveElectionRound(const ElectionRound& electionRound); // save election round
void LoadExistsElectionRound(ElectionRound*& electionRound) noexcept(false); // load exists election round
void electionRoundMenu(ElectionRound*& electionRound); // election round menu;
void introduce(ElectionRound& electionRound); //display introducing message
void displayManageMainMenu(); //display manage main menu
void Menu(ElectionRound*& electionRound, int& optionInput); //menu of action in election round
void returnToMainMenu(); // display message for return to main menu
void AddDistrict(ElectionRound& electionRound) noexcept(false); // add district to electionRound
void getDistrictInputFromUser(string& name, int& numOfDelegates,int& districtType) noexcept(false); // get district input from user
void AddCitizen(ElectionRound& electionRound) noexcept(false); // add citizen to electionRound
void getCitizenInputFromUser(const ElectionRound& electionRound, string& name, string& id, int& birthYear, int& SrialNumberDistrict) noexcept(false); //get citizen input from user
void AddParty(ElectionRound& electionRound); // add party to electionRound
void getPartyInputFromUser(ElectionRound& electionRound, string& name, string& candidateId) noexcept(false); //get party input from user
bool isDoubleCandidate(const ElectionRound& electionRound, string& represenId); // check is double candidate to several parties simultaneously
void AddVote(ElectionRound& electionRound); // add vote to electionRound
void getVoteInputFromUser(const ElectionRound& electionRound, string& Id, int& partySrialNumber) noexcept(false); //get vote input from user
void addRepresentAsAPartyCitizen(ElectionRound& electionRound); //add represent as a party citizen
void getCitizenAsAPartyRepresentFromUserInput(const ElectionRound& electionRound, string& represenId, int& partySrialNumber, int& srialNumberDistrict) noexcept(false); //get citizen as a party represent from user input
bool isDoubleRepresentative(const ElectionRound& electionRound, string& represenId); // check is double representative to several districts in parties simultaneously
void DisplayAllDisticts(const ElectionRound& electionRound); //display all districts
void DisplayAllCitizens(const ElectionRound& electionRound); //display all citizens
void DisplayAllParties(const ElectionRound& electionRound); ////display all parties
Date* GetElectionRoundDateFromUserInput(); //Get election round date from user input
void ShowElectionResults(const ElectionRound& electionRound) noexcept(false); //display election results
void ShowRegularElectionRoundResults(const ElectionRound& electionRound, int numOfParties, int numOfDistricts, vector<vector<int>>& votesArr, vector<int>& totalDeligatesByParty); //Show regular election round results
void ShowSimpleElectionRoundResults(const ElectionRound& electionRound, int numOfParties, vector<vector<int>>& votesArr, vector<int>& totalDeligatesByParty) noexcept(false); // Show simple election round results
void ShowDistrictsResults(const ElectionRound& electionRound, int numOfParties, int numOfDistricts, vector<vector<int>>& votesArr, vector<int>& totalDeligatesByParty); //display election results by districts
void calulateNumOfDelegatesForParty(int districtnumOfDelegates, int sumOfVotes, int numOfParties, vector<int>& districtVotesByPartyArr, vector<int>& numOfDelegatesForParty); // calulate num of delegates for party
void showPartiesResults(const ElectionRound& electionRound, vector<int>& totalDeligatesByParty, int numOfParties, int numOfDistricts, vector<vector<int>> votesArr); //display election results by parties
vector<vector<int>> initVotesArr(int numOfParties, int numOfDistricts); //init votes arr
void fillVotesInVotesArrByDistrictAndParty(const ElectionRound& electionRound, vector<vector<int>>& votesArr); //fill votes in votes arr by district and party
int getWinnerPartyIndexInDistrict(vector<int>& districtVotesByPartyArr, const int numOfParties,int districtType); //get winner party index in district
int getSumOfVotesInDistrict(vector<int>& districtVotesByPartyArr, const int numOfParties); //get sum of votes in district
int getNumOfCitizensInDistrict(const ElectionRound& electionRound, const int districtNumber); //get num Of citizens in district
void SortPartyArrByDeligates(vector<int>& totalDeligatesByParty, vector<int>& paritesNSerialNumbersArr, int len); // sort party arr by deligates
