#include "Weight.h"


Weight::Weight(string type, int time_in_minutes, double price_in_euros)
{
	this->type = type;
	this->time_in_minutes = time_in_minutes;
	this->price_in_euros = price_in_euros;
}

string Weight::getType() const
{
	return type;
}

unsigned int Weight::getTime() const
{
	return time_in_minutes;
}

double Weight::getPrice() const
{
	return price_in_euros;
}


