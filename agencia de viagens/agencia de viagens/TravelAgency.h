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
	Vertex * read_current_city(unsigned int &idSource)  ;
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
	/**
	*@brief Makes a trip to one of the monuments found
	*@param source vertex* with the source of the trip;
	*@param found monuments found
	*@param cities cities of the monuments found
	*/
	void tripToMonuments(Vertex* source, const vector<pair<string, int>> &found, const vector <string> cities);

	
public:
	/**
	*@brief Constructor of the class TravelAgency
	Gets from the files nodes.txt and edges.txt all the information to load the graph and transport types
	*/
	TravelAgency();
	/**
	*@brief User inputs necessary to call the shortest path beetween 2 citys
	*/
	void TripToOneCity();
	/**
	*@brief User inputs necessary to create a custom trip using the custom algorithm
	*/
	void CustomTrip();
	/**
	*@brief User inputs necessary to search for a monuments and it's output
	*/
	void searchMonumentsCities();

	friend void graphviewer(TravelAgency& travelAgencyGraph);
};

#endif