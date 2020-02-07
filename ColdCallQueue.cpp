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

#include "ColdCallQueue.h"
#include "Reporting.h"
#include "statePersistence.h"

// Info Methods
std::string ColdCallQueue::getClassName()
{
  return this->class_name;
}

void ColdCallQueue::setClassName(std::string class_name)
{
  this->class_name = class_name;
}

// State methods

void ColdCallQueue::loadQueue(std::vector<struct Student *> newList)
{
  this->student_queue.assign(newList.cbegin(), newList.cend());
  return;
}

void ColdCallQueue::exportQueue()
{
  // Get the data to be exported
  std::vector<struct Student *> exported;
  exported.assign(this->student_queue.cbegin(), this->student_queue.cend());

  // Actually store it
  storeClass(this->class_name, exported);

  return;
}

void ColdCallQueue::addStudent(struct Student * student)
{
  this->student_queue.push_back(student);
  return;
}

std::vector<struct Student *> ColdCallQueue::getOnDeck(const unsigned int requested_count)
{
  std::vector<struct Student *> on_deck;

  for (size_t i = 0; i < requested_count && i < this->student_queue.size(); i++)
  {
    on_deck.push_back( &(*(this->student_queue[i])) );
  }

  return on_deck;
}

void ColdCallQueue::removeOnDeck(const unsigned int position, const char flag)
{
  if (position < this->student_queue.size())
  {
    // Get it
    struct Student * participated = this->student_queue[position];
    // Record the participation
    time_t current_time = time(nullptr);
    participated->participate(current_time,flag);
    // Write the event to the daily log
    appendDailyLog(this->class_name, participated, current_time, flag);
    // Remove it from its current position
    this->student_queue.erase(this->student_queue.begin() + position);
    // Re-add it somewhere
    // Randomized adding of students to end of queue (last 50% of the queue)
    int queue_size = this->student_queue.size();

    int rand_pos = rand() % (queue_size / 2);
    rand_pos = queue_size - rand_pos;
    std::deque<struct Student *>::const_iterator pos = this->student_queue.cbegin();
    std::advance(pos, rand_pos);
    this->student_queue.insert(pos, participated); // inserting to the random number of the queue

    // Update the persistent state data
    this->exportQueue();
  }
  return;
}
