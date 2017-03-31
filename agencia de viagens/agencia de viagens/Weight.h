#pragma once
#pragma once

#include <string>

using namespace std;


class Weight
{
	
	string type;
	unsigned int time_in_minutes; 
	float price_in_euros; 

public:
	Weight(string type, int time_in_minutes, float price_in_euros);
	string getType();
	unsigned int getTime();
	float getPrice();
};

