/*
* Description: Project 1 (cold calling system)
*
* Author: Owen, Mason, James, Zach, Sam
*
* Date of last update: 1/30/2020
*
* Notes:
*
*/

#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <tuple>
#include <ctime>
#include <ostream>


struct Student
{
    // Data
    std::string student_id;
  	std::string first_name;
  	std::string last_name;
  	std::string email;
  	std::string phonetic_spelling;
    char reveal_code;
    std::vector<std::tuple<time_t,char>> participation;

    // Modification
    /**
     * determines whether the Student's basic attributes are the same
     * @param  b the Student it is being compared to
     * @return   true for the same, false for not
     */
    bool compareBasicAttributes(const struct Student * b) const;
    /**
     * Updates basic attributes based on the values provided
     * @param b the Student with the updated values to load in
     */
    void updateBasicAttributes(const struct Student * b);
    /**
     * Stores a participation event in the student using the current date/time and a given flag
     * @param time the time of the participation event to be added
     * @param flag whether the Student's participation should be annotated with a flag
     */
    void participate(time_t time, const char flag);

    // Debug TESTING
    friend std::ostream& operator << (std::ostream &out, const struct Student &c);
};

#endif
