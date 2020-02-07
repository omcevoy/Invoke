/*
* Description: Project 1 (cold calling system)
*
* Author: Owen, Mason, James, Zach, Sam
*
* Date of last update: 2/1/2020
*
* Notes:
*
*/
#ifndef COLD_CALL_CLASS_H
#define COLD_CALL_CLASS_H

#include <memory>
#include <string>
#include <vector>
#include "ColdCallQueue.h"
#include "Student.h"


class ColdCallClass
{
private:
    // Internal state storage
    std::string class_name; // The name of the class this represents
    std::vector<std::shared_ptr<struct Student>> roster; // The current roster of students in the class
    std::vector<std::shared_ptr<struct Student>> newRoster; // The potential new list of students being considered for import
    class ColdCallQueue call_queue; // The queue of students who will be called on

    // Internal methods
    /**
     * Computes what has changed between the current roster and the newRoster, counting only basic attributes, not participation
     * This is used internally to get the comparison list for making changes
     * @param  addedStudents   a list of students that have been added in the new roster
     * @param  updatedStudents a list of pairs of students (old and new respectively) that have been changed in some way in the new roster
     * @param  removedStudents a list of students that have been removed in the new roster
     * @return                 whether there are any changes
     */
    bool compareRosterShared
    (
        std::vector<std::shared_ptr<struct Student>> * addedStudents,
        std::vector<std::pair<std::shared_ptr<struct Student>, std::shared_ptr<struct Student>>> * updatedStudents,
        std::vector<std::shared_ptr<struct Student>> * removedStudents
    );

public:
    // State management methods
    /**
     * Loads the saved state from the backend storage
     * @param class_name the name of the class that should be loaded into this ColdCallClass
     */
    void loadState(const std::string class_name);

    // Misc info
    /**
     * Gets the name for this class
     * @return the name of this class
     */
    std::string getClassName();
    /**
     * Gets a pointer to the ColdCallQueue for this class to use
     * @return a pointer to the ColdCallQueue
     */
    ColdCallQueue * getQueue();

    // Roster management
    /**
     * Gets a list of the students in this class
     * @return the list of students, in no particular order
     */
    std::vector<struct Student *> getStudents();
    /**
     * Loads the roster in the specified file into an internal storage for later comparison
     * @param filename the filename that the roster to load is stored in
     */
    void loadRoster(const std::string filename);

    /**
     * Computes what has changed between the current roster and the newRoster, counting only basic attributes, not participation
     * The UI uses this to have the user confirm the changes before a new roster is imported and existing data is potentially lost
     * @param  addedStudents   a list of students that have been added in the new roster
     * @param  updatedStudents a list of pairs of students (old and new respectively) that have been changed in some way in the new roster
     * @param  removedStudents a list of students that have been removed in the new roster
     * @return                 whether there are any changes
     */
    bool compareRoster
    (
        std::vector<struct Student *> * addedStudents,
        std::vector<std::pair<struct Student *, struct Student *>> * updatedStudents,
        std::vector<struct Student *> * removedStudents
    );

    /**
     * Performs the update with the new roster that was loaded in previously
     * @param should_update whether the new roster data should be loaded in (true) or discarded (false)
     */
    void updateRoster(const bool should_update);

    /**
     * Exports the currently loaded roster data to a file so that changes can later be made and reimported
     * @param filename the filename that the roster should be stored in
     */
    void exportRoster(std::string filename);

    /**
     * Adds a student to the current roster
     * @param student the student in question
     */
    void addStudent(std::shared_ptr<struct Student> student);

    // Reporting
    /**
     * Exports the existing class data in a report that includes participation events
     */
    void exportReport(std::string report_file);

};

#endif
