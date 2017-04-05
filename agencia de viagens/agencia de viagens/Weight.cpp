#include "Weight.h"
#include "utils.h"

Weight::Weight(){}

void Weight::addTripInfo(TripInfo tripInfo)
{
	allTrips.push_back(tripInfo);
}

TripInfo Weight::getEdgeWeightPrice(string & dateStr, set<string> notWantedTypes, Accommodation destination)
{
	TripInfo lessExpensive("", numeric_limits<int>::max(), numeric_limits<double>::max());
	string nextDateStr = dateStr;
	for (TripInfo trip : allTrips)
	{
		nextDateStr = dateStr;
		set<string>::iterator it = notWantedTypes.find(trip.getType());
		if (it != notWantedTypes.end() && lessExpensive.getPrice() > trip.getPrice() + destination.getPrice(addDaysToDate(nextDateStr, minutesToDays(trip.getTime()))))
		{
			lessExpensive = trip;
		}		
	}
	dateStr = nextDateStr;
	return lessExpensive;
}
