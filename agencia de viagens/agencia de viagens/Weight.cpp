#include "Weight.h"


Weight::Weight(){}

 void Weight::addTripInfo(TripInfo tripInfo)
{
	allTrips.push_back(tripInfo);
}

 TripInfo Weight::getEdgeWeightPrice(set<string> notWantedTypes)
 {
	 TripInfo lessExpensive("", numeric_limits<int>::max(), numeric_limits<double>::max());
	 for (TripInfo trip: allTrips){
		 set<string>::iterator it = notWantedTypes.find(trip.getType());
		 if (it != notWantedTypes.end() && lessExpensive.getPrice() > trip.getPrice()) {
			 lessExpensive = trip;
		 }
	 }
	 return lessExpensive;
 }


