#include "regularelectionround.h"

int TypeRegularElectionRound = 0;

#define rcastcc reinterpret_cast<const char*>


RegularElectionRound::RegularElectionRound(const Date& date) : ElectionRound(date)
{
}

RegularElectionRound::RegularElectionRound(ifstream& in_Binary_file, DistrictListHanlder& districtlist) : ElectionRound(in_Binary_file, districtlist) {
	_districts = districtlist;
}

void RegularElectionRound::addDistrict(const District* district) {
	const_cast<LinkedList<District>&>(_districts.getDistrictList()).add(*district);
}

void RegularElectionRound::saveBin(ofstream& out_file) const noexcept(false) {
	out_file.write(rcastcc(&TypeRegularElectionRound), sizeof(TypeRegularElectionRound));
	if (!out_file.good()) {
		throw ios_base::failure("error writing");
	}
	_districts.saveBin(out_file);
	ElectionRound::saveBin(out_file);
}