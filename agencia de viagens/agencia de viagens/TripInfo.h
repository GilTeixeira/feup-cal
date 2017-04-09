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
	TripInfo(string type, int time_in_minutes, double price_in_euros);
	string getType() const;
	unsigned int getTime() const;
	double getPrice() const;
	friend ostream& operator<<(ostream &out, const TripInfo &trip);
};

#endif
