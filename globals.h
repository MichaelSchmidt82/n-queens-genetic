/*
Author:         Michael Schmidt
Description:    Solve N Queens using a genetic algorithm
*/

#ifndef GLOBALS_H
#define GLOBALS_H

/* Imports */
//#include <algorithm>
#include <cassert>
#include <iostream>
#include <mutex>
#include <vector>
#include <iomanip>

/* Using Statements */
using std::atoi;
using std::cout;
using std::endl;
using std::setw;
using std::setprecision;
using std::vector;

/* Forward Declarations */
class Individual;

/* Typedefs */
typedef int Gene;
typedef Gene* Sequence;
typedef Individual* IndividualPtr;
typedef vector<IndividualPtr> Population;

#endif // !GLOBALS_H
