////////////////////////////////////////////////////////////////////////////////
//
// Invariant Handling
//
// INVARIANT_FAILURE() is an output and abort macro that takes a location
// parameter to enable debugging location
//
// INVARIANT() is an invariant test that takes the test as a parameter
// together with a location in if the invariant fails.
//
// TEST_INVARIANT() is a pseudonym for INVARIANT()
//
// There is no set/unset macro for invariants since they are case-specific 
//
// Change history:
// Created: 1 July 2017 ; PASW
//

#ifndef INVARIANT_H
#define INVARIANT_H

#include <iostream>
#include <stdlib.h>

#define INVARIANT_FAILURE(LOC) do { \
    std::cerr << LOC << ": Invariant Failure; Aborting" << std::endl;	\
    abort(); \
  } while (0)

#define INVARIANT_TEST(TEST, LOC) do {  \
    if ((TEST)) {		   \
      INVARIANT_FAILURE(LOC);      \
    }                              \
  } while(0)

#endif
