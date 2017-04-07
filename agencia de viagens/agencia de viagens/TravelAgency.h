#ifndef TRAVEL_AGENCY_H_
#define TRAVEL_AGENCY_H_

#include "utils.h"
#include "exceptions.h"
#include "Graph.h"
#include "FichaJUNG.h"

class TravelAgency
{
	Graph travelAgencyGraph;
	vector<string> transportTypes;
public:
	TravelAgency();
	void TripToOneCity();
	set<string> load_notWantedTypes();
	friend void graphviewer(TravelAgency& travelAgencyGraph);
};

#endif