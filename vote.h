#pragma once
#include "citizen.h"
#include "partyListHandler.h"

class Vote
{
	private:
		Citizen* _citizen;
		Party* _party;
	public:
		//Constructos
		Vote(const Citizen& citizen, const Party& party);
		Vote(const Vote& vote);
		Vote(ifstream& in_Binary_file, CitizenListHandler& citizenList, PartyListHandler& partylist) noexcept(false);
		//Getters
		const Citizen& getCitizen() const { return *this->_citizen; }
		const Party getParty() const { return *this->_party; }
		//Setters
		bool setCitizen(const Citizen& citizen);
		bool SetParty(const Party& party);

		const Vote& operator=(const Vote& vote) = delete;
		void saveBin(ofstream& out_file) const noexcept(false);
};