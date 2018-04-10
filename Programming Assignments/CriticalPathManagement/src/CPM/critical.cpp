#include <iostream>
#include "tasks.h"
#include "matrix.h"

using namespace std;

//
// This is a test driver for testing your CPM code; it contains very little
// testing at present; you should add tests to it.
//


int main(const int argc, const char* const argv[]) {
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " <PSF File>" << endl;
    exit(-1);
  }

  Tasks t;
  if (t.readFile(argv[1]) < 0) {
    //    cerr << argv[0] << ": Error reading " << argv[1] << endl;
    exit(-1);
  }
  Tasks criticalPath = t.criticalPath();
  cout << "Critical Path is: " << endl << criticalPath << endl;

  cout << "Length of Critical Path is: " << t.pathLength(criticalPath) << endl;

  for(int i = 0; i < t.largestTaskNumber(); i++){
    cout << "Slack for task "<<i<<" is " << t.slack(t(i)) << endl;
  }


  return 0;
}
