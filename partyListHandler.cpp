#include "partyListHandler.h"

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

PartyListHandler::PartyListHandler(const PartyListHandler& otherPartyListHandler) {
	_partyList = otherPartyListHandler._partyList;
}

PartyListHandler::PartyListHandler(ifstream& in_Binary_file, CitizenListHandler& citizenListHandler) noexcept(false)
{
	int numOfParties;
	in_Binary_file.read(rcastc(&numOfParties), sizeof(numOfParties));
	if (!in_Binary_file.good()) {
		throw ios_base::failure("error reading");
	}
	for (int i = 0; i < numOfParties; i++) {
		Party* newParty = new Party(in_Binary_file, citizenListHandler);
		_partyList.add(*newParty);
	}
}

void PartyListHandler::saveBin(ofstream& out_file) const noexcept(false) {
	int partyListSize = _partyList.getlListSize();
	out_file.write(rcastcc(&partyListSize), sizeof(partyListSize));
	if (!out_file.good()) {
		throw ios_base::failure("error writing");
	}
	LinkedList<Party>::LinkedListConstIterator begin = _partyList.cbegin();
	LinkedList<Party>::LinkedListConstIterator end = _partyList.cbegin();
	for (begin; begin != ++end; begin++)
	{
		(*begin).saveBin(out_file);
	}
}