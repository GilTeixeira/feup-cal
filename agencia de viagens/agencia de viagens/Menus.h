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
#include <cstdlib>
#undef max



using namespace std;


/**
*@brief Menu to ask user to read from a text file.
*@return True to exit program, false to repeat.
*/
bool menuTextFile();

/**
*@brief Main Menu.
*@param ....
*/
void mainMenu();
