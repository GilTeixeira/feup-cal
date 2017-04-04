#pragma once
#include "utils.h"
#include "exceptions.h"
#include "Graph.h"
//#include "graphviewer.h"
class TravelAgency
{
	Graph<Node> travelAgencyGraph;
	vector<string> transportTypes;
public:
	TravelAgency();
};

