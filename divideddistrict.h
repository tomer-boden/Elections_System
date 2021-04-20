#pragma once
#include "district.h"

extern int TypeDividedDistrict;

class DividedDistrict : public District {
	public:
		DividedDistrict(const string _name, const int _serialNumber, const int _numOfRepresentatives);
		DividedDistrict(const DividedDistrict& otherDividedDistrict);
		DividedDistrict(ifstream& in_Binary_file);
		virtual ~DividedDistrict() {};

		virtual const DividedDistrict& operator=(const DividedDistrict& otherDividedDistrictr);
		virtual void toOs(ostream& os) const override;
		virtual void saveBin(ofstream& out_file) const noexcept(false);
};
