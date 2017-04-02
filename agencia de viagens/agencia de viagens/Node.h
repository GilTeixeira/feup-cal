#pragma once

#include <string>
#include "Accommodation.h"

using namespace std;
class Node
{
	string cityName;
	Accommodation accommodation;
public:
	Node( string cityName, Accommodation accommodation);
	string getCityName() const;
	bool operator==(const Node &node) const;
};

