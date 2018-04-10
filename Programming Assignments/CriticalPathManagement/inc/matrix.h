///////////////////////////////////////////////////////////////////////
//
// Class LowerTriangularMatrix:
//
// Provides a simple (strict) lower triangular matrix class. 
// By default, there is bounds checking.  Boundary checking can be
// turned off by #defining NO_BOUNDARY_CHECK.  If it is off, access
// outside the boundaries of the triangle is undefined.
// 

#ifndef LOWER_TRIANGULAR_MATRIX_H
#define LOWER_TRIANGULAR_MATRIX_H

// #define BOUNDARY_CHECK

#include <iostream>


class LowerTriangularMatrix {
public:
  int  dimension() const { return _dimension; };            // Return Matrix dimension
  void zero();                                              // Zero the matrix
  void operator=(const LowerTriangularMatrix& m);           // Copy the matrix
  float& operator()(const int row, const int col) const;    // Access an element
  
  LowerTriangularMatrix() : LowerTriangularMatrix(0) {};
  LowerTriangularMatrix(const int dimension);
  LowerTriangularMatrix(const LowerTriangularMatrix& m);
 ~LowerTriangularMatrix();

private:
                                  // Allow matrix printing
  friend std::ostream& operator<<(std::ostream& os, const LowerTriangularMatrix& m);

  int    _dimension;              // Only one needed, since it is half-a-square
  float* _data;
};

#endif
