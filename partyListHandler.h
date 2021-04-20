#pragma once
#include "party.h"

//Implement Parties List Handler Class
class PartyListHandler {
	private:
		LinkedList<Party> _partyList;
	public:
		//Constructors
		PartyListHandler() {};
		PartyListHandler(const PartyListHandler& otherPartyListHandler);
		PartyListHandler(ifstream& in_Binary_file, CitizenListHandler& citizenListHandler) noexcept(false);
		//Distructors
		~PartyListHandler() {};
		//Getters
		const LinkedList<Party>& getPartyList() const { return this->_partyList; }

		void saveBin(ofstream& out_file) const noexcept(false);
};