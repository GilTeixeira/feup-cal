/**
* @file utils.h
* @author 
* @title Utilitie Functions
* @brief Utilitie functions and definitions to help in the development of this project
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
@brief Clears console screen, for a clean look, expecially used in menus
*/
void clrscr();



void read_line(ifstream & f, string & line, uint &linenum);

Node read_node(ifstream &f, uint &linenum);

Weight read_edge(ifstream &f, uint &linenum, int& source, int &dest, int &edgeID, vector<string> &transportTypes);

double minutesToHours(const int &time_in_minutes);

double minutesToDays(const int &time_in_minutes);

void addDaysToDate(string & dateStr, unsigned int days);

pair<int, int> CoodinatesToMap(const float longitude, const float latitude);

#endif