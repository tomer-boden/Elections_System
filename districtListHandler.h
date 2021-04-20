#pragma once
#include <typeinfo>
#include "linkedList.h"
#include "uniondistrict.h"
#include "divideddistrict.h"

//Implement District List Handler Class
class DistrictListHanlder {
	private:
		LinkedList<District> _districtList;
	public:
		//Constructors
		DistrictListHanlder() {};
		DistrictListHanlder(const DistrictListHanlder& otherDistrictListHandler);
		DistrictListHanlder(ifstream& in_Binary_file) noexcept(false);
		//Distructors
		~DistrictListHanlder() {};
		//Getters
		const LinkedList<District>& getDistrictList() const { return this->_districtList; };
		const int getDistrictTypeFromBinaryFile(ifstream& in_Binary_file);
		void saveBin(ofstream& out_file) const noexcept(false);
};
