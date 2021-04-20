#pragma once
#include "vote.h"

//Implement Votes List Handler Class
class VoteListHandler {
	private:
		LinkedList<Vote> _voteList;
	public:
		//Constructors
		VoteListHandler() {};
		VoteListHandler(const VoteListHandler& otherVoteListHandler);
		VoteListHandler(ifstream& in_Binary_file, CitizenListHandler& citizenlistHandler, PartyListHandler& partylistHandler) noexcept(false);
		//Distructor
		~VoteListHandler() {};
		//Getters
		const LinkedList<Vote>& getVoteList() const { return this->_voteList; }

		bool isDoubleVote(const string Id) const;
		void saveBin(ofstream& out_file) const noexcept(false);
};
