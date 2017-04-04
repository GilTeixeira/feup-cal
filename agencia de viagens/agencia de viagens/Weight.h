#pragma once

#include <vector>
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
	TripInfo getEdgeWeightPrice(set<string> notWantedTypes);

};

