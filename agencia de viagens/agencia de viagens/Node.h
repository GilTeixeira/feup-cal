#pragma once

#include <string>
#include "Accommodation.h"

using namespace std;
class Node
{
	int nodeID;
	string cityName;
	Accommodation accommodation;
public:
	Node(int nodeID, string cityName, Accommodation accommodation);
	int getNodeID() const;
	string getCityName() const;
	bool operator==(const Node &node) const;
};

