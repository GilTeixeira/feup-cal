#include "Node.h"

Node::Node(int nodeID, string cityName, vector <string> monuments, Accommodation accommodation, float longitude, float latitude)
	: accommodation(accommodation)
{
	this->nodeID = nodeID;
	this->cityName = cityName;
	this->monuments = monuments;
	this->longitude = longitude;
	this->latitude = latitude;
}

Node::Node(int nodeID)
{
	this->nodeID = nodeID;
	this->longitude = 0.0;
	this->latitude = 0.0;
}

string Node::getCityName() const
{
	return cityName;
}

int Node::getNodeID() const {
	return nodeID;
}

vector<string> Node::getMonuments() const
{
	return monuments;
}

bool Node::operator==(const Node & node) const
{
	return nodeID == node.getNodeID();
}

bool Node::operator!=(const Node & node) const
{
	return nodeID != node.getNodeID();
}


Accommodation Node::getAccommodation() const
{
	return accommodation;
}

float Node::getLatitude() const 
{
	return latitude;
}

float Node::getLongitude() const
{
	return longitude;
}
