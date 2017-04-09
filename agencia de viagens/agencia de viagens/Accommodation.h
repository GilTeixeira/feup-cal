/**
* @file Accommodation.h
* @title Class Accommodation
* @brief Class that stores information about accomodation in a city
*/

#ifndef ACCOMMODATION_H_
#define ACCOMMODATION_H_

#include <vector>
#include <map>
#include "date.h"
class Accommodation
{
	//shashmaps com datas no futuro que alteram o preço (2*, 0.5*), por enquanto preço base só
	double price;
	vector < pair <Date, Date> > datesPriceChange;
	vector <double> percentageToChange;
	static map<int, double> const Accommodation::percentageDay;

public:
	/**
	*@brief Create class Accommodation with base price.
	*@param price The base price.
	*/
	Accommodation(double price);

	/**
	*@brief Gets price.
	*@param dateStr date in which the Accomodation is used.
	*@return price of the Accommodation per day.
	*/
	double getPrice(string dateStr) const;

	/**
	*@brief Add Date in which the price is changed.
	*@param datesToAdd pair of Dates in which the price is changed.
	*/
	void addDates(pair<Date,Date> datesToAdd);

	/**
	*@brief Add percentage of the alteration of the base price.
	*@param perc percentage of change of price.
	*/
	void addPercentage(double perc);
};

#endif