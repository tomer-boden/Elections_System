#include "districtListHandler.h"

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>


DistrictListHanlder::DistrictListHanlder(const DistrictListHanlder& otherDistrictListHandler) {
	_districtList = otherDistrictListHandler._districtList;
}

DistrictListHanlder::DistrictListHanlder(ifstream& in_Binary_file) noexcept(false) {
	District* newDistict = nullptr;
	int DistrictType, numOfDistricts;
	in_Binary_file.read(rcastc(&numOfDistricts), sizeof(numOfDistricts));
	for (int i = 0; i < numOfDistricts; i++) {
		in_Binary_file.read(rcastc(&DistrictType), sizeof(DistrictType));
		if (!in_Binary_file.good()) {
			throw ios_base::failure("error reading");
		}
		if (DistrictType == TypeUnionDistrict)
			newDistict = new UnionDistrict(in_Binary_file);
		else
			newDistict = new DividedDistrict(in_Binary_file);
		_districtList.add(*newDistict);
	}
}

const int DistrictListHanlder::getDistrictTypeFromBinaryFile(ifstream& in_Binary_file) {
	int DistrictType;
	in_Binary_file.read((char*)&DistrictType, sizeof(DistrictType));
	return DistrictType;
}

void DistrictListHanlder::saveBin(ofstream& out_file) const noexcept(false) {
	int districtListSize = _districtList.getlListSize();
	out_file.write(rcastcc(&districtListSize), sizeof(districtListSize));
	LinkedList<District>::LinkedListConstIterator begin = _districtList.cbegin();
	LinkedList<District>::LinkedListConstIterator end = _districtList.cbegin();
	for (begin; begin != ++end; begin++)
	{
		UnionDistrict* unionDistrict = dynamic_cast<UnionDistrict*>(&const_cast<District&>((*begin)));
		if (unionDistrict) {
			unionDistrict->saveBin(out_file);
		}
		else {
			DividedDistrict* dividedDistrict = dynamic_cast<DividedDistrict*>(&const_cast<District&>((*begin)));
			if (dividedDistrict)
				dividedDistrict->saveBin(out_file);
		}
	}
	if (!out_file.good()) {
		throw ios_base::failure("error writing");
	}
}
