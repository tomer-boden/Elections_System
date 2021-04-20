#include "vote.h"

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

Vote::Vote(const Citizen& citizen, const Party& party) : _party(const_cast<Party*>(&party)), _citizen(const_cast<Citizen*>(&citizen))
{
}

Vote::Vote(const Vote& vote) : _citizen(const_cast<Citizen*>(vote._citizen)), _party(const_cast<Party*>(vote._party))
{
}

Vote::Vote(ifstream& in_Binary_file,CitizenListHandler& citizenList, PartyListHandler& partylist) noexcept(false)
{
	string citizenId;
	int partyIndex;
	in_Binary_file.read(const_cast<char*>(citizenId.c_str()), sizeof(citizenId));
	in_Binary_file.read(rcastc(&partyIndex), sizeof(partyIndex));
	if (!in_Binary_file.good()) {
		throw ios_base::failure("error reading");
	}
	_citizen = const_cast<Citizen*>(&citizenList.getCitizenByID(citizenId));
	_party = const_cast<Party*>(&partylist.getPartyList().getDataByIndex(partyIndex-1));
}

bool Vote::setCitizen(const Citizen& citizen) {
	this->_citizen = const_cast<Citizen*>(&citizen);
	return true;
}

bool Vote::SetParty(const Party& party) {
	this->_party = const_cast<Party*>(&party);
	return true;
} 

void Vote::saveBin(ofstream& out_file) const noexcept(false) {
	string citizenId = _citizen ->getId();
	int partyIndex = _party -> getSerialNumber();
	out_file.write(citizenId.c_str(), sizeof(citizenId));
	out_file.write(rcastcc(&partyIndex), sizeof(partyIndex));
	if (!out_file.good()) {
		throw ios_base::failure("error writing");
	}
}