#pragma once

#include <string>
#include <map>

using namespace std;


class TripInfo
{
	string type;
	double price_in_euros;
	unsigned int time_in_minutes;

public:
	TripInfo(string type, int time_in_minutes, double price_in_euros);
	string getType() const;
	unsigned int getTime() const;
	double getPrice() const;
};


