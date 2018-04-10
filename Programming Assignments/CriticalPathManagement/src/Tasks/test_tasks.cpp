////////////////////////////////////////////////////////////////////////////////
//
// Test Task/Tasks Classes
//
// This file contains a series of tests for the Task/Tasks classes
//
// PASW
//

#include <iostream>

#include "tasks.h"

using namespace std;

int main() {

  Task t1;
  Task t2(0);
  Task t3(12);
  Task t4(2,3,1,5,"Fred");

  cout << t1 << endl
       << t2 << endl
       << t3 << endl
       << t4 << endl;

  Tasks t;
  cout << t << endl;

  cout << "Read: " << t.readFile("../../PSF/sampleProject.psf") << " lines from PSF file" << endl;

  cout << t << endl;
  
  return 0;
}
