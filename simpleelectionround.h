#pragma once
#include "electionRound.h"
#include "divideddistrict.h"

extern int TypeSimpleElectionRound;

class SimpleElectionRound : public ElectionRound {
	private:
		DividedDistrict _dividedDistrict;
	public:
		//constructors
		SimpleElectionRound(const Date& date, const DividedDistrict& _dividedDistrict);
		SimpleElectionRound(const SimpleElectionRound& otherSimpleElectionRound) = delete;
		SimpleElectionRound(ifstream& in_Binary_file, DistrictListHanlder& districtlist);
		//distructors
		virtual ~SimpleElectionRound();
		//getters
		DividedDistrict& getDividedDistrict() { return this->_dividedDistrict; }
		int getNumOfRepresentatives() { return _dividedDistrict.getNumOfRepresentatives(); }
		
		virtual void saveBin(ofstream& out_file) const noexcept(false);
};