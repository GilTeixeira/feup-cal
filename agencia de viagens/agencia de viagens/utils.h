/**
* @file utils.h
* @title Utilitie Functions
* @brief Utilitie functions and definitions to help in the development of this project.
*/

#ifndef UTILS_H_
#define UTILS_H_

#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Node.h"
#include "Accommodation.h"
#include "Weight.h"
#include "TravelAgency.h"

#undef max

using namespace std;
typedef unsigned int uint;

#define TAB	"\t"		
#define BIG_TAB	"\t\t\t\t\t\t\t"
#define MAP_WIDTH  1135
#define MAP_HEIGHT  605
/**
*@brief Clears console screen, for a clean look, expecially used in menus.
*/
void clrscr();

/**
*@brief Reads line of File.
*@param f The fileto be read.
*@param line The line read.
*@param linenum The line's number.
*/
void read_line(ifstream & f, string & line, uint &linenum);

/**
*@brief Read Node from file.
*@param f The file to be read.
*@param linenum The line's number.
*@return The Node read.
*/
Node read_node(ifstream &f, uint &linenum);

/**
*@brief Read Weight from file.
*@param f The file to be read.
*@param linenum The line's number.
*@param source The Source's node ID.
*@param dest The Destiny's node ID.
*@param edgeID The Edge's ID.
*@param transportTypes vector of Transportation types.
*@return The Weight read.
*/
Weight read_edge(ifstream &f, uint &linenum, int& source, int &dest, int &edgeID, vector<string> &transportTypes);

/**
*@brief Converts time in minutes to hours.
*@param time_in_minutes Time in Minutes.
*@return Time in hours.
*/
double minutesToHours(const int &time_in_minutes);

/**
*@brief Converts time in minutes to days.
*@param time_in_minutes Time in Minutes.
*@return Time in Days.
*/
double minutesToDays(const int &time_in_minutes);

/**
*@brief Adds days to Date.
*@param dateStr Date.
*@param days Days to be added.
*/
void addDaysToDate(string & dateStr, unsigned int days);

/**
*@brief Converts Real Coordinates to 2d Coordinates.
*@param longitude City's longitude.
*@param latitude City's latitude.
*@return 2d Coordinates.
*/
pair<int, int> CoodinatesToMap(const float longitude, const float latitude);

int editDistance(string pattern, string text);
int kmp(string text, string pattern);

#endif