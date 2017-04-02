#include "Node.h"

Node::Node(string cityName, Accommodation accommodation)
{

	this->cityName = cityName;
	this->accommodation = accommodation;
}



string Node::getCityName()
{
	return cityName;
}
