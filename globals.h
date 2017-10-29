#ifndef GLOBALS_H
#define GLOBALS_H

/* Imports */
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

/* Using Statements */
using std::atoi;
using std::cout;
using std::cin;
using std::endl;
using std::vector;

/* Forward Declarations */
class Individual;

/* Typedefs */
typedef int Gene;
typedef int* Sequence;
typedef Individual* IndividualPtr;
typedef vector<IndividualPtr> Population;







#endif // !GLOBALS_H
