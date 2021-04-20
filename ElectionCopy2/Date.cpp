#include "Date.h"

Date::Date()
{
	_day = 0;
	_month = 0;
	_year = 0;
}

Date::Date(ifstream& file)
{
	int day, month, year;
	file.read(rcastc(&day), sizeof(int));
	file.read(rcastc(&month), sizeof(int));
	file.read(rcastc(&year), sizeof(int));
	if (!file.good()){
		throw "problem occurred while loading data from the file";
	}
	setDay(day);
	setMonth(month);
	setYear(year);
}

Date::Date(int day, int month, int year) : _day(day), _month(month), _year(year){}

Date ::~Date(){}

Date::Date(const Date& date) {
	setDay(date._day);
	setMonth(date._month);
	setYear(date._year);
}

void Date::saveDate(ofstream& file)const
{
	file.write(rcastcc(&_day), sizeof(int));
	if (!file.good())
		throw "Error in day.";
	file.write(rcastcc(&_month), sizeof(int));
	if (!file.good())
		throw "Error in month.";
	file.write(rcastcc(&_year), sizeof(int));
	if (!file.good())
		throw "Error in year.";
}

bool Date::setDay(int day)
{
	this->_day = day;
	return true;
}

bool Date::setMonth(int month)
{
	this->_month = month;
	return true;
}

bool Date::setYear(int year)
{
	this->_year = year;
	return true;
}

const Date& Date:: operator=(const Date& date) {
	setDay(date._day);
	setMonth(date._month);
	setYear(date._year);
	return *this;
}