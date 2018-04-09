#include "tuple.h"
#include "invariant.h"
#include <iostream>
#include <limits.h>

#define TUPLE_INVARIANT(LOC) INVARIANT_TEST(_numItems < -1, LOC)

// Set up an error tuple to be returned as necessary
const Tuple errorTuple(-1,0);
#define TUPLE_ERROR INT_MIN

bool Tuple::isEmpty() const {
  TUPLE_INVARIANT("Tuple::isEmpty()");
  if (_numItems == 0)
    return true;
  return false;
}

bool Tuple::isError() const {
  TUPLE_INVARIANT("Tuple::isEmpty()");
  if (_numItems == -1)
    return true;
  return false;
}

int Tuple::size() const {
  TUPLE_INVARIANT("Tuple::size()");
  if (_numItems == -1)
    return TUPLE_ERROR;
  return _numItems;
}

// NEED TO FIX THIS FOR numItems == 0
Tuple Tuple::project(const int numItems, const int items[]) const {
  TUPLE_INVARIANT("Tuple::project()");
  if (numItems < 0)
    return (Tuple)errorTuple;

  int data[numItems];
  for (int i = 0; i < numItems; ++i) {
    if (items[i] < 1 || items[i] > _numItems)
      return (Tuple)errorTuple;
    data[i] = _pData[items[i]-1];
  }
  Tuple t(numItems,data);
  return t;
}

int Tuple::operator()(const int item) const {
  TUPLE_INVARIANT("Tuple::operator()()");
  if (item < 1 || item > _numItems)
    return TUPLE_ERROR;
  return _pData[item-1];
  return 0;
}

void Tuple::operator=(const Tuple& t) {
  TUPLE_INVARIANT("Tuple::operator=()");

  if (t._numItems < 0) {
    _numItems = -1;                  // Set it to the error tuple
    if (_pData != _data)             // Clean up allocated data, if any
      delete [] _pData;
    return;
  }

  _numItems = t._numItems;
  if (t._numItems > AVAILLEN) {      // Need to allocate space
    if (_pData != _data)             // Clean up allocated data, if any
      delete [] _pData;
    PDATALEN = t._numItems;
    _pData = new int[PDATALEN];
  }

  for (int i = 0; i < _numItems; ++i)
    _pData[i] = t._pData[i];
}

bool Tuple::operator==(const Tuple& t) const{
  TUPLE_INVARIANT("Tuple::operator==()");
  if (_numItems < 0 || t._numItems < 0)
    return false;

  if (_numItems != t._numItems)
    return false;

  for (int i = 0; i < _numItems; ++i)
    if (_pData[i] != t._pData[i])
      return false;

  return true;
}

Tuple Tuple::operator+(const Tuple& t) const {
  TUPLE_INVARIANT("Tuple::operator+()");

  if (t._numItems < 0)
    return (Tuple)errorTuple;

  int data[_numItems + t._numItems];
  for (int i = 0; i < _numItems; ++i) {
    data[i] = _pData[i];
  }
  for (int i = 0; i < t._numItems; ++i) {
    data[_numItems+i] = t._pData[i];
  }
  
  Tuple* cat = new Tuple((_numItems + t._numItems),data);
  return *cat;
}

  // Constructors and destructor
Tuple::Tuple() {
  _numItems = 0;
  _pData = _data;
}

Tuple::Tuple(const int t) {
  _numItems = 1;
  _pData = _data;
  _pData[0] = t;
}

Tuple::Tuple(const Tuple& t) : Tuple(t._numItems, t._pData) {}   // Req's C++11

Tuple::Tuple(const int numItems, const int data[]) {
  if (numItems < 0) {
    _numItems = -1;      // Set it to the error tuple
    _pData = _data;      // Otherwise the delete will crash
    return;
  }
  _numItems = numItems;
  if (_numItems > normalTupleSize) {
    PDATALEN = _numItems;
    _pData = new int[PDATALEN];
    
  }
  else {
    _pData = _data;
  }
  for (int i = 0; i < _numItems; ++i)
    _pData[i] = data[i];
}

Tuple::~Tuple() {
  TUPLE_INVARIANT("Tuple::~Tuple()");
  if (_pData != _data)   // Clean up allocated data
    delete [] _pData;
  _numItems = -2;        // Unset invariant
}
 

std::ostream& operator<<(std::ostream& os, const Tuple& t) {
#ifdef DEBUG
  std::cerr << "*** " << t._numItems << " ***" << std::endl;
#endif
  if (t._numItems == 0) {
    os << "<>";
    return os;
  }
  else if (t._numItems > 0) {
    os << "<" << t._pData[0];
    for (int i = 1; i < t._numItems; ++i)
      os << "," << t._pData[i];
    os << ">";
    return os;
  }
  else if (t._numItems == -1) {
    os << "<ERROR TUPLE>";
    return os;
  }
  else {
    std::cerr << "Error: Attempted to output deleted tuple; exiting";
    exit(-1);
  }
}
