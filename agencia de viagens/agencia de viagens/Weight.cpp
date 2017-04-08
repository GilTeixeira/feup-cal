#include "Weight.h"
#include "utils.h"

Weight::Weight(){}

void Weight::addTripInfo(TripInfo tripInfo)
{
	allTrips.push_back(tripInfo);
}


TripInfo Weight::getEdgeWeightPrice(set<string> notWantedTypes)
{
	TripInfo lessExpensive = allTrips.at(0);
	for (TripInfo trip : allTrips)
	{

		set<string>::iterator it = notWantedTypes.find(trip.getType());
		if (it != notWantedTypes.end())
			continue;

		if (lessExpensive.getPrice() > trip.getPrice())
		{
			lessExpensive = trip;
		}
	}
	return lessExpensive;
}

