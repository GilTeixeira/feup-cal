/**
* @file utils.h
* @author 
* @title Utilitie Functions
* @brief Utilitie functions and definitions to help in the development of this project
*/

#pragma once
#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Node.h"
#include "Accommodation.h"
#include "Weight.h"
#include "TravelAgency.h"

using namespace std;
typedef unsigned int uint;

#define TAB	"\t"		
#define BIG_TAB	"\t\t\t\t\t\t\t"
/**
@brief Clears console screen, for a clean look, expecially used in menus
*/
void clrscr();

//template<typename T>bool check_duplicates(const vector<T> &v,T arg);

void read_line(ifstream & f, string & line, uint &linenum);

Node read_node(ifstream &f, uint &linenum);

pair < string, Weight> read_weight(ifstream &f, uint &linenum);

double minutesToHours(const int &time_in_minutes);

double minutesToDays(const int &time_in_minutes);
