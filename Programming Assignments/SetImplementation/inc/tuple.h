///////////////////////////////////////////////////////////////////////
//
// Class Tuple:
//
// Storage and access to tuples
// Tuples are defined as ordered lists
// Since we do not know how big a tuple will be (e.g., it can be the
// result of a Cartesian product), this class maintains Tuples and
// access control to the tuple.
//
// This class only maintains tuples of int.  The value INT_MIN
// is used as a error code, and so any use of it within a tuple
// entry is undefined.
//
// For the purpose of projection, the first item is identified
// as item 1, not item 0.  For example, if the tuple t = (43,1,17)
// then t(1) is 43 and t.project(2,[1,3]) is (43,17).
//
// Note that project() and concatenation return Tuples, not Tuple ref
// or Tuple pointers.  This is to simplify memory management and is
// done on the assumption that the tuples will not, generally, be large.
// If tuples are large, this decision will have to be altered.
//
// This class also defines the empty tuple and the error tuple:
//   The empty tuple is <> and is defined as a tuple with 0 items.
//   The error tuple is defined as having -1 items; to facilitate bug
//   detection, the invariant for class tuple is _numItems >= -1.  The
//   error tuple can be thought of as the tuple equivalent of NaN.
// 

#ifndef TUPLE_H
#define TUPLE_H

#include <iostream>

class Tuple {
 public:
  bool isEmpty() const;                    // Returns true if the tuple contains zero items
  bool isError() const;                    // Returns true if this is the error tuple

  int  size() const;
                                           // Take a tuple of size >= numItems and pull out the specific
                                           // items referenced in array items[]
                                           // The largest referenced item in items must be <= _numItems
  Tuple project(const int numItems, const int items[]) const;

                                           // Projection of a single item; item must be <= _numItems
  int  operator()(const int item) const;
                                           // Copy t to this tuple, dealing with memory management as necessary
  void operator=(const Tuple& t);
  bool operator==(const Tuple& t) const;
                                           // Concatenate t to this tuple, returing the result
  Tuple operator+(const Tuple& t) const;

  // Constructors and destructor
  Tuple();          
  Tuple(const int t);                      // Create a tuple with a single element: <t>
  Tuple(const Tuple& t);
  Tuple(const int numItems, const int data[]);
 ~Tuple(); 

 protected:
                                           // Allow tuple printing
  friend std::ostream& operator<<(std::ostream& os, const Tuple& t);
                                           // Most tuples should contain no more than this many items
  static const int normalTupleSize = 16;   // This should not be changed idly; it must be >= sizeof(int) and should be large
                                           // enough to accomodate the vast majority of tuples while not being so large as
                                           // to waste a lot of space.

  int  _numItems;                          // The actual number of items in the tuple
  int* _pData;                             // This is what should be used to access the data as it will _always_ point to the tuple.
                                           // If _numItems <= normalTupleLength, then _pData = _data; otherwise, space is allocated
                                           // for the token dynamically and _pData points to that space; the length of the space
                                           // allocated is stored in the first sizeof(int) bytes of _data
  int  _data[normalTupleSize];
  
#define PDATALEN (((int*)_data)[0])                                    // Convenient macro to determine allocated data size
#define AVAILLEN ((_pData == _data) ? (normalTupleSize) : (PDATALEN))  // Convenient macro to determine available data size
};

#endif
