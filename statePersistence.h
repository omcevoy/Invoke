/*
* Description: Project 1 (cold calling system)
*
* Author: Owen, Mason, James, Zach, Sam
*
* Date of last update: 2/02/2020
*
* Notes:
*
*/
#ifndef STATEPERSISTENCE_H
#define STATEPERSISTENCE_H

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <sstream>
#include <ctime>
#include <cstdio>
#include "ColdCallClass.h"

/**
 * This function takes a list of struct Student *'s and
 * writes all the data from the list to a file so that the
 * information may be stored between program executions.
 * @param class_name the name of the class being stored
 * @param roster     the list of struct Student *'s whose data will be stored
 */
void storeClass(std::string class_name, std::vector<struct Student *> roster);



/**
 * This function takes the name of a class that was previously stored by StoreClass.
 * It parses through the file and loads the data back into list of struct Student *'s
 * to be used again by the program.
 * @param cName the name of the class being loaded
 */
std::vector<std::shared_ptr<struct Student>> loadClass(std::string cName);

/**
 * This function is used for deleting a class's state file(s) once it's data is no longer needed
 * @param class_name the name of the class whose data will be deleted
 */
void deleteClass(std::string class_name);

/**
 * This function writes the list of classes provided to a file
 * so that the classes can be automatically loaded back in upon restart of the program.
 * @param class_names a list of the names of the classes to be stored
 */
void saveClassList(std::vector<std::string> class_names);

/**
 * This function is used to load in the list of classes from the file
 * previously saved by saveClassList so that we know what to load back in again.
 */
std::vector<std::string> loadClassList();

/**
 * This function creates the necesarry directories in the User's Documents directory
 * These directories are used for storing essential data and are where the reports can
 * be fund
 */

void createDir();

/**
 * This function gets the path to the specified directory
 * @param hidden an integer which determines if the path should be to the hidden one or not
 */

std::string getPath(int hidden);

#endif
