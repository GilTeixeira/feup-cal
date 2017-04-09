/**
* @file TripInfo.h
* @title Class TripInfo
* @brief  Class that stores Information about the Trip
*/


#ifndef TRIP_INFO_
#define TRIP_INFO_

#include <string>
#include <map>
#include <iomanip>

using namespace std;

class TripInfo
{
	string type;
	double price_in_euros;
	unsigned int time_in_minutes;

public:
	/**
	*@brief Creates a TripInfo object.
	*@param type Type of Transportation.
	*@param time_in_minutes Time in minutes of the Trip.
	*@param price_in_euros Price in euros of the Trip.
	*/
	TripInfo(string type, int time_in_minutes, double price_in_euros);

	/**
	*@brief Gets the Trip's type of Transportation.
	*@return type of transportation.
	*/
	string getType() const;

	/**
	*@brief Gets the Trip duration.
	*@return Time in minutes of the Trip.
	*/
	unsigned int getTime() const;

	/**
	*@brief Gets the Trip cost.
	*@return Price in euros of the Trip.
	*/
	double getPrice() const;

	/**
	*@brief Operator to print Information about the trip.
	*@param out	Where to print the Trip Information.
	*@param trip The Trip to print.
	*/
	friend ostream& operator<<(ostream &out, const TripInfo &trip);
};

#endif
