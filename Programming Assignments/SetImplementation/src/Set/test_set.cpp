////////////////////////////////////////////////////////////////////////////////
//
// Test Set Class
//
// This file contains a series of tests for the Set class
// TO DO: Create grade calculation example
//
// PASW
//

#include <iostream>

#include "set.h"

using namespace std;

// Example of a selection predicate function
bool tuple1Large(const Tuple& t) {
  return (t(1) > 200);
}

bool equals(const Tuple& t) {
  return (t(1) == t(2));
}

int main() {
  Set s1;                              // Create an empty set
  int data[] = { 222, 111, 333, 333 };
  Set s2(3, data);                     // Create a set of three unary tuples
  Set s100(4, data);
	Tuple t1;
	Tuple t2(3,data);
	Tuple t3(2,data);
	Tuple t4(1,data);
	Tuple t5[] = {t1,t2,t3,t4};
	Set s6(4, t5);
	Set s7(3, t5);
	Set s8 = s7;
  Set s3 = s2.cartesian(s2);           // This should produce a set of 9 binary tuples

  Set s4 = s3.select(&tuple1Large);    // This should eliminate all elements from set s3 where the first item in the tuple <= 200

  cout << "s1: " << s1 << endl
       << "s2: " << s2 << endl
			 << "s6: " << s6 << endl
       << "s7: " << s7 << endl
			 << "s8: " << s8 << endl
			 << "s1 x s2: " << s1.cartesian(s2) << endl
       << "s3: " << s3 << endl
       << "s100: " << s100 << endl
			 << "s4: " << s4 << endl
       << "s3.select(equals): " << s3.select(&equals) << endl;

  // Test union (with duplicate elimination)
  cout << "s2.union_(s2): " << s2.union_(s2) << endl;
  cout << "s3.union_(s2): " << s3.union_(s2) << endl;
	cout << "s4.union_(s3): " << s4.union_(s3) << endl;
	cout << "s6.union_(s3): " << s6.union_(s3) << endl;	
  
  // Test union (with duplicate elimination)
  cout << "s2.intersection((s3.union_(s2))): " << s2.intersection(s3.union_(s2)) << endl;
  cout << "s2.intersection(s2): " << s2.intersection(s2) << endl;
  
  // Test difference (with duplicate elimination)
  cout << "s2.difference((s3.union_(s2))): " << s2.difference(s3.union_(s2)) << endl;
  cout << "(s3.union_(s2)).difference(s2): " << (s3.union_(s2)).difference(s2) << endl;
  cout << "s2.difference(s2): " << s2.difference(s2) << endl;

#if 1
  // Test projection
  for (int i = 1; i <= s2.cardinality(); ++i) 
    cout << "s2(" << i << "): " << s2(i) << endl;
#endif
  Set s5 = s3.cartesian(s2);
  cout << "s5: " << s5 << endl;
  int prj[] = {1,3};
  cout << "s5.project(2,prj): " << s5.project(2,prj) << endl;
#if 2
  cout << "s1: " << s1 << endl;
	cout << "s1.cardinality(): " << s1.cardinality() << endl;
  cout << "s1(1): " << s1(1) << endl;
  cout << "s1.project(2,prj): " << s1.project(2,prj) << endl;
	cout << endl;
	cout << "s1.project(0,prj): " << s1.project(0,prj) << endl;
	cout << endl; 
  s1 = s3;
  cout << "s1: " << s1 << endl;
	cout << "s1.cardinality(): " << s1.cardinality() << endl;
  cout << "s1(1): " << s1(1) << endl;
  cout << "s1.project(2,prj): " << s1.project(2,prj) << endl;
	cout << endl;
	cout << "s1: " << s1 << endl;
  cout << "s1.cardinality(): " << s1.cardinality() << endl;
  cout << "s1(1): " << s1(1) << endl;
  cout << "s1.project(2,prj): " << s1.project(2,prj) << endl;
#endif  
  return 0;
}
