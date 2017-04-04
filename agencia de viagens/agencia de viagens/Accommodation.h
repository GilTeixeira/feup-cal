#pragma once

#include <vector>
#include <map>
#include "date.h"
class Accommodation
{
	//shashmaps com datas no futuro que alteram o pre�o (2*, 0.5*), por enquanto pre�o base s�
	double price;
	vector < pair <Date, Date> > datesPriceChange;
	vector <double> percentageToChange;
	static map<int, double> const Accommodation::percentageDay;

public:
	/*Accommodation();*/
	Accommodation(double price);
	double getPrice(string dateStr) const;
	void addDates(pair<Date,Date> datesToAdd);
	void addPercentage(double perc);
};

