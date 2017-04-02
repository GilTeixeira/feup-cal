#pragma once
#pragma once

#include <string>

using namespace std;


class Weight
{
	
	string type;
	double price_in_euros;
	unsigned int time_in_minutes; 

public:
	Weight(string type, int time_in_minutes, double price_in_euros);
	string getType() const;
	unsigned int getTime() const;
	double getPrice() const;
};

