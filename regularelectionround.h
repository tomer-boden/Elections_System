#pragma once
#include "electionRound.h"
#include "districtListHandler.h"

extern int TypeRegularElectionRound;

class RegularElectionRound : public ElectionRound {
	private:
		DistrictListHanlder _districts;

	public:
		//constructors
		RegularElectionRound(const Date& date);
		RegularElectionRound(const RegularElectionRound& otherRegularElectionRound) = delete;
		RegularElectionRound(ifstream& in_Binary_file, DistrictListHanlder& districtlist);
		//distructors
		virtual ~RegularElectionRound() {};
		//getters
		const DistrictListHanlder& getDistricts() const { return this->_districts; }

		void addDistrict(const District* district);
		virtual void saveBin(ofstream& out_file) const noexcept(false);
};


