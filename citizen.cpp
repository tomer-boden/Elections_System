#include "citizen.h"
#include "utilities.h"

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

Citizen::Citizen(const string name, const string Id, const int birthYear, const District* district) noexcept(false) : _name(name), _Id(Id), _birthYear(birthYear), _district(const_cast<District*>(district)) //We pass a district as a constant variable because it is not changed so we have eliminated the constant
{
	validateId(Id);
	validateBirthYear(birthYear);
}

Citizen::Citizen(const Citizen& otherCitizen) : _name(otherCitizen._name), _Id(otherCitizen._Id), _birthYear(otherCitizen._birthYear), _district(const_cast<District*>(otherCitizen._district))
{
}

Citizen::Citizen(ifstream& in_Binary_file, int& IdDistrict) noexcept(false)
{
	int nameSize , birthYear;
	in_Binary_file.read(const_cast<char*>(_name.c_str()), sizeof(_name));
	in_Binary_file.read(const_cast<char*>(_Id.c_str()), sizeof(_Id));
	in_Binary_file.read(rcastc(&birthYear), sizeof(birthYear));
	in_Binary_file.read(rcastc(&IdDistrict), sizeof(IdDistrict));
	if (!in_Binary_file.good()) {
		throw ios_base::failure("error reading");
	}
	_birthYear = birthYear;
	_district = nullptr;
}

void Citizen::setName(const string name) {
	this->_name = name;
}

void Citizen::setId(const string Id) noexcept(false) {
	validateId(Id);
	this->_Id = Id;
}

void Citizen::setBirthYear(const int birthYear) noexcept(false) {
	validateBirthYear(birthYear);
	this->_birthYear = _birthYear;
}

void Citizen::setDistrict(const District* district) {
	this->_district = const_cast<District*>(district);
}

bool Citizen::operator==(const Citizen& other) {
	return _Id == other._Id;
}

const Citizen& Citizen::operator=(const Citizen& citizen) {
	this->_name = citizen._name;
	this->_Id = citizen._Id;
	this->_birthYear = citizen._birthYear;
	this->_district = const_cast<District*>(citizen._district);
	return *this;
}

ostream& operator<<(ostream& os, const Citizen& citizen) {
	os << "Name: " << citizen._name << " , " << "Id: " << citizen._Id << " , " << "Birth year: " << citizen._birthYear << " , " << "District: " << citizen._district->getName() << endl;
	return os;
}

void Citizen::saveBin(ofstream& out_file) const noexcept(false) {
	out_file.write(_name.c_str(), sizeof(_name));
	out_file.write(_Id.c_str(), sizeof(_Id));
	out_file.write(rcastcc(&_birthYear), sizeof(_birthYear));
	int IdDistrict = _district->getSerialNumber();
	out_file.write(rcastcc(&IdDistrict), sizeof(IdDistrict));
	if (!out_file.good()) {
		throw ios_base::failure("error writing");
	}
}

void Citizen::validateId(const string Id) noexcept(false) {
	if (Id.length() != 9)
		throw invalid_argument("Invalid Id");
}

void Citizen::validateBirthYear(const int birthYear) noexcept(false) {
	if (birthYear<0)
		throw invalid_argument("Invalid birthYear");
}