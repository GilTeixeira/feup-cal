#ifndef TRAVEL_AGENCY_H_
#define TRAVEL_AGENCY_H_

#include "utils.h"
#include "exceptions.h"
#include "Graph.h"
#include "FichaJUNG.h"
#include <iomanip>  

class TravelAgency
{
private:
	Graph travelAgencyGraph;
	vector<string> transportTypes;
	set<string> load_notWantedTypes();
	void outPut_TripToOneCity(const list<Vertex> &shortestPath, uint accommodationTime,string dateStr,const set<string> &notWantedTypes);
	void outPut_CustomTrip(const vector < list<Vertex>> &shortestPath, const map<string, uint> &accomTime, string &dateStr, const set <string> &notWantedTypes);
public:
	TravelAgency();
	void TripToOneCity();
	void CustomTrip();
	friend void graphviewer(TravelAgency& travelAgencyGraph);
};

#endif