#include "Accommodation.h"

//Accommodation::Accommodation(){}

map<int, double> const Accommodation::percentageDay = []() {
	map<int, double> tmp;
	tmp[0] = 1.2;
	tmp[1] = 0.9;
	tmp[2] = 0.8;
	tmp[3] = 0.8;
	tmp[4] = 0.9;
	tmp[5] = 1.0;
	tmp[6] = 1.3;
	return tmp;
}();

Accommodation::Accommodation(double price)
{
	this->price = price;
}

Accommodation::Accommodation()
{
	price = 0.0;
}

double Accommodation::getPrice(string dateStr) const
{
	Date dateToTravel = Date(dateStr);
	for (size_t i = 0; i < datesPriceChange.size(); i++) {
		if (dateToTravel.isLessDayMonth(datesPriceChange.at(i).second) && datesPriceChange.at(i).first.isLessDayMonth(dateToTravel))
			return price*percentageToChange.at(i)*percentageDay.find(dateToTravel.getDayofTheWeek())->second;
	}

	return price*percentageDay.find(dateToTravel.getDayofTheWeek())->second;
}

void Accommodation::addDates(pair<Date, Date> datesToAdd)
{
	datesPriceChange.push_back(datesToAdd);
}

void Accommodation::addPercentage(double perc)
{
	percentageToChange.push_back(perc);
}
