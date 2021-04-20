#include "electionRound.h"

ElectionRound::ElectionRound(const Date& date)
{
	_date = new Date(date); 
}

ElectionRound::~ElectionRound() {
	delete _date;
}

ElectionRound::ElectionRound(ifstream& in_Binary_file, DistrictListHanlder& districtlist) noexcept(false) {
	_date = new Date(in_Binary_file);
	_voterRegister = CitizenListHandler(in_Binary_file, districtlist);
	_parties = PartyListHandler(in_Binary_file, _voterRegister);
	_votes =  VoteListHandler(in_Binary_file, _voterRegister, _parties);
}

void ElectionRound::setDate(const Date& date) {
	try {
		_date->setDay(date.getDay());
		_date->setMonth(date.getMonth());
		_date->setYear(date.getYear());
	}
	catch (invalid_argument e) {
		cout << e.what() << endl;
	}
}

void ElectionRound::addCitizen(const Citizen& citizen) {
	Citizen* newcCitizen = new Citizen(citizen);
	const_cast<LinkedList<Citizen>&>(_voterRegister.getCitizenList()).add(*newcCitizen);
}

void ElectionRound::addParty(const Party& party) {
	Party* newParty = new Party(party);
	const_cast<LinkedList<Party>&>(_parties.getPartyList()).add(*newParty);
}

void ElectionRound::addVote(const Vote& vote) {
	Vote* newVote = new Vote(vote);
	const_cast<LinkedList<Vote>&>(_votes.getVoteList()).add(*newVote);
}
void ElectionRound::saveBin(ofstream& out_file) const noexcept(false) {
	_date->saveBin(out_file);
	_voterRegister.saveBin(out_file);
	_parties.saveBin(out_file);
	_votes.saveBin(out_file);
}