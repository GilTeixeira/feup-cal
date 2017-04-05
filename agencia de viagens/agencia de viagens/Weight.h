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
	Weight();
	void addTripInfo(TripInfo tripInfo);
	TripInfo Weight::getEdgeWeightPrice(string & dateStr, set<string> notWantedTypes, Accommodation destination);
};

#endif