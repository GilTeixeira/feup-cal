#pragma once

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
