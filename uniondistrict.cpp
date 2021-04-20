#include "uniondistrict.h"

int TypeUnionDistrict = 1;

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>


UnionDistrict::UnionDistrict(const string name, const int serialNumber, const int numOfRepresentatives): District(name,serialNumber,numOfRepresentatives)
{
}

UnionDistrict::UnionDistrict(const UnionDistrict& otherUnionDistrict) : District(otherUnionDistrict)
{
}

UnionDistrict::UnionDistrict(ifstream& in_Binary_file) : District(in_Binary_file)
{
}

const UnionDistrict& UnionDistrict::operator=(const UnionDistrict& otherUnionDistrict) {
	District::operator=(otherUnionDistrict);
	return *this;
}


void UnionDistrict::toOs(ostream& os) const
{
	os << typeid(*this).name() + 6;
}

void UnionDistrict::saveBin(ofstream& out_file) const noexcept(false) {
	out_file.write(rcastcc(&TypeUnionDistrict), sizeof(TypeUnionDistrict));
	if (!out_file.good()) {
		throw ios_base::failure("error writing");
	}
	District::saveBin(out_file);
}
