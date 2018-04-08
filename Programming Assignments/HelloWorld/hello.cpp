// 
// Hello World starter code for ECE 108 Lab 0
//

#include <iostream>
#include "hello.h"

using namespace std;	// this is needed for cout instead of std::cout

int main(int argc, char* argv[]) {
	switch (argc) {
		case 0: 
			cout << "No Arguments!" << endl;
			break;
		case 1:
			cout << MESSAGE << "World." << endl;
			break;
		case 2:
			cout << MESSAGE << argv[argc-1] << "." << endl;
         		break; 
		default:
			cout << "You have too many arguments for me!" << endl;
		break;
      
	} //switch (argc)
} // main()

