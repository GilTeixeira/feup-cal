#ifndef MENUS_H_
#define MENUS_H_

/**
* @file Menus.h
* @author AEDA T4GE
* @title Menus
* @brief Menu functions.
*/
#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>

#include "utils.h"
#include "exceptions.h"
#include "TravelAgency.h"
#include <cstdlib>
#undef max



using namespace std;

/**
*@brief Main Menu.
*@param ....
*/
void mainMenu(TravelAgency &travelAgency);
void callTripToOneCity(TravelAgency &travelAgency);
void callCustomTrip(TravelAgency &travelAgency);

#endif