/*
* Description: Project 1 (cold calling system)
*
* Author: Owen, Mason, James, Zach, Sam
*
* Date of last update: 2/3/2020
*
* Notes:
*
*/

#include "ColdCallClassList.h"
#include "statePersistence.h"

void ColdCallClassList::loadClasses()
{
  // Import class list from the saved state
  std::vector<std::string> class_names = loadClassList();
  // Create class objects for each
  for (std::vector<std::string>::iterator it = class_names.begin(); it != class_names.end(); it++)
  {
    // Add and load in any existing data
    this->addClass(*it);
  }
}

void ColdCallClassList::saveClasses()
{
  // Save a list of all current classes
  // Generate list of current class names
  std::vector<std::string> class_names;
  for (std::map<std::string, std::shared_ptr<class ColdCallClass>>::const_iterator it = this->classes.cbegin(); it != this->classes.cend(); it++)
  {
    // Save the name of the class to a separate list
    class_names.push_back((*it).first);
  }
  // Save the list of class names to the saved state information
  saveClassList(class_names);
}

// Adds a class with the given name to the list of classes
void ColdCallClassList::addClass(std::string class_name)
{
  // Check if that class is already loaded
  if (this->classes.count(class_name) > 0)
  {
    // It's already loaded, nothing to do
    return;
  }
  // Try to load class in from file if it exists
  std::shared_ptr<class ColdCallClass> addedClass (new class ColdCallClass());
  addedClass->loadState(class_name);
  this->classes.insert(std::pair<std::string, std::shared_ptr<class ColdCallClass>>(class_name, addedClass));
  // Update the list of classes
  this->saveClasses();
  return;
}

void ColdCallClassList::deleteClass(std::string class_name)
{
  // Delete its associated files
  ::deleteClass(class_name);
  // Remove the class from the classes list
  this->classes.erase(class_name);
  // Update the state information
  this->saveClasses();
  return;
}


std::vector<std::string> ColdCallClassList::getClassList()
{
  std::vector<std::string> class_name_list;
  // Add all the currently loaded class names to a list
  for (std::map<std::string, std::shared_ptr<class ColdCallClass>>::const_iterator it = this->classes.cbegin(); it != this->classes.cend(); it++)
  {
    std::shared_ptr<class ColdCallClass> currentClass = (*it).second;
    class_name_list.push_back(currentClass->getClassName());
  }
  return class_name_list;
}

class ColdCallClass * ColdCallClassList::getClass(std::string class_name)
{
  class ColdCallClass * gotten = nullptr;
  if (this->classes.count(class_name) > 0)
  {
    std::shared_ptr<class ColdCallClass> gotten_sptr = this->classes.at(class_name);
    gotten = &(*gotten_sptr);
  }
  return gotten;
}
