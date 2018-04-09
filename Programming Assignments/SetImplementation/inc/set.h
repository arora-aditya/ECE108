///////////////////////////////////////////////////////////////////////
//
// Class Set:
//
// Storage and access to sets
//
// This class maintains Sets and access control to the set.
//
// This class only maintains sets of tuples of int.  The value INT_MIN
// is used as a error code, and so any use of it within a tuple
// entry is undefined.
//
// For the purpose of projection, the first item in a tuple is identified
// as item 1, not item 0.
//
// Note that the various operations returns Sets, not Set ref
// or set pointers.  This is to simplify memory management and is
// done on the assumption that the Sets will not, generally, be large.
// If Sets are large, this decision will have to be altered.
//
// This class also defines the empty set and the error set:
//   The empty set is {} and is defined as a set with 0 items.
//   The error set is defined as having -1 items; to facilitate bug
//   detection, the invariant for class set is _numItems >= -1.  The
//   error set can be thought of as the set equivalent of NaN.
// 

#ifndef SET_H
#define SET_H

#include "tuple.h"
#include <iostream>

typedef bool predicate(const Tuple& t);

class Set {
 public:
  bool isEmpty() const;                    // Returns true if this is the empty set
  bool isError() const;                    // Returns true if this is the error set

  int  cardinality() const;

  Set union_(const Set& s) const;          // Note _ because "union" is a C++ keyword
  Set intersection(const Set& s) const;
  Set difference(const Set& s) const;
  Set select(predicate* p) const;          // Need to specify predicates
  Set operator()(const int item) const;
  Set project(const int numItems, const int items[]) const;
  Set cartesian(const Set& s) const;

  void operator=(const Set& s);

  Set();
  Set(const Set& s);
  Set(const int numElements, const int data[]);       // Set of tuples of size 1
  Set(const int numElements, const Tuple Tuples[]);   // Convert array of tuples to a set
 ~Set();

 protected:
                                             // Allow set printing
  friend std::ostream& operator<<(std::ostream& os, const Set& s);

  int    _numElements;
  int    _tupleArraySize;
  Tuple* _pTuples;
};

#endif
