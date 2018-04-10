///////////////////////////////////////////////////////////////////////
//
// Class Task:
//
// Provides a simple Task Class for project planning.
// 
// 

#include "invariant.h"
#include "task.h"
#include <iostream>

using namespace std;

#define TASK_INVARIANT(LOC)  INVARIANT_TEST(_identifier < -1, LOC)

bool Task::isError() const {
  TASK_INVARIANT("Task::isError()");
  return (_identifier == -1);
}

bool Task::addDependency(const int dependency) {
  TASK_INVARIANT("Task::addDependency()");
  if (isError())
    return false;
  if (dependency == 0)
    return true;
  if (_numberOfDependencies >= MAX_NUMBER_DEPENDENCIES)
    return false;
  _dependsOn[_numberOfDependencies] = dependency;
  ++_numberOfDependencies;
  return true;
}

void Task::operator=(const Task& t) {  // Shallow copy, but allows for invariant test
  TASK_INVARIANT("Task::opertor=()");
  if (t._identifier < -1) {
    cerr << "Task::Task(const Task& t): attempting to use destroyed Task for constructor; exiting" << endl;
    exit(-1);
  }
  _identifier    = t._identifier;
  _expectedTime  = t._expectedTime;
  _bestCaseTime  = t._bestCaseTime;
  _worstCaseTime = t._worstCaseTime;
  _numberOfDependencies = t._numberOfDependencies;
  for (int i = 0; i < MAX_NUMBER_DEPENDENCIES; ++i)
    _dependsOn[i] = t._dependsOn[i];
  for (int i = 0; i < MAX_TASK_NAME_LENGTH; ++i)
    _name[i] = t._name[i];
  _name[MAX_TASK_NAME_LENGTH] = 0;  // Just in case the name really is 255 char long  
}

  
Task::Task(const int id) {          // This is a special constructor for creating task 0 and task N+1
  if (id == 0) {                    // Task 0 can be created at any time
    _identifier = 0;                
    _expectedTime = 0;
    _bestCaseTime  = 0;
    _worstCaseTime = 0;
    _numberOfDependencies = 0;
    int i = 0;
    const char task0Name[] = "Project Initiation";
    while (task0Name[i] != 0) {
      _name[i] = task0Name[i];
      ++i;
    }
    _name[i] = 0;
  }
  else {
    _identifier = id;               // Task N+1 will be created if the id is not equal to 0; it is assumed to be correct
    _expectedTime = 0;
    _bestCaseTime  = 0;
    _worstCaseTime = 0;
    _numberOfDependencies = 0;
    int i = 0;
    const char taskNPOName[] = "Project Completion";
    while (taskNPOName[i] != 0) {
      _name[i] = taskNPOName[i];
      ++i;
    }
    _name[i] = 0;

  }
  return;
}

Task::Task(const Task& t) {
  if (t._identifier < -1) {
    cerr << "Task::Task(const Task& t): attempting to use destroyed Task for constructor; exiting" << endl;
    exit(-1);
  }
  _identifier    = t._identifier;
  _expectedTime  = t._expectedTime;
  _bestCaseTime  = t._bestCaseTime;
  _worstCaseTime = t._worstCaseTime;
  _numberOfDependencies = t._numberOfDependencies;
  for (int i = 0; i < MAX_NUMBER_DEPENDENCIES; ++i)
    _dependsOn[i] = t._dependsOn[i];
  for (int i = 0; i < MAX_TASK_NAME_LENGTH; ++i)
    _name[i] = t._name[i];
  _name[MAX_TASK_NAME_LENGTH] = 0;  // Just in case the name really is 255 char long  
}

Task::Task(const int id, const float expected, const float best, const float worst, const char name[]) {
  if (id < 0) {
    cerr << "Task::Task(const int id, const float expected, const float best, const float worst, const char name[]): attempting to assign negative taskID in constructor; exiting" << endl;
    exit(-1);
  }
  _identifier    = id;
  _expectedTime  = expected;
  _bestCaseTime  = best;
  _worstCaseTime = worst;
  _numberOfDependencies = 0;
  for (int i = 0; i < MAX_TASK_NAME_LENGTH+1; ++i)
    _name[i] = name[i];
}

Task::~Task() {
  TASK_INVARIANT("Task::~Task()");
  _identifier = -2;
}

// Abbreviated task printout (omits best and worst case time)
std::ostream& operator<<(std::ostream& os, const Task& t) {
  if (t._identifier < -1) {
    cerr << "ostream& operator<<(): attempting to print deleted Task; exiting" << endl;
    exit(-1);
  }
  if (t._identifier == -1) {
    os << "ERROR-TASK";
    return os;
  }
  if (t._numberOfDependencies == 0)
    os << "[" << t._identifier << ", " << t._expectedTime << ", " << t._name << " (Depends On {})]";
  else if (t._numberOfDependencies == 1)
    os << "[" << t._identifier << ", " << t._expectedTime << ", " << t._name << " (Depends On {" << t._dependsOn[0] << "})]";
  else {
    os << "[" << t._identifier << ", " << t._expectedTime << ", " << t._name << " (Depends On {" << t._dependsOn[0];
    for (int i = 1; i < t._numberOfDependencies; ++i)
      os << ", " << t._dependsOn[i];
    os << "})]";
  }
  return os;
}
