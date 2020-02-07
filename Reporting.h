/*
* Description: Project 1 (cold calling system)
*
* Author: Owen, Mason, James, Zach, Sam
*
* Date of last update: 2/2/2020
*
* Notes:
*
*/

#ifndef REPORTING_H
#define REPORTING_H

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <sstream>
#include "Student.h"
#include "statePersistence.h"

/**
 * Function that is used to record a participation event to the class's daily log file
 * @param class_name the name of the class the participation happened in (used to determine what log file to write to)
 * @param student    the student who participated
 * @param time       the time of the participation event
 * @param flag       if the user's participation should be flagged in some way
 */
void appendDailyLog(std::string class_name, struct Student * student, time_t time, char flag);

/**
 * Writes the data from the roster to a file in the following format, with participation data
 * total times participated <tab> <first_name> <tab> <last name> ... <phonetic spelling> <\n>
 * @param roster   all the students in the class
 * @param filename the filename of where the report should be exported to
 */
void exportTermData(std::vector<std::shared_ptr<struct Student>> roster, std::string filename);

#endif
