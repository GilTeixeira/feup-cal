#include "Node.h"

Node::Node(string cityName, Accommodation accommodation)
	: accommodation(accommodation)
{
	this->cityName = cityName;
}

string Node::getCityName() const
{
	return cityName;
}

bool Node::operator==(const Node & node) const
{
	return cityName == node.getCityName();
}
