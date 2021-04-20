#pragma once
#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include "district.h"
using namespace std;

class Citizen {
	private:
		string _name;
		string _Id;
		int _birthYear;
		District* _district;

		//validation
		void validateId(const string Id) noexcept(false);
		void validateBirthYear(const int birthYear) noexcept(false);
	public:
		//Constructors
		Citizen(const string name, const string Id, const int birthYear, const District* district = nullptr) noexcept(false);
		Citizen(const Citizen& otherCitizen);
		Citizen(ifstream& in_Binary_file, int& IdDistrict) noexcept(false);
		//Distructor
		~Citizen() {};
		//Getters
		const string getName() const { return this->_name; }
		const string getId() const { return this->_Id; }
		const int getBirthYear() const { return this->_birthYear; }
		const District* getDistrict() const { return this->_district; }
		//Setters
		void setName(const string name);
		void setId(const string Id) noexcept(false);
		void setBirthYear (const int birthYear) noexcept(false);
		void setDistrict(const District* district);

		const Citizen& operator=(const Citizen& citizen); //Placement operator
		bool operator==(const Citizen& other);
		friend ostream& operator<<(ostream& os, const Citizen& citizen); //Print operator
		void saveBin(ofstream& out_file) const noexcept(false);

};