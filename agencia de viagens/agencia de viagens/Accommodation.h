#pragma once

#include <vector>
#include "date.h"
class Accommodation
{
	//shashmaps com datas no futuro que alteram o preço (2*, 0.5*), por enquanto preço base só
	double price;
	vector < pair <Date, Date> > datesPriceChange;
	vector <double> percentageToChange;

public:
	/*Accommodation();*/
	Accommodation(double price);
	double getPrice(string dateStr) const;
	void addDates(pair<Date,Date> datesToAdd);
	void addPercentage(double perc);
};

