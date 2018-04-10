// ECE 108 Lab 2 -- Sat Solver
//
// Read logical expressions in DIMACS format from files specified on the
// command line, and for each one print its name and one of "satisfiable",
// "unsatisfiable" or "tautology".

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <map>
#include <limits.h>
#include <bitset>
extern "C"{
	#include "dimacs_reader.h"
}

char satisfiable[] = {"satisfiable"};
char tautology[] = {"tautology"};
char unsatisfiable[] = {"unsatisfiable"};

using namespace std;
class file {
	public:
		int numVars;
		int numClauses;
		int status;
		// -1 -> Undefined, 0 -> Tautology, 1 -> Satisfiable, 2 -> Unsatisfiable
		int currentState;
		// -1 -> Undefined, 0 -> All trues uptill now, 1 -> Mix of true and false, 2 -> only false uptill now
		int * posClause;
		int * negClause;
		int clauseCounter;
		int trueClauses;
		bool posFlag, negFlag;
		map<int, int> checkMap;
		int clauseLen[100];

	file(int nv, int nc){
		numVars = nv;
		numClauses = nc;
		status = -1;
		posClause = new int[nc];
		negClause = new int[nc];
		trueClauses = 0;
		clauseCounter = 0;
		posFlag = negFlag = false;
	}

	void addClause(int numLits, int *  literals){
		if(numLits == 1 && literals[0] == 1){
			posFlag = true;
		}
		if(numLits == 1 && literals[0] == -1){
			negFlag = true;
		}
		clauseLen[clauseCounter] = numLits;
		posClause[clauseCounter] = 0;
		negClause[clauseCounter] = 0;
		for(int i = 0; i < numLits; i++){
			if(literals[i] > 0){
				posClause[clauseCounter] |= (1u << literals[i]-1);
			}
			else{
				negClause[clauseCounter] |= (1u << ((-1 * literals[i])-1));
			}
		}
		if(posClause[clauseCounter]&negClause[clauseCounter]){
			trueClauses +=1;
		}

		clauseCounter += 1;
	}

	bool evalClause(){
		if(trueClauses == numClauses){
			currentState = 0;
			return 1;
		}

		if(posFlag && negFlag){
			currentState = 2;
			return 1;
		}
		int i,j;
		i = 0;
		int max = 0;
		max |= (1u << numVars+1);
		max = max - 1;
		int rue = 0;
		while (i < max) {
			rue = 1;
			for (j = 0; j < numClauses; j++) {
				if (!(i&posClause[j] || (~i)&negClause[j]))	 {
					rue = 0;
					break;
				}
			}
			if (rue) {
				currentState = 1;
				return 1;
			}
			else{
				i++;
			}
		}
		currentState = 2;
		return 1;

	}
};

file F(0,0);

void init(int numvars, int numclauses) {
	// Callback function that gets passed to read_dimacs().
	// Indicates start of a new expression with up to numvars variables
	// and numclauses clauses.
	F = file(numvars, numclauses);

}

void add_clause(int numlits, int literals[]) {
	// Callback function that gets passed to read_dimacs().
	// The literals argument is an array of ints, numlits is its length.
	// Each literal is the index (starting from 1) of a variable.
	// Negative integers represent logical negations of variables.
	F.addClause(numlits, literals);
}

char *classify() {
	// return (char *) "unsatisfiable";
	// Evaluate the current expression and return one of
	// "satisfiable", "unsatisfiable" or "tautology".

	F.evalClause();
	// F.evalClause();
	switch(F.currentState){
		// -1 -> Undefined, 0 -> All trues uptill now, 1 -> Mix of true and false, 2 -> only false uptill now
		case 0: return (char *) "tautology";
		case 1: return (char *) "satisfiable";
		case 2: return (char *) "unsatisfiable";
	}

	return (char *) "unsatisfiable";

}

int main(int argc, char *argv[]) {
	int i;
	for (i = 1; i < argc; ++i) {
		read_dimacs(argv[i], init, add_clause);
		printf("%s: %s\n", argv[i], classify());
	}
	return 0;
}
