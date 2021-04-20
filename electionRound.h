#pragma once
#include "date.h"
#include "citizenListHandler.h"
#include "partyListHandler.h"
#include "voteListHandler.h"

class ElectionRound {
	protected:
		Date* _date;
		CitizenListHandler _voterRegister;
		PartyListHandler _parties;
		VoteListHandler _votes;
	public:
		//Constructor
		ElectionRound(const Date& date);
		ElectionRound(const ElectionRound& otherElectionRound) = delete;
		ElectionRound(ifstream& in_Binary_file, DistrictListHanlder& districtlist) noexcept(false);
		//Distructor
		virtual ~ElectionRound();
		//Getters
		const Date& getDate() const { return *this->_date; }
		const CitizenListHandler& getVoterRegister() const { return this->_voterRegister; }
		const PartyListHandler& getParties() const { return this->_parties; }
		const VoteListHandler& getVotes() const { return this->_votes; }
		//setter
		void setDate(const Date& date) noexcept(false);

		void addCitizen(const Citizen& citizen);
		void addParty(const Party& party);
		void addVote(const Vote& vote); 

		virtual const ElectionRound& operator=(const ElectionRound& electionRound) = delete;
		virtual void saveBin(ofstream& out_file) const noexcept(false);
		
};
