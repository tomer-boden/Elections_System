#include "divideddistrict.h"

int TypeDividedDistrict = 0;

#define rcastcc reinterpret_cast<const char*>

DividedDistrict::DividedDistrict(const string name, const int serialNumber, const int numOfRepresentatives) : District(name, serialNumber, numOfRepresentatives)
{
}

DividedDistrict::DividedDistrict(const DividedDistrict& otherDividedDistrict) : District(otherDividedDistrict)
{
}

DividedDistrict::DividedDistrict(ifstream& in_Binary_file) : District(in_Binary_file)
{
}

const DividedDistrict& DividedDistrict::operator=(const DividedDistrict& otherDividedDistrict) {
	District::operator=(otherDividedDistrict);
	return *this;
}

void DividedDistrict::toOs(ostream& os) const
{
	os << typeid(*this).name() + 6;
}

void DividedDistrict::saveBin(ofstream& out_file) const {
	out_file.write(rcastcc(&TypeDividedDistrict), sizeof(TypeDividedDistrict));
	if (!out_file.good()) {
		throw ios_base::failure("error writing");
	}
	District::saveBin(out_file);
}
