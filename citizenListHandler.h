#pragma once
#include "citizen.h"
#include "districtListHandler.h"
#include "linkedList.h"
#include <fstream>

//Implement Citizen List Handler Class
class CitizenListHandler {
private:
	LinkedList<Citizen> _citizenList;
public:
	//Constructors
	CitizenListHandler() {};
	CitizenListHandler(const CitizenListHandler& otherCitizenListHandler);
	CitizenListHandler(ifstream& in_Binary_file, DistrictListHanlder& districtListHandler) noexcept(false);
	//Distructors
	~CitizenListHandler() {};
	//Getters
	const LinkedList<Citizen>& getCitizenList() const { return this->_citizenList; };
	const Citizen& getCitizenByID(const string Id) const;
	bool IsCitizenExist(const string Id) const; 
	void saveBin(ofstream& out_file) const noexcept(false);
};

