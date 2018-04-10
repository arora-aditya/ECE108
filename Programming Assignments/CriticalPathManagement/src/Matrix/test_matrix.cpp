////////////////////////////////////////////////////////////////////////////////
//
// Test Matrix Class
//
// This file contains a series of tests for the Matrix class
//
// PASW
//

#include <iostream>

#include "matrix.h"

using namespace std;

int main() {

  LowerTriangularMatrix m1(5);
  m1.zero();
  
  m1(2,0) = 1;
  cout << m1;

  LowerTriangularMatrix m2(0);
  m2 = m1;
  m2(3,2) = 3.2;
  cout << m2;

  cout << "Location (2,0) of m2 is: " << m2(2,0) << endl;

  cout.flush();

  m2(3,3) = 1;
  cout << "m2(3,3): " << m2(3,3) << endl;
  
  return 0;
}
