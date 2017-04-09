/**
* @file TravelAgency.h
* @title Class TravelAgency
* @brief Class that contains the graph and everything related to it, also used to communicate with graph.h fucntions (input/output)
*/

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
	/**
	*@brief Asks the user what tranportation types he doens't want to use
	*@return set<string> with the transportation types
	*/
	set<string> load_notWantedTypes();
	/**
	*@brief Outputs to the console the information of the shortest path beetween two citys;
	*@param shortestPath list with all the vertexes who make the shortest path
	*@param accommodationTime time of accomodation
	*@param dateStr string containing the date of the trip
	*@param notWantedTypes tranportation types that the user doens't want to use
	*/
	void outPut_TripToOneCity(const list<Vertex> &shortestPath, uint accommodationTime,string dateStr,const set<string> &notWantedTypes);
	/**
	*@brief Outputs to the console the information of the shortest path beetween all the user input;
	*@param shortestPath vector containing lists with all the vertexes who make the shortest path beetween two citys
	*@param accomTime map containg the accommodation time for a specified city 
	*@param dateStr string containing the date of the trip
	*@param notWantedTypes tranportation types that the user doens't want to use
	*/
	void outPut_CustomTrip(const vector < list<Vertex>> &shortestPath, const map<string, uint> &accomTime, string &dateStr, const set <string> &notWantedTypes);
public:
	/**
	*@brief Constructor of the class TravelAgency
	Gets from the files nodes.txt and edges.txt all the information to load the graph and transport types
	*/
	TravelAgency();
	/**
	*@brief User inputs necessary to call the shortes path beetween 2 citys
	*/
	void TripToOneCity();
	/**
	*@brief User inputs necessary to create a custom trip using the custom algorithm
	*/
	void CustomTrip();
	friend void graphviewer(TravelAgency& travelAgencyGraph);
};

#endif