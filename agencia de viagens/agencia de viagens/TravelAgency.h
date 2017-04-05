#ifndef TRAVEL_AGENCY_H_
#define TRAVEL_AGENCY_H_

#include "utils.h"
#include "exceptions.h"
#include "Graph.h"
//#include "graphviewer.h"
class TravelAgency
{
	Graph travelAgencyGraph;
	vector<string> transportTypes;
public:
	TravelAgency();
};

#endif