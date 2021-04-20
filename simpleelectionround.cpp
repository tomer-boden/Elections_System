#include "simpleelectionround.h"

int TypeSimpleElectionRound = 1;

#define rcastcc reinterpret_cast<const char*>

SimpleElectionRound::SimpleElectionRound(const Date& date, const DividedDistrict& dividedDistrict) : ElectionRound(date) , _dividedDistrict(dividedDistrict)
{
}

SimpleElectionRound::SimpleElectionRound(ifstream& in_Binary_file, DistrictListHanlder& districtlist) : ElectionRound(in_Binary_file, districtlist) , _dividedDistrict(dynamic_cast<DividedDistrict&>(const_cast<District&>((districtlist.getDistrictList().getDataByIndex(0)))))
{
}

SimpleElectionRound::~SimpleElectionRound() {
}

void SimpleElectionRound::saveBin(ofstream& out_file) const noexcept(false) {
	out_file.write(rcastcc(&TypeSimpleElectionRound), sizeof(TypeSimpleElectionRound));
	int numOfRep = _dividedDistrict.getNumOfRepresentatives();
	out_file.write(rcastcc(&numOfRep), sizeof(numOfRep));
	if (!out_file.good()) {
		throw ios_base::failure("error writing");
	}
	ElectionRound::saveBin(out_file);
}