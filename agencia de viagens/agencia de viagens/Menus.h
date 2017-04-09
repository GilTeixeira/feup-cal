#ifndef MENUS_H_
#define MENUS_H_

/**
* @file Menus.h
* @title Menus
* @brief Some Menu functions.
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
*@brief Displays the Main Menu.
*@param travelAgency The Travel Agency
*/
void mainMenu(TravelAgency &travelAgency);

/**
*@brief Calculates the best Trip to a single city
*@param travelAgency The Travel Agency
*/
void callTripToOneCity(TravelAgency &travelAgency);

/**
*@brief Calculates the best Trip to multiple cities
*@param travelAgency The Travel Agency
*/
void callCustomTrip(TravelAgency &travelAgency);

#endif