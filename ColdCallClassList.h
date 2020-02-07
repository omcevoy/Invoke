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
#ifndef COLD_CALL_CLASS_LIST_H
#define COLD_CALL_CLASS_LIST_H

#include <memory>
#include <string>
#include <map>
#include "ColdCallClass.h"

class ColdCallClassList
{
private:
  std::map<std::string, std::shared_ptr<class ColdCallClass>> classes;

public:
  // Loading/exporting
  /**
   * Loads all the classes from the backend that have been added to the program
   */
  void loadClasses();

  /**
   * Saves the current state of all of the classes currently loaded to the backend
   */
  void saveClasses();

  // Class management
  /**
   * Adds a class to the current state and saves it to the backend
   * @param class_name the name of the new class
   */
  void addClass(std::string class_name);

  /**
   * Deletes a class and all its data
   * @param class_name the name of the class to delete
   */
  void deleteClass(std::string class_name);

  /**
   * Gets a list of the names of all the classes currently loaded
   */
  std::vector<std::string> getClassList();

  /**
   * Gets a specific class for use in UI
   * @param  class_name the name of the class to get
   * @return            a pointer to the class of that name, nullptr if it does not exist
   */
  class ColdCallClass * getClass(std::string class_name);
};


#endif
