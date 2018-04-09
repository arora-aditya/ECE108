////////////////////////////////////////////////////////////////////////////////
//
// Test Set Class
//
// This file contains a series of tests for the Token class
//
// PASW
//

#include <iostream>

#include "tuple.h"

using namespace std;

int main() {
  Tuple t1;
  int data[] = { 222, 111, 333 };
  Tuple t2(3, data);
  Tuple t3(t2);

  cout << "t1: " << t1 << endl
       << "t2: " << t2 << endl
       << "t3: " << t3 << endl;

  // Test projection
  for (int i = 1; i <= t2.size(); ++i) 
    cout << "t2(" << i << "): " << t2(i) << endl;

  int prj[] = {1,3};
  cout << "t2.project(2,prj): " << t2.project(2,prj) << endl;

  cout << "t1.size(): " << t1.size() << endl;
  cout << "t1(1): " << t1(1) << endl;
  cout << "t1.project(2,prj): " << t1.project(2,prj) << endl;

  t1 = t3;
  cout << "t1.size(): " << t1.size() << endl;
  cout << "t1(1): " << t1(1) << endl;
  cout << "t1.project(2,prj): " << t1.project(2,prj) << endl;

  t1 = t1 + t2;
  cout << "t1: " << t1 << endl;
  t1 = t1 + t1;
  cout << "t1: " << t1 << endl;
  t1 = t1 + t1;
  cout << "t1: " << t1 << endl;

  cout << "t1.size(): " << t1.size() << endl;
  cout << "t1(1): " << t1(1) << endl;
  cout << "t1.project(2,prj): " << t1.project(2,prj) << endl;

  Tuple t4(23);
  cout << "t4 + t2: " << t4 + t2 << endl;
  
  return 0;
}
