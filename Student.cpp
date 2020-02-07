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

#include "Student.h"

bool Student::compareBasicAttributes(const struct Student * b) const
{
  bool is_equal = false;
  if (this->student_id != b->student_id)
  {
    return is_equal;
  }
  if (this->first_name != b->first_name)
  {
    return is_equal;
  }
  if (this->last_name != b->last_name)
  {
    return is_equal;
  }
  if (this->email != b->email)
  {
    return is_equal;
  }
  if (this->phonetic_spelling != b->phonetic_spelling)
  {
    return is_equal;
  }
  if (this->reveal_code != b->reveal_code)
  {
    return is_equal;
  }
  is_equal = true;
  return is_equal;
}


void Student::updateBasicAttributes(const struct Student * b)
{
  if (this->first_name != b->first_name)
  {
    this->first_name = b->first_name;
  }
  if (this->last_name != b->last_name)
  {
    this->last_name = b->last_name;
  }
  if (this->email != b->email)
  {
    this->email = b->email;
  }
  if (this->phonetic_spelling != b->phonetic_spelling)
  {
    this->phonetic_spelling = b->phonetic_spelling;
  }
  if (this->reveal_code != b->reveal_code)
  {
    this->reveal_code = b->reveal_code;
  }
  return;
}

void Student::participate(time_t time, const char flag)
{
  this->participation.push_back(std::tuple<time_t, char>(time, flag));
  return;
}


// Debug TESTING
std::ostream& operator << (std::ostream &out, const struct Student &s)
{
  out << s.first_name;
  out << ' ' << s.last_name;
  out << " <" << s.email << '>';
  out << " (" << s.phonetic_spelling << ')';
  out << " reveal: " << s.reveal_code;
  return out;
}
