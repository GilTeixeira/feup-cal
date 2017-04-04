#include "Accommodation.h"

//Accommodation::Accommodation(){}

Accommodation::Accommodation(double price)
{
	this->price = price;
}

double Accommodation::getPrice(string dateStr) const
{
	Date dateToTravel = Date(dateStr);
	for (size_t i = 0; i < datesPriceChange.size(); i++) {
		if (dateToTravel.isLessDayMonth(datesPriceChange.at(i).second) && datesPriceChange.at(i).first.isLessDayMonth(dateToTravel))
			return price*percentageToChange.at(i);
	}

	return price;
}

void Accommodation::addDates(pair<Date, Date> datesToAdd)
{
	datesPriceChange.push_back(datesToAdd);
}

void Accommodation::addPercentage(double perc)
{
	percentageToChange.push_back(perc);
}
