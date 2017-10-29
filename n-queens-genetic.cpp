/*



*/

/* Imports */
#include "globals.h"
#include "individual.h"
#include "set_once.h"

/* Prototypes */
void init_population(Population & population, const int POP_SIZE, const int N);
double fRand (double fMin = 0.0, double fMax = 1.0);
IndividualPtr reproduce (const Population & population);

/* int main */
int main (int argc, char * argv[]) {
    assert(argc == 4 && "Provide Population size, Seed, and N as command ling args.");
    srand(atoi(argv[2]));

    /* Constants */
    const int POP_SIZE = atoi(argv[1]);
    const int N = atoi(argv[3]);

    Population population;
    Population next_gen;
    IndividualPtr mother, father, child;

    init_population(population, POP_SIZE, N);

    int sum = 0;
    double start = 1.0;
    double threshold;
    for (int i = 0; i < N; i++) {

        /* Examine and calculate fitness of current generation */
        std::sort (population.begin(), population.end(), IndividualPtrCompare());
        for (IndividualPtr i : population)
            sum += i->queen_pairs();

        if (population[0]->solution()) {
            cout << "YES" << endl;
            break;
        }

        for (IndividualPtr i : population) {
            start = i->set_fitness(sum, start);
            i-> printer();
        }
        /* */

        /* Create, examine and calculate the fitness of the next generation */
        start = 1.0;
        sum = 0;

        for (int i = POP_SIZE * 2; i >= 0; i--)
            next_gen.push_back(reproduce(population));

        std::sort (next_gen.begin(), next_gen.end(), IndividualPtrCompare());
        for (int i = POP_SIZE * 2; i > POP_SIZE -1 ; i--) {
            delete next_gen[i];
            next_gen.pop_back();
        }

        for (IndividualPtr i : next_gen)
            sum += i->queen_pairs();

        cout << "--------------------NEXT----------" << endl;
        for (IndividualPtr i : next_gen) {
            start = i->set_fitness(sum, start);
            cout << start << " : ";
            i->printer();
        }

        start = 1;
        sum = 0;

        population.clear();
        population = next_gen;
        next_gen.clear();

        cout << "---------------------------------" << endl;
    }

    population[0]->printer();



    return 0;
}
//

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

    if (fRand() < 0.15)
        child->mutate();

    return child;
}
void init_population (Population & population, const int POP_SIZE, const int N) {
    int stop = POP_SIZE - 1;

    IndividualPtr individual = new Individual(N);
    do {
        population.push_back(individual);
        individual = new Individual();
    } while (population.size() < stop);
    population.push_back(individual);
}

double fRand(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}
