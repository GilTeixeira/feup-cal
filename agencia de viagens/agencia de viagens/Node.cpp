#include "Node.h"

Node::Node(int nodeID, string cityName, Accommodation accommodation, float longitude, float latitude)
	: accommodation(accommodation)
{
	this->nodeID = nodeID;
	this->cityName = cityName;
	this->longitude = longitude;
	this->latitude = latitude;
}

string Node::getCityName() const
{
	return cityName;
}

int Node::getNodeID() const {
	return nodeID;
}

bool Node::operator==(const Node & node) const
{
	return nodeID == node.getNodeID();
}

bool Node::operator!=(const Node & node) const
{
	return nodeID != node.getNodeID();
}


Accommodation const & Node::getAccommodation() const
{
	return accommodation;
}

float Node::getLatitude()
{
	return latitude;
}

float Node::getLongitude()
{
	return longitude;
}
