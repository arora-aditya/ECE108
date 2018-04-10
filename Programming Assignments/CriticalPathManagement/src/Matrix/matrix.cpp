///////////////////////////////////////////////////////////////////////
//
// Class LowerTriangularMatrix:
//
// Proveds a simple (strict) lower-bound matrix class.
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
// If tuples are large, this decision will have to b altered.
//
// This class also defines the empty tuple and the error tuple:
//   The empty tuple is <> and is defined as a tuple with 0 items.
//   The error tuple is defined as having -1 items; to facilitate bug
//   detection, the invariant for class tuple is _numItems >= -1.  The
//   error tuple can be thought of as the tuple equivalent of NaN.
//

#include "matrix.h"
#include "invariant.h"
#include <iostream>

using namespace std;

// Macros

#define LTM_INVARIANT(LOC) INVARIANT_TEST(_dimension < 0, LOC)

#define DATA_SIZE(DIMENSION) ((DIMENSION*(DIMENSION+1))>>1)
#define DATA_OFFSET(X,Y) (((X*(X-1))>>1)+Y)

// Define NO_BOUNDARY_CHECK if you wish to skip boundary checks

#ifdef NO_BOUNDARY_CHECK
#define BOUNDARY_CHECK(X,Y,DIMENSION)
#else
#define BOUNDARY_CHECK(X,Y,DIMENSION) do {                                                                 \
    if (!((X > 0) && (X < DIMENSION) && (Y < X))) {                                     		   \
      cerr << "Matrix access bound error: " << X << "; " << Y << "; " << DIMENSION << "; exiting" << endl; \
      exit(-1);                                                                                            \
    }                                                                                                      \
  } while(0)
#endif

// Methods

void LowerTriangularMatrix::zero() {
  LTM_INVARIANT("LowerTriangularMatrix::zero()");
  for (int i = 0; i < DATA_SIZE(_dimension); ++i)
    _data[i] = 0;
  return;
}

void LowerTriangularMatrix::operator=(const LowerTriangularMatrix& m) {
  LTM_INVARIANT("LowerTriangularMatrix::operator=()");
  // check m.INVARIANT;
  if (_data)
    delete[] _data;
  _dimension = m._dimension;
  if (m._data) {
    _data = new float[DATA_SIZE(_dimension)];
    for (int i = 0; i < DATA_SIZE(_dimension); ++i)
      _data[i] = m._data[i];
  }
  else
    _data = 0;
  return;
}

float& LowerTriangularMatrix::operator()(const int x, const int y) const {
  LTM_INVARIANT("LowerTriangularMatrix::operator=(const int x, const int y)");
  BOUNDARY_CHECK(x, y, _dimension);
  return *(_data+DATA_OFFSET(x,y));
}

LowerTriangularMatrix::LowerTriangularMatrix(const int dimension) {
  if (dimension < 0) {
    cerr << "LowerTriangularMatrix::LowerTriangularMatrix(" << dimension << "): invalid construction attempt; exiting" << endl;
    exit(-1);
  }
  _dimension = dimension;
  if (_dimension < 2) {
    _data = 0;
  }
  else {
    _data = new float[DATA_SIZE(_dimension)];
  }
}

LowerTriangularMatrix::LowerTriangularMatrix(const LowerTriangularMatrix& m) {
  if (m._dimension < 0) {
    cerr << "LowerTriangularMatrix::LowerTriangularMatrix(const LowerTriangularMatrix& m): accessing deleted matrix; exiting" << endl;
    exit(-1);
  }
  _dimension = m._dimension;
  if (m._dimension < 2) {
    _data = 0;
  }
  else {
    _data = new float[((_dimension*(_dimension+1))>>1)];  // N(N+1)/2
  }
}

LowerTriangularMatrix::~LowerTriangularMatrix() {
  LTM_INVARIANT("LowerTriangularMatrix::~LowerTriangularMatrix()");
  if (_data != 0)
    delete[] _data;
  _dimension = -1;
}

                                           // Allow matrix printing
std::ostream& operator<<(std::ostream& os, const LowerTriangularMatrix& m) {
  if (m._dimension < 0) {
    cerr << "LowerTriangularMatrix (ostream::operator<<): accessing deleted matrix; exiting" << endl;
    exit(-1);
  }
  if (m._dimension == 0) {
    os << "Null Matrix";
    return os;
  }
  if (m._dimension == 1) {
    os << "[]" << endl;
    return os;
  }
  os << "0: ";
  os << "[]" << endl;
  for (int i = 1; i < m._dimension; ++i) {
    os << i << ": ";
    os << "[";
    for (int j = 0; j < i; ++j) {
      os << m(i,j);
      if (j < (i-1))
	os << ", ";
    }
    os << "]" << endl;
  }
  return os;
};
