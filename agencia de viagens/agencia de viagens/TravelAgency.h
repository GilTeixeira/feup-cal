#ifndef TRAVEL_AGENCY_H_
#define TRAVEL_AGENCY_H_

#include "utils.h"
#include "exceptions.h"
#include "Graph.h"
#include "FichaJUNG.h"

class TravelAgency
{
private:
	Graph travelAgencyGraph;
	vector<string> transportTypes;
	set<string> load_notWantedTypes();
	void outPut_TripToOneCity(const list<Vertex> &shortestPath, uint accommodationTime,string dateStr,const set<string> &notWantedTypes);
public:
	TravelAgency();
	void TripToOneCity();
	friend void graphviewer(TravelAgency& travelAgencyGraph);
};

#endif