#pragma once
#include "district.h"

extern int TypeUnionDistrict;

class UnionDistrict : public District {

	public:
		UnionDistrict(const string _name, const int _serialNumber, const int _numOfRepresentatives);
		UnionDistrict(const UnionDistrict& otherUnionDistrict);
		UnionDistrict(ifstream& in_Binary_file);
		virtual ~UnionDistrict() {};

		virtual const UnionDistrict& operator=(const UnionDistrict& otherUnionDistrict);
		virtual void toOs(ostream& os) const override;
		virtual void saveBin(ofstream& out_file) const noexcept(false);
};
