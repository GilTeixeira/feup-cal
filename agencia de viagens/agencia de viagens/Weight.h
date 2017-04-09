/**
* @file Weight.h
* @title Class Weight
* @brief Declaration of Class Weight of the Edges of the Graph
*/

#ifndef WEIGHT_H_
#define WEIGHT_H_

#include <vector>
#include "Accommodation.h"
#include "TripInfo.h"
#include <set>
#include <string>

using namespace std;

class Weight
{
	vector <TripInfo> allTrips;
public:
	/**
	*@brief Creates a Weight object
	*/
	Weight();

	/**
	*@brief Adds a new way of transport between two Cities
	*@param tripInfo The new way of transport
	*/
	void addTripInfo(TripInfo tripInfo);

	/**
	*@brief Gets the lowest priced way of transportation
	*@param notWantedTypes The ways of transportation undesired by the costumer
	*@return TripInfo The cheaper way of transport
	*/
	TripInfo getEdgeWeightPrice(set<string> notWantedTypes);
};

#endif