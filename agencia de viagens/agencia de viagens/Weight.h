#pragma once

#include <vector>
#include "TripInfo.h"

using namespace std;


class Weight
{
	vector <TripInfo> allTrips;
public:
	Weight();
	void addTripInfo(TripInfo tripInfo);
};

