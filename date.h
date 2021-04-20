#pragma once
#include <iostream>
#include <fstream>
#include <map>
using namespace std;


class Date {
	private:
		int _day;
		int _month;
		int _year;

		//validate
		void validateDay(const int day, const int numOfDays) noexcept(false);
		void validateMonth(const int month) noexcept(false);
		void validateYear(const int year) noexcept(false);
	public:
		//Constructor
		Date(const int day, const int month, const int year) noexcept(false);
		Date(const Date& otherDate);
		Date(ifstream& in_Binary_file) noexcept(false);
		//Getters
		const int getDay() const { return this->_day; }
		const int getMonth() const { return this->_month; }
		const int getYear() const { return this->_year; }
		//Setters
		void setDay(const int day) noexcept(false);
		void setMonth(const int month) noexcept(false);
		void setYear(const int year) noexcept(false);
		void saveBin(ofstream& out_file) const noexcept(false);
};
