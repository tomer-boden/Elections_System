#include "voteListHandler.h"

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

VoteListHandler::VoteListHandler(const VoteListHandler& otherVoteListHandler) {
	_voteList = otherVoteListHandler._voteList;
}

VoteListHandler::VoteListHandler(ifstream& in_Binary_file, CitizenListHandler& citizenlistHandler, PartyListHandler& partylistHandler) noexcept(false)
{
	int numOfVotes;
	in_Binary_file.read(rcastc(&numOfVotes), sizeof(numOfVotes));
	if (!in_Binary_file.good()) {
		throw ios_base::failure("error reading");
	}
	for (int i = 0; i < numOfVotes; i++) {
		Vote* newVote = new Vote(in_Binary_file, citizenlistHandler, partylistHandler);
		_voteList.add(*newVote);
	}
}

bool VoteListHandler::isDoubleVote(const string Id) const {
	LinkedList<Vote>::LinkedListConstIterator begin = _voteList.cbegin();
	LinkedList<Vote>::LinkedListConstIterator end = _voteList.cbegin();
	for (begin; begin != ++end; begin++)
	{
		if ((*begin).getCitizen().getId().compare(Id) == 0)
			return  true;
	}
	return false;
}

void VoteListHandler::saveBin(ofstream& out_file) const noexcept(false) {
	int VoteListSize = _voteList.getlListSize();
	out_file.write(rcastcc(&VoteListSize), sizeof(VoteListSize));
	if (!out_file.good()) {
		throw ios_base::failure("error writing");
	}
	LinkedList<Vote>::LinkedListConstIterator begin = _voteList.cbegin();
	LinkedList<Vote>::LinkedListConstIterator end = _voteList.cbegin();
	for (begin; begin != ++end; begin++)
	{
		(*begin).saveBin(out_file);
	}
}