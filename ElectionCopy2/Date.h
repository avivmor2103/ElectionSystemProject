#pragma once
#include"FileManger.h"
using namespace std;

class Date{
private:
	int _day, _month, _year;
public:
	Date();
	Date(ifstream& file);
	Date(int day, int month, int year);
	~Date();
	Date(const Date& date);
	
	/********Getters*********/
	int getDay() { return _day; }
	int getMonth() { return _month; }
	const int getYear() { return _year; }
	
	/********Setters*********/
	bool setDay(int day);
	bool setMonth(int month);
	bool setYear(int year);

	void saveDate(ofstream& file)const;
	const Date& operator=(const Date& date);
};
