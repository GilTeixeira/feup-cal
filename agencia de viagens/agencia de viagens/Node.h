/**
* @file Node.h
* @title Node Class
* @brief Class that stores Node Information 
*/

#ifndef NODE_H_
#define NODE_H_

#include <string>
#include "Accommodation.h"

using namespace std;
class Node
{
	int nodeID;
	string cityName;
	vector <string> monuments;
	Accommodation accommodation;
	float longitude;
	float latitude;
public:
	/**
	*@brief Creates a Node
	*@param nodeID
	*@param cityName
	*@param accommodation
	*@param longitude
	*@param latitude
	*/
	Node(int nodeID, string cityName, vector <string> monuments, Accommodation accommodation, float longitude, float latitude);

	Node(int nodeID);
	/**
	*@brief Gets the Node's ID.
	*@return nodeID.
	*/
	int getNodeID() const;

	/**
	*@brief Gets the City's name.
	*@return City's name.
	*/
	string getCityName() const;

	/**
	*@brief Gets the Accommodation.
	*@return The accommodation.
	*/
	Accommodation getAccommodation() const;

	/**
	*@brief Compares two dates
	*@param date The date to be compared
	*/

	vector<string> getMonuments() const;
	bool operator==(const Node & node) const;

	/**
	*@brief Compares two dates
	*@param date The date to be compared
	*/
	bool operator!=(const Node & node) const;

	/**
	*@brief Gets the Longitude of the City.
	*@return Longitude of the City.
	*/
	float getLongitude() const;

	/**
	*@brief  Gets the Latitude of the City.
	*@return Latitude of the City.
	*/
	float getLatitude() const;
};

#endif