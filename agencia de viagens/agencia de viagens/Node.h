#pragma once

#include <string>
#include "Accommodation.h"
typedef long int BigInt;
using namespace std;
class Node
{
	BigInt nodeID;
	string cityName;
	Accommodation accommodation;
public:
	Node(BigInt nodeID, string cityName, Accommodation accommodation);
	BigInt getNodeID();
	string getCityName();
    

};

