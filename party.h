#pragma once
#include <vector>
#include <string>
#include "citizenListHandler.h"

class Party {
	private:
		string _name;
		int _serialNumber;
		Citizen* _candidate = nullptr;
		vector<CitizenListHandler> _representListByDistrictArr;
		
	public:
		//Constructors
		Party(const string name, const int serialNumber, const Citizen* candidate);
		Party(const Party& otherParty);
		Party(ifstream& in_Binary_file, CitizenListHandler& citizenList) noexcept(false);
		//Distructor
		~Party() {};
		//Getters
		const string getName() const { return this->_name; }
		const int getSerialNumber() const { return this->_serialNumber; }
		const Citizen& getCandidate() const { return *this->_candidate; }
		const vector<CitizenListHandler>& getRepresentListByDistrictArr() const { return this->_representListByDistrictArr; }
		
		//Setters
		void setName(const string name);
		void setSerialNumber(const int serialNumber);
		void setCandidate(const Citizen& candidate);

		void addDistrictToRepresentListByDistrictArr(const int districtSerialNumber); //add district as organ in array and init empty represent list to it.
		void addCitizenAsAPartyRepresent(const Citizen& citizen, const int districtSerialNumber); //add citizen as a party represent in district by district serial number

		const Party& operator=(const Party& party);
		friend ostream& operator<<(ostream& os, const Party& party);
		void saveBin(ofstream& out_file) const noexcept(false);
};