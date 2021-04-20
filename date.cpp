#include "date.h"

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

enum Months { January = 1, February = 2, March = 3, April, May, June, July, August, September, October, November, December };
map<const int, int> DayForMonth{ {January,31} , {February,28} , {March,31}, {April,30}, {May,31}, {June,30}, {July,31}, {August,31}, {September,30}, {October,31}, {November,30}, {December,31} };


Date::Date(const int day, const int month, const int year) noexcept(false) : _day(day), _month(month), _year(year)
{
	validateMonth(month);
	validateDay(day, DayForMonth.find(month)->second);
	validateYear(year);
}

Date::Date(const Date& otherDate) : _day(otherDate._day), _month(otherDate._month), _year(otherDate._year)
{
}

Date::Date(ifstream& in_Binary_file) noexcept(false)
{
	int day, month, year;
	const int m = 5;
	in_Binary_file.read(rcastc(&day), sizeof(day));
	in_Binary_file.read(rcastc(&month), sizeof(month));
	in_Binary_file.read(rcastc(&year), sizeof(year));
	if (!in_Binary_file.good()) {
		throw ios_base::failure("error reading");
	}
	validateMonth(month);
	validateDay(day, DayForMonth.find(month)->second);
	validateYear(year);
	_day = day;
	_month = month;
	_year = year;
}

void Date::setDay(const int day) noexcept(false) {
	validateDay(day, DayForMonth.find(_month)->second);
	this->_day = day;
}

void Date::setMonth(const int month) noexcept(false) {
	validateMonth(month);
	this->_month = month;
}

void Date::setYear(const int year) noexcept(false) {
	validateYear(year);
	this->_year = year;
}

void Date::saveBin(ofstream& out_file) const noexcept(false) {
	out_file.write(rcastcc(&_day), sizeof(_day));
	out_file.write(rcastcc(&_month), sizeof(_month));
	out_file.write(rcastcc(&_year), sizeof(_year));
	if (!out_file.good()) {
		throw ios_base::failure("error writing");
	}
}

void Date::validateDay(const int day, const int numOfDays) noexcept(false) {
	if (day > numOfDays || day < 1) {
		throw invalid_argument("Invalid day");
	}
}

void Date::validateMonth(const int month) noexcept(false) {
	if (month < 1 || month > 12) {
		throw invalid_argument("Invalid month");
	}
}
void Date::validateYear(const int year) noexcept(false) {
	if (year < 0) {
		throw invalid_argument("Invalid year");
	}
}