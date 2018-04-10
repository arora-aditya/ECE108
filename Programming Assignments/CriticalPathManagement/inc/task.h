///////////////////////////////////////////////////////////////////////
//
// Class Task
//
// Provides a simple Task Class for project planning.
//
//

#ifndef TASK_H
#define TASK_H

#include <iostream>
// #include <tasks.h>

const int MAX_NUMBER_DEPENDENCIES = 10;
const int MAX_TASK_NAME_LENGTH = 255;

class Tasks;

class Task {
 public:
  bool isError() const;
  bool addDependency(const int dependency);
  void operator=(const Task& t);  // Shallow copy, but allows for invariant test

  Task() { _identifier = -1; };   // Set it to "errorTask" by default
  Task(const int id);             // Special case for creating tasks 0 and N+1
  Task(const Task& t);            // Implemented in the .cpp file
  Task(const int id, const float expected, const float best, const float worst, const char name[]);
  ~Task();


 private:
  friend std::ostream& operator<<(std::ostream& os, const Task& t);
  friend class Tasks;
  int   _identifier;
  float _expectedTime;
  float _bestCaseTime;
  float _worstCaseTime;
  int   _numberOfDependencies;
  int   _dependsOn[MAX_NUMBER_DEPENDENCIES];
  char  _name[MAX_TASK_NAME_LENGTH+1];

};

#endif
