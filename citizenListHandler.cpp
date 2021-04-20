#include "citizenListHandler.h"

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>


CitizenListHandler::CitizenListHandler(const CitizenListHandler& otherCitizenListHandler) {
	_citizenList = otherCitizenListHandler._citizenList;
}

CitizenListHandler::CitizenListHandler(ifstream& in_Binary_file, DistrictListHanlder& districtListHandler) noexcept(false) {
	int DistirctId , numOfCitizens;
	in_Binary_file.read(rcastc(&numOfCitizens), sizeof(numOfCitizens));
	if (!in_Binary_file.good()) {
		throw ios_base::failure("error reading");
	}
	for (int i = 0; i < numOfCitizens; i++) {
		Citizen* newCitizen = new Citizen(in_Binary_file, DistirctId);
		newCitizen->setDistrict(&districtListHandler.getDistrictList().getDataByIndex(DistirctId - 1));
		_citizenList.add(*newCitizen);
	}
}

bool CitizenListHandler::IsCitizenExist(const string Id) const {
	LinkedList<Citizen>::LinkedListConstIterator begin = _citizenList.cbegin();
	LinkedList<Citizen>::LinkedListConstIterator end = _citizenList.cbegin();
	for (begin; begin != ++end; begin++)
	{
		if ((*begin).getId().compare(Id)==0)
			return  true;
	}
	return false;
}

const Citizen& CitizenListHandler::getCitizenByID(const string Id) const {
	LinkedList<Citizen>::LinkedListConstIterator begin = _citizenList.cbegin();
	LinkedList<Citizen>::LinkedListConstIterator end = _citizenList.cbegin();
	for (begin; begin != ++end; begin++)
	{
		if ((*begin).getId().compare(Id) == 0)
			return  *begin;
	}
}

void CitizenListHandler::saveBin(ofstream& out_file) const noexcept(false) {
	int citizenListSize = _citizenList.getlListSize();
	out_file.write(rcastcc(&citizenListSize), sizeof(citizenListSize));
	if (!out_file.good()) {
		throw ios_base::failure("error writing");
	}
	LinkedList<Citizen>::LinkedListConstIterator begin = _citizenList.cbegin();
	LinkedList<Citizen>::LinkedListConstIterator end = _citizenList.cbegin();
	for (begin; begin != ++end; begin++)
	{
		(*begin).saveBin(out_file);
	}
}
