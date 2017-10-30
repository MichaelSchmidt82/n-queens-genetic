/*
Author:         Michael Schmidt
Description:    Solve N Queens using a genetic algorithm
*/

/* Imports */
#include "globals.h"
#include "individual.h"
#include "set_once.h"

/* Prototypes */
void init_population(Population & population, const int POP_SIZE, const int N = -1);
void next_population(Population & population, Population & next_gen, const int POP_SIZE);
void fitness_function(Population & population);
void inbreed_check (Population & population, Population & next_gen, const int POP_SIZE);
double fRand (double fMin = 0.0, double fMax = 1.0);
IndividualPtr reproduce (const Population & population);

/* int main */
int main (int argc, char * argv[]) {
    assert(argc == 4 && "Provide Population size, Seed, and N as command ling args.");
    srand(atoi(argv[2]));

    /* Constants */
    const int POP_SIZE = atoi(argv[1]);
    const int N = atoi(argv[3]);

    Population curr_generaiton;
    Population next_generation;

    init_population(curr_generaiton, POP_SIZE, N);
    std::sort(curr_generaiton.begin(), curr_generaiton.end(), IndividualPtrCompare());

    while (!curr_generaiton[0]->solution()) {
        /* Examine and calculate fitness of current generation */
        fitness_function(curr_generaiton);

        /* Create & Calculate the fitness of the next generation */
        next_population(curr_generaiton, next_generation, POP_SIZE);
        fitness_function(next_generation);
        inbreed_check(curr_generaiton, next_generation, POP_SIZE);
    }

    curr_generaiton[0]->printer();
    return 0;
}

///////////////
/* FUNCTIONS */
//////////////

void init_population (Population & population, const int POP_SIZE, const int N) {
    int stop = POP_SIZE - 1;
    IndividualPtr individual;

    individual = (N == -1) ? new Individual() : new Individual(N);
    do {
        population.push_back(individual);
        individual = new Individual();
    } while (population.size() < stop);
    population.push_back(individual);
}

void next_population (Population & population, Population & next_gen, const int POP_SIZE) {
    /* Over reproduce */
    for (int i = POP_SIZE * 2; i >= 0; i--)
        next_gen.push_back(reproduce(population));

    /* Survival of the fittest */
    std::sort (next_gen.begin(), next_gen.end(), IndividualPtrCompare());
    for (int i = (POP_SIZE * 2); i > POP_SIZE -1 ; i--) {
        delete next_gen[i];
        next_gen.pop_back();
    }
}

void fitness_function(Population & population) {
    double start = 1.0;
    int sum = 0;

    for (IndividualPtr i : population)
        sum += i->queen_pairs();

    for (IndividualPtr i : population)
        start = i->set_fitness(sum, start);
}

void inbreed_check (Population & population, Population & next_gen, const int POP_SIZE) {
    bool inbreed = (*population[0] == *population[POP_SIZE - 1]);
    /* Checks to see if the population has become a master race */

    for (IndividualPtr i : population)
        delete i;
    population.clear();

    if (inbreed)
        init_population(population, POP_SIZE);
    else
        population = next_gen;

    next_gen.clear();
}

IndividualPtr reproduce (const Population & population) {
    IndividualPtr mother = population[0];
    IndividualPtr father = population[0];
    IndividualPtr child = nullptr;

    double threshold = fRand();
    for (IndividualPtr i : population)
        if ( i->fitness() > threshold)
            mother = i;

    threshold = fRand();
    for (IndividualPtr i : population)
        if ( i->fitness() > threshold)
            father = i;

    child = new Individual(*mother, *father);
    if (fRand() < 0.01)
        child->mutate();

    return child;
}

double fRand(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}
