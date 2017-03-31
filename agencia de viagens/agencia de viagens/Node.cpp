#include "Node.h"

Node::Node(BigInt nodeID, string cityName, Accommodation accommodation)
{
	this->nodeID = nodeID;
	this->cityName = cityName;
	this->accommodation = accommodation;
}

BigInt Node::getNodeID()
{
	return nodeID;
}

string Node::getCityName()
{
	return cityName;
}
