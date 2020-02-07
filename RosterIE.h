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
#ifndef ROSTERIE_H
#define ROSTERIE_H

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <sstream>
#include "Student.h"
#include "statePersistence.h"
#include "ColdCallClass.h"
#include <sys/stat.h>

/**
 * this function reads a line and determines whether the delimiter is a comma or a tab
 *
 * @param  line a sample line of input to be examined for delimiters
 * @return      the delimiter detected in the file, values are '/t', ',', and '0'
 *              it returns '0' if there is no comma or tab in the line
 */
char getDelim(std::string line);

/**
 * Parses a roster file and creates shared_ptr's to struct Student's representing everyone in that class
 * @param file the filename of the roster file to load from
 */
std::vector<std::shared_ptr<struct Student>> importRoster(std::string file);

/**
 * Writes the data from the internal program roster to a file,
 * without the participation data, in the following format
 * <first_name> <tab> <last name> ... <phonetic spelling> <\n>
 * @param roster   the list of Students in the roster to export
 * @param filename the filename of the roster file to export to
 */
void exportRoster(std::vector<std::shared_ptr<struct Student>> roster, std::string filename);

#endif
