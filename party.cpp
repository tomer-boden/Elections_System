#include "party.h"
#include "utilities.h"

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

Party::Party(const string name, const int serialNumber, const Citizen* candidate) : _name(name), _serialNumber(serialNumber), _candidate(const_cast<Citizen*>(candidate))
{
	this->_representListByDistrictArr.push_back(CitizenListHandler());
}

Party::Party(const Party& otherParty) : _name(otherParty._name), _serialNumber(otherParty._serialNumber), _candidate(const_cast<Citizen*>(otherParty._candidate)), _representListByDistrictArr(otherParty._representListByDistrictArr)
{
}

Party::Party(ifstream& in_Binary_file,CitizenListHandler& citizenList) noexcept(false) {
	int len, serialNumber, numOfcitizens, Psize, lSize;
	string candidateId;
	in_Binary_file.read(const_cast<char*>(_name.c_str()), sizeof(_name));
	in_Binary_file.read(rcastc(&serialNumber), sizeof(serialNumber));
	in_Binary_file.read(const_cast<char*>(candidateId.c_str()), sizeof(candidateId));
	in_Binary_file.read(rcastc(&Psize), sizeof(Psize));
	in_Binary_file.read(rcastc(&lSize), sizeof(lSize));
	if (!in_Binary_file.good()) {
		throw ios_base::failure("error reading");
	}
	_serialNumber = serialNumber;
	_candidate = const_cast<Citizen*>(&citizenList.getCitizenByID(candidateId));
	for (int i = 0; i < lSize; i++) {
		this->_representListByDistrictArr.push_back(CitizenListHandler());
	}
	for (int i = 0; i < lSize; i++) {
		in_Binary_file.read(rcastc(&numOfcitizens), sizeof(numOfcitizens));
		for (int j = 0; j < numOfcitizens; j++) {
			in_Binary_file.read(const_cast<char*>(candidateId.c_str()), sizeof(candidateId));
			const Citizen& citizen = citizenList.getCitizenByID(candidateId);
			addCitizenAsAPartyRepresent(citizen, i);
		}
	}
}

void Party::setName(const string name) {
	this->_name = name;
}

void Party::setSerialNumber(const int serialNumber) {
	this->_serialNumber = serialNumber;
}

void Party::setCandidate(const Citizen& candidate) {
	this->_candidate = const_cast<Citizen*>(&candidate);
}

void Party::addDistrictToRepresentListByDistrictArr(int districtSerialNumber) {
	if (districtSerialNumber >= _representListByDistrictArr.capacity()) {
		_representListByDistrictArr.resize(districtSerialNumber+1);
	}
}

void Party::addCitizenAsAPartyRepresent(const Citizen& citizen, const int districtSerialNumber) {
	const_cast<LinkedList<Citizen>&>(_representListByDistrictArr[districtSerialNumber].getCitizenList()).add(citizen);
}

const Party& Party::operator=(const Party& otherParty) {
	this->_name = otherParty._name;
	this->_serialNumber = otherParty._serialNumber;
	this->_candidate = otherParty._candidate;
	this->_representListByDistrictArr = otherParty._representListByDistrictArr;
	return *this;
}

ostream& operator<<(ostream& os, const Party& party) {
	os << "Name: " << party._name << " , " << "Serial number: " << party._serialNumber << " , " << "Candidate: " << *party._candidate << endl
		<< "Districts Represent list: " << endl ;
	for (int i = 0; i < party._representListByDistrictArr.size(); i++) {
		os << "District " << i+1 << ": " << endl;
		if (party._representListByDistrictArr[i].getCitizenList().getlListSize())
			 os << party._representListByDistrictArr[i].getCitizenList() ;
		os << endl;
	}
	return os;
}

void Party::saveBin(ofstream& out_file) const noexcept(false) {
	int pSize = _representListByDistrictArr.capacity();
	int lSize = _representListByDistrictArr.size();
	string candidateId = _candidate->getId();
	out_file.write(_name.c_str(), sizeof(_name));
	out_file.write(rcastcc(&_serialNumber), sizeof(_serialNumber));
	out_file.write(candidateId.c_str(), sizeof(candidateId));
	out_file.write(rcastcc(&pSize), sizeof(pSize));
	out_file.write(rcastcc(&lSize), sizeof(lSize));
	for (int i = 0; i < lSize; i++) {
		int numOfCitizens = _representListByDistrictArr[i].getCitizenList().getlListSize();
		out_file.write(rcastcc(&numOfCitizens), sizeof(numOfCitizens));
		for (int j = 0; j < numOfCitizens; j++) {
			string citizenId = _representListByDistrictArr[i].getCitizenList().getDataByIndex(j).getId();
			out_file.write(citizenId.c_str(), sizeof(citizenId));
		}
	}
	if (!out_file.good()) {
		throw ios_base::failure("error writing");
	}
}