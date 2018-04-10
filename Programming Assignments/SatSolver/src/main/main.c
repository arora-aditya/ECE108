// ECE 108 Lab 2 -- Sat Solver
//
// Read logical expressions in DIMACS format from files specified on the
// command line, and for each one print its name and one of "satisfiable",
// "unsatisfiable" or "tautology".

#include <stdio.h>
#include "dimacs_reader.h"

void init(int numvars, int numclauses) {
	// Callback function that gets passed to read_dimacs().
	// Indicates start of a new expression with up to numvars variables
	// and numclauses clauses.
}

void add_clause(int numlits, int literals[]) {
	// Callback function that gets passed to read_dimacs().
	// The literals argument is an array of ints, numlits is its length.
	// Each literal is the index (starting from 1) of a variable.
	// Negative integers represent logical negations of variables.
}

char *classify() {
	// Evaluate the current expression and return one of
	// "satisfiable", "unsatisfiable" or "tautology".
	return "unsatisfiable";
}

int main(int argc, char *argv[]) {
	int i;
	for (i = 1; i < argc; ++i) {
		read_dimacs(argv[i], init, add_clause);
		printf("%s: %s\n", argv[i], classify());
	}
	return 0;
}

