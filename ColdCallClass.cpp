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

#include <iostream>//TESTING
#include <deque>
#include <map>
#include "ColdCallClass.h"
#include "statePersistence.h"
#include "RosterIE.h"
#include "Reporting.h"

void ColdCallClass::loadState(const std::string class_name)
{
  // Set this class's name
  this->class_name = class_name;
  // Load the saved state from the StatePersistence module
  std::vector<std::shared_ptr<struct Student>> loaded = loadClass(class_name);
  this->roster.assign(loaded.cbegin(), loaded.cend());
  // Load the queue with the data we had stored
  this->call_queue.setClassName(class_name);
  this->call_queue.loadQueue(this->getStudents());
  return;
}

// Misc info
std::string ColdCallClass::getClassName()
{
  return this->class_name;
}

ColdCallQueue * ColdCallClass::getQueue()
{
  return &(this->call_queue);
}

// Roster management
std::vector<struct Student *> ColdCallClass::getStudents()
{
  std::vector<struct Student *> class_list;
  for (std::vector<std::shared_ptr<struct Student>>::const_iterator cit = this->roster.cbegin(); cit != this->roster.cend(); cit++)
  {
    class_list.push_back(&(**cit));
  }
  return class_list;
}

void ColdCallClass::loadRoster(const std::string filename)
{
  std::vector<std::shared_ptr<struct Student>> newRoster;

  // Load the roster from the RosterIE module
  std::vector<std::shared_ptr<struct Student>> loaded = importRoster(filename);

  // Load the data in to be imported later after confirmation
  this->newRoster.assign(loaded.cbegin(), loaded.cend());

  return;
}

bool ColdCallClass::compareRoster
(
    std::vector<struct Student *> * addedStudents,
    std::vector<std::pair<struct Student *, struct Student *>> * updatedStudents,
    std::vector<struct Student *> * removedStudents
)
{
  std::vector<std::shared_ptr<struct Student>> added;
  std::vector<std::pair<std::shared_ptr<struct Student>,std::shared_ptr<struct Student>>> modified;
  std::vector<std::shared_ptr<struct Student>> removed;
  bool is_different = this->compareRosterShared(&added, &modified, &removed);

  for (std::vector<std::shared_ptr<struct Student>>::const_iterator ait = added.cbegin(); ait != added.cend(); ait++)
  {
    addedStudents->push_back(&(**ait));
  }
  for (std::vector<std::pair<std::shared_ptr<struct Student>,std::shared_ptr<struct Student>>>::const_iterator mit = modified.cbegin(); mit != modified.cend(); mit++)
  {
    updatedStudents->push_back(std::pair<struct Student *, struct Student *>(&(*((*mit).first)), &(*((*mit).first))));
  }
  for (std::vector<std::shared_ptr<struct Student>>::const_iterator rit = removed.cbegin(); rit != removed.cend(); rit++)
  {
    removedStudents->push_back(&(**rit));
  }
  return is_different;
}


bool ColdCallClass::compareRosterShared
(
    std::vector<std::shared_ptr<struct Student>> * addedStudents,
    std::vector<std::pair<std::shared_ptr<struct Student>, std::shared_ptr<struct Student>>> * updatedStudents,
    std::vector<std::shared_ptr<struct Student>> * removedStudents
)
{
  bool is_different = false;
  std::map<std::string, std::shared_ptr<struct Student>> current;
  std::map<std::string, std::shared_ptr<struct Student>> loading;

  // Create maps for easier lookups
  for (std::vector<std::shared_ptr<struct Student>>::const_iterator cit = this->roster.cbegin(); cit != this->roster.cend(); cit++)
  {
    current.insert(std::pair<std::string, std::shared_ptr<struct Student>>((**cit).student_id, *cit));
  }
  for (std::vector<std::shared_ptr<struct Student>>::const_iterator nit = this->newRoster.cbegin(); nit != this->newRoster.cend(); nit++)
  {
    loading.insert(std::pair<std::string, std::shared_ptr<struct Student>>((**nit).student_id, *nit));
  }

  // Perform the actual comparisons
  // Check for things in the current roster but not in the new roster
  for (std::vector<std::shared_ptr<struct Student>>::const_iterator cit = this->roster.cbegin(); cit != this->roster.cend(); cit++)
  {
    std::shared_ptr<struct Student> oldStudent = *cit;
    // Check if they've been removed
    if (loading.count(oldStudent->student_id) < 1)
    {
      // No student with that ID exists, add them to the list of removed students
      removedStudents->push_back(oldStudent);
    }
  }

  // Check for new or updated things from the new roster
  for (std::vector<std::shared_ptr<struct Student>>::const_iterator nit = this->newRoster.cbegin(); nit != this->newRoster.cend(); nit++)
  {
    std::shared_ptr<struct Student> newStudent = *nit;

    // Check if they've been added
    if (current.count(newStudent->student_id) < 1)
    {
      // No student with that ID exists, add them to the list of added students
      addedStudents->push_back(newStudent);
    }
    else
    {
      // A student with that ID exists, check if they are the same
      std::shared_ptr<struct Student> oldStudent = current.at(newStudent->student_id);
      if (!(newStudent->compareBasicAttributes(&(*oldStudent))))
      {
        // Basic attributes are different, store the old and new students for comparison
        updatedStudents->push_back(std::pair<std::shared_ptr<struct Student>,std::shared_ptr<struct Student>>(oldStudent, newStudent));
      }
    }
  }

  // Check if anything is different
  if (addedStudents->size() > 0 || updatedStudents->size() > 0 || removedStudents->size() > 0)
  {
    // There's at least one difference
    is_different = true;
  }

  return is_different;
}

void ColdCallClass::updateRoster(const bool should_update)
{
  if (!should_update)
  {
    // The user has decided against this import, clear the data we loaded in
    this->newRoster.clear();
    return;
  }
  // Get a list of changes that need to be made
  std::vector<std::shared_ptr<struct Student>> added;
  std::vector<std::pair<std::shared_ptr<struct Student>, std::shared_ptr<struct Student>>> modified;
  std::vector<std::shared_ptr<struct Student>> removed;
  bool is_different = this->compareRosterShared(&added, &modified, &removed);

  // Check if there are any changes to make
  if (!is_different)
  {
    // There are not
    this->newRoster.clear();
    return;
  }


  // Make the changes
  // Remove removed students
  for (std::vector<std::shared_ptr<struct Student>>::iterator cit = this->roster.begin(); cit != this->roster.end(); cit++)
  {
    for (std::vector<std::shared_ptr<struct Student>>::const_iterator rit = removed.cbegin(); rit != removed.cend(); rit++)
    {
      // Check if this is one of the ones to remove
      if ((**rit).student_id == (**cit).student_id)
      {
        // Remove it
        cit = this->roster.erase(cit);
        cit--;
      }
    } // End removed loop
  } // End current loop

  // Update existing students
  for (std::vector<std::shared_ptr<struct Student>>::iterator cit = this->roster.begin(); cit != this->roster.end(); cit++)
  {
    for (std::vector<std::pair<std::shared_ptr<struct Student>,std::shared_ptr<struct Student>>>::const_iterator mit = modified.cbegin(); mit != modified.cend(); mit++)
    {
      // Check if this is one of the ones that has been modified
      if ((*mit).second->student_id == (**cit).student_id)
      {
        // Update it
        (**cit).updateBasicAttributes(&(*((*mit).second)));
      }
    } // End modifed loop
  } // End current loop


  // Add new students
  // Actually add the shared_ptrs to students
  for (std::vector<std::shared_ptr<struct Student>>::iterator ait = added.begin(); ait != added.end(); ait++)
  {
    // Add it
    this->addStudent(*ait);
  } // End added loop

  // We're done with the new stuff
  this->newRoster.clear();


  // Regenerate the Queue, if needed
  if (removed.size() > 0)
  {
    // Just replace it with the current roster order and randomize it a bit
    std::vector<struct Student *> class_students = this->getStudents();
    this->call_queue.loadQueue(class_students);
    // TODO: randomize?
    // this->call_queue.randomize();// ?
  }

  // Export the current state
  storeClass(this->class_name, this->getStudents());



  return;
}

void ColdCallClass::exportRoster(std::string filename)
{
  // Export the roster to the RosterIE module
  ::exportRoster(this->roster, filename);
}

void ColdCallClass::addStudent(std::shared_ptr<struct Student> student)
{
  // Add them to the roster
  this->roster.push_back(student);
  // Add them to the queue
  this->call_queue.addStudent(&(*student));
  return;
}

void ColdCallClass::exportReport(std::string report_file)
{
  // Export the end of term report
  exportTermData(this->roster, report_file);
  return;
}
