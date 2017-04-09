#ifndef NODE_H_
#define NODE_H_

#include <string>
#include "Accommodation.h"

using namespace std;
class Node
{
	int nodeID;
	string cityName;
	Accommodation accommodation;
	float longitude;
	float latitude;
public:
	Node(int nodeID, string cityName, Accommodation accommodation, float longitude, float latitude);
	int getNodeID() const;
	string getCityName() const;
	Accommodation getAccommodation() const;
	bool operator==(const Node & node) const;
	bool operator!=(const Node & node) const;
	float getLongitude() const;
	float getLatitude() const;
};

#endif