/**
* @file Date.h
* @title Class Date
* @brief Declaration of Date that handles all dates in the project.
*/

#ifndef DATE_H_
#define DATE_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include "exceptions.h"
using namespace std;


class Date {
private:
	int day;
	int month;
	int year;
public:
	/**
	*@brief Creates a Date with the current date.
	*/
	Date();

	/**
	*@brief Creates a Date with the date information in a string.
	*@param dateStr String containing a date in the format DD/MM/YYYY.
	*/
	Date(string dateStr); 

	/**
	*@brief Creates a Date with a day and month
	*/

	Date(int day, int month);

	/**
	*@brief Gets the Date's day.
	*@return Day.
	*/	

	int getDay() const;

	/**
	*@brief Gets the Date's month.
	*@return Month.
	*/
	int getMonth() const;

	/**
	*@brief Gets the Date's year.
	*@return Year.
	*/
	int getYear() const;

	/**
	*@brief Compares two dates
	*@param date The date to be compared
	*/

	bool operator==(const Date &date) const;

	/*
	*@brief Compares the day and month of two dates
	*@param date2 The date to be compared
	*/
	bool isLessDayMonth(const Date &date2)const;

	/**
	*@brief Prints the Date to a file in the format DD/MM/YYYY.
	*@param out Stream of the file to print to.
	*/
	void save(ofstream &out) const;

	/**
	*@brief Prints a Date to a file in the format DD/MM/YYYY.
	*@param out Stream of the file to print to.
	*@param date Date to print.
	*@return Stream of the file to print to.
	*/
	friend ostream& operator<<(ostream &out, const Date &date);

	/**
	*Compares Dates by their amount of days since 00/00/0000.
	*@brief Compares Dates.
	*@param date1 Date.
	*@param date2 Date.
	*@return True if date1 is older than date2, false otherwise.
	*/
	friend bool operator<(const Date &date1, const Date &date2);

	/**
	*Disparate variation of the Gauss's Algorithm that determinates the Day of the Week.
	*@brief Determination of the day of the week.
	*@return The day of the week(0 = Sunday, ..., 6 = Saturday).
	*/
	int getDayofTheWeek() const;
};

/**
*@brief Determination of the number of days of a month.
*@param month A momth.
*@return The number of day of the month.
*/

inline int maxmonthday(int month) {
	switch (month)
	{
		case 4: case 6: case 9: case 11:
			return 30;
		case 2:
			return 29;
		default:
			return 31;
	}
}

#endif