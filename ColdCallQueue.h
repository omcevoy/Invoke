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
#ifndef COLD_CALL_QUEUE_H
#define COLD_CALL_QUEUE_H

#include <deque>
#include <memory>
#include <string>
#include <vector>
#include "Student.h"


class ColdCallQueue
{
private:
    // Internal storage
    std::deque<struct Student *> student_queue; // The students in the queue
    std::string class_name; // The name of the class this queue is for
public:
    // Info methods
    std::string getClassName();
    void setClassName(std::string class_name);
    // State methods
    /**
     * Loads a ColdCallQueue with the given students
     * @param newList the new list of students
     */
    void loadQueue(std::vector<struct Student *> newList);

    /**
      *Exports the queue in its current order to persistent storage
     */
     void exportQueue();

    /**
     * Adds an individual student to the ColdCallQueue, such as when the roster changes though just an addition
     * @param student the student being added
     */
    void addStudent(struct Student * student);

    // Interface Methods
    /**
     * Gets a list of Students that are "On Deck"
     * The UI uses this to know what students to display as being "On Deck"
     * @param requested_count the number of Students to be returned as "On Deck"
     */
    std::vector<struct Student *> getOnDeck(const unsigned int requested_count);

    /**
     * Removes a Student from "On Deck", marking their participation and putting them back in the queue
     * The UI uses this to remove a Student from "On Deck", and should then update its list with getOnDeck
     * @param position the position of the Student in the "On Deck" list that should be removed
     * @param flag     whether the Student's participation should be annotated with a flag or not
     */
    void removeOnDeck(const unsigned int position, const char flag);

};


#endif
