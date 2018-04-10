///////////////////////////////////////////////////////////////////////
//
// Class Tasks:
//
// Provides a simple Tasks Class for project planning.
//
//

#include "invariant.h"
#include "tasks.h"
#include "matrix.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>

using namespace std;

#define TASKS_INVARIANT(LOC) INVARIANT_TEST(_numberOfTasks < 0, LOC)

float min(float a,float b){
  return a>b?b:a;
}

int Tasks::numberOfTasks() const {
  TASKS_INVARIANT("Tasks::numberOfTasks");
  return _numberOfTasks;
}

int Tasks::largestTaskNumber() const {
  TASKS_INVARIANT("Tasks::largestTaskNumber");
  return _largestTaskNumber;
}

Task Tasks::operator()(const int id) const {      // This returns info about a task; it does not allow change of a task
  TASKS_INVARIANT("Tasks::largestTaskNumber");
  if (id < 0 || id > _largestTaskNumber)
    return Task();
  else
    return _tasks[id];
}

// Needed for readFile
#define SKIP_WHITESPACE do {                                                                                                                 \
	  int i = 0;                                                                                                                         \
	  while ((line[i] == ' ') || (line[i] == '\t') || (line[i] == '\n') || (line[i] == '\r'))                                            \
	    ++i;                                                                                                                             \
	  if (line[i] != 0) {                                                                                                                \
	    cerr << "Tasks::readFile(): Unexpected character while reading file " << psfFile << ":" << psfLineNumber << "; exiting" << endl; \
	    exit(-1);                                                                                                                        \
	  }                                                                                                                                  \
        } while(0)


int Tasks::readFile(const char psfFile[]) {       // This is the only method for placing tasks into the task array
  TASKS_INVARIANT("Tasks::readFile()");

  ifstream infile;
  infile.open(psfFile);
  if (!infile.is_open()) {
    cerr << "Tasks::readFile(): unable to open file: " << psfFile << "; exiting" << endl;
    exit(-1);
  }

  enum PSF_STATE { START, TASKS, DEPENDENCIES };
  PSF_STATE state = START;
  bool done = false;
  int psfLineNumber = 0;
  while (!done) {
    ++psfLineNumber;
    char line[MAX_PSF_LINE_LENGTH];
    if (!infile.getline(line, MAX_PSF_LINE_LENGTH)) {       // Get next line
      if (strlen(line) == MAX_PSF_LINE_LENGTH - 1) {        // If line is max length, this is why we had a problem
	cerr << "Tasks::readFile(): Maximum line length (" << MAX_PSF_LINE_LENGTH << ") exceeded at line " << psfLineNumber << "; exiting" << endl;
	exit(-1);
      }
      else if (infile.eof()) {                     // If not, probably at end of file
	done = true;
      }
      else {                                       // Weird; no idea what happened
	cerr << "Tasks::readFile(): Unexpected file read error occurred at line " << psfLineNumber << "; exiting" << endl;
	exit(-1);
      }
    }
    switch (state) {
    case START:
      switch (line[0]) {
      case '%':                  // Comment; ignore rest of line
	break;

      case 't':                  // Start of "Tasks"
      case 'T':
	// Verify, then switch to TASKS state (will accept text after "Tasks" provided it is seprated by whitespace)
	if ((strncasecmp(line, "Tasks", 5) == 0) && (line[5] == 0 || line[5] == ' ' || line[5] == '\t'))
	  state = TASKS;
	else {
	  cerr << "Tasks::readFile(): Unexpected character while reading file " << psfFile << ":" << psfLineNumber << "; exiting" << endl;
	  exit(-1);
	}
	break;

      case ' ':                  // Gonna be nice and skip the line if it is all whitespace
      case '\t':
      case '\n':
      case '\r':
	SKIP_WHITESPACE;
	break;

      case 0:                    // Empty line; skip it
	break;

      default:
	cerr << "Tasks::readFile(): Unexpected character while reading file " << psfFile << ":" << psfLineNumber << "; exiting" << endl;
	exit(-1);
      }
      break;

    case TASKS:
      switch (line[0]) {
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':                  // Some task description
	if (!readTask(line, psfFile, psfLineNumber)) {
	  cerr << "Tasks::readFile(): Unexpected character while reading file " << psfFile << ":" << psfLineNumber << "; exiting" << endl;
	  exit(-1);
	}
	break;

      case 'd':                  // Start of "Dependencies"
      case 'D':
	// Verify, then switch to DEPENDENCIES state (will accept text after "Dependencies" provided it is seprated by whitespace)
	if ((strncasecmp(line, "Dependencies", 12) == 0) && (line[12] == 0 || line[12] == ' ' || line[12] == '\t'))
	  state = DEPENDENCIES;
	else {
	  cerr << "Tasks::readFile(): Unexpected character while reading file " << psfFile << ":" << psfLineNumber << "; exiting" << endl;
	  exit(-1);
	}
	break;

      case '%':                  // Comment; ignore rest of line
	break;

      case ' ':                  // Gonna be nice and skip the line if it is all whitespace
      case '\t':
      case '\n':
      case '\r':
	SKIP_WHITESPACE;
	break;

      case 0:                    // Empty line; skip it
	break;

      default:
	cerr << "Tasks::readFile(): Unexpected character while reading file " << psfFile << ":" << psfLineNumber << "; exiting" << endl;
	exit(-1);
      }
      break;

    case DEPENDENCIES:
      switch (line[0]) {
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':                  // Some task description
	if (!readDependencies(line, psfFile, psfLineNumber)) {
	  cerr << "Tasks::readFile(): Unexpected character while reading file " << psfFile << ":" << psfLineNumber << "; exiting" << endl;
	  exit(-1);
	}
	break;

      case '%':                  // Comment; ignore rest of line
	break;

      case ' ':                  // Gonna be nice and skip the line if it is all whitespace
      case '\t':
      case '\n':
      case '\r':
	SKIP_WHITESPACE;
	break;

      case 0:                    // Empty line; skip it
	break;

      default:
	cerr << "Tasks::readFile(): Unexpected character while reading file " << psfFile << ":" << psfLineNumber << "; exiting" << endl;
	exit(-1);
      }
      break;

    default:
      cerr << "Tasks::readFile(): Unknown state while reading file " << psfFile << ":" << psfLineNumber << "; exiting" << endl;
      exit(-1);
    }
  }
  // Now add Project Initiation and Project Completion
  _tasks[0] = Task(0);
  _largestTaskNumber++;
  _tasks[_largestTaskNumber] = Task(_largestTaskNumber);
  return psfLineNumber;
}

bool Tasks::readTask(const char line[], const char psfFile[], const int psfLineNumber) {
  // ID , Expected , Best , Worst , Name
  int id;
  float expected;
  float best;
  float worst;
  char  name[MAX_TASK_NAME_LENGTH] = {0};
  int rc = sscanf(line, "%d , %f , %f , %f , %255c", &id, &expected, &best, &worst, name);
  if (rc != 5) {
      cerr << "Tasks::readFile(): Unable to parse line while reading file " << psfFile << ":" << psfLineNumber << "; exiting" << endl;
    exit(-1);
  }
  if (id > 0 && id < MAX_NUMBER_TASKS && _tasks[id].isError()) {
    _tasks[id] = Task(id, expected, best, worst, name);
    _numberOfTasks++;
    if (id > _largestTaskNumber)
      _largestTaskNumber = id;
  }
  else {
    // Should output some error message here; for now:
    return false;
  }
  return true;
}

bool Tasks::addTask(Task& t){
  if (t._identifier > 0 && t._identifier < MAX_NUMBER_TASKS && _tasks[t._identifier].isError()) {
    _tasks[t._identifier] = t;
    _numberOfTasks++;
    // cout << _longestPath << "$$$$$$$$$$$$$$$\n";
    if (t._identifier > _largestTaskNumber)
      _largestTaskNumber = t._identifier;
  }
  else{
    return false;
  }
  return true;
}
// There is no error checking in this, so if the PSF file is messed up, everything is messed up ...

bool Tasks::readDependencies(const char line[], const char psfFile[], const int psfLineNumber) {
  // ID (, id)+
  const char* pLine = line;
  int id = atoi(pLine);
  while (*pLine) {
    if (*pLine == ',') {
      if (!(_tasks[id].addDependency(atoi(pLine+1))))  // Need a better error output here
	return false;
    }
    ++pLine;
  }
  return true;
}

Tasks::Tasks() {
  _numberOfTasks = 0;
  _largestTaskNumber = 0;
  // _longestPath = 0;
  // Default constructor will be run for each element of the array automatically (and thus all will be error tasks)
}

Tasks::~Tasks() {
  TASKS_INVARIANT("Tasks::~Tasks()");
  _numberOfTasks = -1;
  // _longestPath = -1;
}

Tasks Tasks::criticalPath(){
  sN = LowerTriangularMatrix(_largestTaskNumber+1);
  LowerTriangularMatrix sM(_largestTaskNumber+1);
  sN.zero();
  sM.zero();
  // std::unordered_map<int, int> times;
  for (int i = 0; i <= _largestTaskNumber; ++i){
    if (!_tasks[i].isError()){
      Task t = _tasks[i];
      // cout << endl << endl << t <<  endl ;
      if(t._numberOfDependencies == 0){
        if(t._identifier != 0){
          sN(t._identifier,0) = t._expectedTime;
        }
        if(t._identifier == _largestTaskNumber){
          // for(int k = 0; k < _largestTaskNumber; k++){
          //   sN(_largestTaskNumber, k) = _tasks[k]._expectedTime;
          // }
          // cout << sN;
        }
      }
      else{
        for (int i = 0; i < t._numberOfDependencies; ++i){
          sN(t._identifier,t._dependsOn[i]) = t._expectedTime;
          // cout << t._dependsOn[i] << ": [";
          for(int j = 0; j < t._dependsOn[i]; j++){
            // cout << sN(t._dependsOn[i], j) << ", ";
            if(sN(t._dependsOn[i], j)!= 0){
              if(sN(t._identifier,j) != 0){
                sN(t._identifier,j) = sN(t._identifier,j) > sN(t._dependsOn[i], j)?sN(t._identifier,j):sN(t._dependsOn[i], j);
              }
              sN(t._identifier,j) = sN(t._dependsOn[i], j);
            }
          }
          // cout << "]" << endl;
        }
      }
      // cout << sN << endl << endl;
      // for(int i = 0;i)
      // if (t._numberOfDependencies == 0)
      //   cout << "[" << t._identifier << ", " << t._expectedTime << ", " << t._name << " (Depends On {})]";
      // else if (t._numberOfDependencies == 1)
      //   cout << "[" << t._identifier << ", " << t._expectedTime << ", " << t._name << " (Depends On {" << t._dependsOn[0] << "})]";
      // else {
      //   cout << "[" << t._identifier << ", " << t._expectedTime << ", " << t._name << " (Depends On {" << t._dependsOn[0];
      //   for (int i = 1; i < t._numberOfDependencies; ++i)
      //     cout << ", " << t._dependsOn[i];
      //   cout << "})]";
      // }
    }
    // cout << endl;
  }
  int ma = -1,id = -1;
  for(int i = 0; i <= _largestTaskNumber; ++i){
    for(int j = i-1; j >= 1; j--){
      if(sN(i,j) != 0){
        if(j > ma){
          id = i;
          ma = j;
          break;
        }
      }
    }
  }
  // cout << id << endl << _tasks[id] << endl;
  // cout << endl;
  // cout << endl;
  // for(int i = 0; i <= _largestTaskNumber; ++i){
  //   int su = 0;
  //   for(int j = 0; j < i; j++){
  //     su += sN(i,j);
  //   }
  //   times[i] = su;
  // }
  // for (auto& t : times)
  //   std::cout << t.first << "\t" << t.second << "\n";
  for(int i = _largestTaskNumber; i >= 0; i--){
    int j = i-1;
    for(; j >= 0; j--){
      if(sN(i,j) != 0){
        sM(i,j) = sN(i,j);
        break;
      }
    }
  }
  // cout << sM << endl << endl;
  std::unordered_map<int, int> dic3;
  for(int i = 1; i < _largestTaskNumber; i++){
    for(int j = i-1; j>= 0; j--){
      if(sM(i,j) != 0){
        dic3[i] = j;
        break;
      }
    }
  }
  // for (auto& t : dic3)
  //   std::cout << t.first << "\t" << t.second << "\n";
  // for()
  Task t = _tasks[id];
  int totalTime =  0;
  // cout << "TOTAL TIME: "<< totalTime << endl << endl;
  Tasks T;
  while(t._numberOfDependencies != 0){
    totalTime += t._expectedTime;
    int i = t._identifier;
    dic[i] = 0;
    int id = -1, ma = -1;
    for(int j = i-1; j >= 1; j--){
      if(sN(i,j) != 0){
        if(j > ma){
          ma = j;
          // cout << ma;
          break;
        }
      }
    }
    // cout << sN << endl;
    T.addTask(t);
    // cout << t << endl;
    // cout << ma << endl;


    t = _tasks[ma];
  }
  // cout << dic;
  T.addTask(t);
  // cout << t;
  #if 1
  totalTime += t._expectedTime;
	TotalTime = totalTime;
  //cout << "TOTAL TIME: "<< TotalTime << endl << endl;
  int i = t._identifier;
  dic[i] = 0;
  std::unordered_map<int, int> start;
  std::unordered_map<int, int> end;
  std::unordered_map<int, int> endTasks;
  // cout << sN;
  for(int i = 0; i < _largestTaskNumber; i++){
    int k = 0;
    for(int j = i+1; j < _largestTaskNumber; j++){
      // cout << "("<<j+1<<","<<i<<"):" << "("<<sN(j+1,i)<<")";
      k+= sN(j,i);
    }
    // cout << "K:" << k;
    // for (auto& t : endTasks)
    //   std::cout << "ENDTASKS0:" <<t.first << "\t" << t.second << "\n";
    if(k == 0){
      endTasks[i] = 1;
    }
    // cout << endl;
  }

  for (auto& t : endTasks)
    end[t.first] = totalTime;


  // for (auto& t : end)
  //   std::cout << "END1:" <<t.first << "\t" << t.second << "\n";
  //   // cout << endl << endl;
  // cout << endl << endl;

  for(int i = 0; i < _largestTaskNumber; i++){
    if(start.find(i) == start.end()){
      start[i] = start[dic3[i]] + _tasks[i]._expectedTime;
    }
  }

  // for (auto& t : dic)
  //   std::cout << "dic: "<<t.first << "\t" << t.second << "\n";
  // cout << endl << endl;

  for (auto& t : dic)
    end[t.first] = start[t.first];

    // for (auto& t : end)
    //   std::cout << "ENDdic: "<<t.first << "\t" << t.second << "\n";
    // cout << endl << endl;

    for(int i = _largestTaskNumber -1; i > 0; i--){
      Task l = _tasks[i];
      // cout << l << i << endl;
      for(int j = 0; j < l._numberOfDependencies; j++){
        if(end.find(l._dependsOn[j]) == end.end()){
          end[l._dependsOn[j]] = end[_tasks[i]._identifier] - _tasks[l._dependsOn[j]]._expectedTime;
        }
        else{
          end[l._dependsOn[j]] = min(end[_tasks[i]._identifier] - _tasks[l._dependsOn[j]]._expectedTime, end[l._dependsOn[j]]);
        }
      }
    }

    for(int i = 0; i < _largestTaskNumber; i++){
      dic[_tasks[i]._identifier] = end[_tasks[i]._identifier] - start[_tasks[i]._identifier];
    }

  // for (auto& t : start)
  //   std::cout << t.first << "\t" << t.second << "\n";
  // cout << endl << endl;
  //
  // for (auto& t : end)
  //   std::cout << "END2:" <<t.first << "\t" << t.second << "\n";
  // cout << endl << endl;
  // //
  // // cout << endl << endl;
  // //
  // for (auto& t : dic)
  //   std::cout << "DICF:" << t.first << "\t" << t.second << "\n";

  // cout << endl;
  // cout << endl;
#endif

  // cout << T._longestPath << "---------------\n";
  return T;
}                   // TODO FOR ASSIGNMENT; Not const, since you may wish to record it in the private data
float Tasks::pathLength(const Tasks& t) const{
	int k = 0;
  for(int i = 0; i <= t._largestTaskNumber; i++){
    if (!t._tasks[i].isError())
      k+=t._tasks[i]._expectedTime;
  }
  return k;
}; // TODO FOR ASSIGNMENT

float Tasks::slack(const Task& t) const{
  if(dic.find(t._identifier) == dic.end()){
    return -1;
  }
  return dic.at(t._identifier);
};       // TODO FOR ASSIGNMENT

std::ostream& operator<<(std::ostream& os, const Tasks& t) {
  if (t._numberOfTasks < 0) {
    cerr << "ostream& operator<<(): attempting to print deleted list of Tasks; exiting" << endl;
    exit(-1);
  }
  for (int i = 0; i <= t._largestTaskNumber; ++i)
    if (!t._tasks[i].isError())
      os << t._tasks[i] << endl;
  return os;
}
