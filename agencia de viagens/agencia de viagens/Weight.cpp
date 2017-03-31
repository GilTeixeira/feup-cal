#include "Weight.h"


Weight::Weight(string type, int time_in_minutes, float price_in_euros)
{
	this->type = type;
	this->time_in_minutes = time_in_minutes;
	this->price_in_euros = price_in_euros;
}

string Weight::getType()
{
	return type;
}

unsigned int Weight::getTime()
{
	return time_in_minutes;
}

float Weight::getPrice()
{
	return price_in_euros;
}


