#include "district.h"
#include "utilities.h"

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

District::District(const string name, const int serialNumber, const int numOfRepresentatives) noexcept(false) : _name(name), _serialNumber(serialNumber), _numOfRepresentatives(numOfRepresentatives)
{
	validateNumOfRepresentatives(numOfRepresentatives);
}

District::District(const District& otherDistrict)
{	
	*this = otherDistrict;
}

District::District(ifstream& in_Binary_file) noexcept(false) {
	int serialNumber, numOfRepresentatives;
	in_Binary_file.read(const_cast<char*>(_name.c_str()), sizeof(_name));
	in_Binary_file.read(rcastc(&serialNumber), sizeof(serialNumber));
	in_Binary_file.read(rcastc(&numOfRepresentatives), sizeof(numOfRepresentatives));
	if (!in_Binary_file.good()) {
		throw ios_base::failure("error reading");
	}
	validateNumOfRepresentatives(numOfRepresentatives);
	_serialNumber = serialNumber;
	_numOfRepresentatives = numOfRepresentatives;
}

void District::setName(const string name) {
	this->_name = name;
}

void District::setSerialNumber(const int serialNumber) {
	this->_serialNumber = serialNumber;
}

void District::setNumOfRepresentatives(const int numOfRepresentatives) {
	validateNumOfRepresentatives(numOfRepresentatives);
	this->_numOfRepresentatives = numOfRepresentatives;
}

const District& District::operator=(const District& otherDistrict) {
	this->_name = otherDistrict._name;
	this->_serialNumber = otherDistrict._serialNumber;
	this->_numOfRepresentatives = otherDistrict._numOfRepresentatives;
	return *this;
}

ostream& operator<<(ostream& os, const District& district) {
	os << "Distict type: "; 
	district.toOs(os);
	os << " --> " << "Name: " << district._name << " , " << "Serial number: " << district._serialNumber << " , " << "Num of representatives: " << district._numOfRepresentatives << endl;
	return os;
}

void District::saveBin(ofstream& out_file) const noexcept(false) {
	out_file.write(_name.c_str(), sizeof(_name));
	out_file.write(rcastcc(&_serialNumber), sizeof(_serialNumber));
	out_file.write(rcastcc(&_numOfRepresentatives), sizeof(_numOfRepresentatives));
	if (!out_file.good()) {
		throw ios_base::failure("error writing");
	}
}

void District::validateNumOfRepresentatives(const int numOfRepresentatives) noexcept(false) {
	if (numOfRepresentatives < 0) {
		throw invalid_argument("Invalid num of representatives");
	}
}