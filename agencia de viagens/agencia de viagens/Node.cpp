#include "Node.h"

Node::Node(int nodeID, string cityName, Accommodation accommodation)
	: accommodation(accommodation)
{
	this->nodeID = nodeID;
	this->cityName = cityName;
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
