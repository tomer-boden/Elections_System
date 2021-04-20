#pragma once
#include <iostream>
#include <fstream>
using namespace std;

class District
{
	protected:
		string _name;
		int _serialNumber;
		int _numOfRepresentatives;

		//validation
		void validateNumOfRepresentatives(const int numOfRepresentatives) noexcept(false);
	public:
		//Constructor
		District(const string name, const int serialNumber, const int numOfRepresentatives) noexcept(false);
		District(const District& otherDistrict);
		District(ifstream& in_Binary_file) noexcept(false);
		//Distructor
		virtual ~District() {};
		//Getters
		const string getName() const { return this->_name; }
		const int getSerialNumber() const { return this->_serialNumber; }
		const int getNumOfRepresentatives() const { return this->_numOfRepresentatives; }
		//Setters
		void setName(const string name);
		void setSerialNumber(const int serialNumber);
		void setNumOfRepresentatives(const int numOfRepresentatives);

		virtual const District& operator=(const District& otherDistrict);
		virtual void toOs(ostream& os) const = 0;
		friend ostream& operator<<(ostream& os, const District& district);
		virtual void saveBin(ofstream& out_file) const noexcept(false);
};