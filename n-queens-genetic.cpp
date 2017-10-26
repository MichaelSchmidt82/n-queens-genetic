/*



*/

/* Imports */
#include "globals.h"

/* Prototypes */
void init_population (Population & population, const int POP_SIZE, const int N);
int fitness (const Individual & indiv, const int N);

/* int main */
int main (int argc, char * argv[]) {
    assert(argc == 4 && "Provide Population size, Seed, and N as command ling args.");
    srand(atoi(argv[2]));

    /* Constants */
    const int POP_SIZE = atoi(argv[1]);
    const int N = atoi(argv[3]);

    Population population;

    init_population(population, POP_SIZE, N);

    fitness (population[0], N);

    for (Individual i : population) {
        for (int g = 0; g < N; g++)
            cout << i[g];
        cout << endl;
    }

    return 0;
}

void init_population (Population & population, const int POP_SIZE, const int N) {
    for (int p = 0; p < POP_SIZE; p++) {
        Individual i = new int[N];
        for (int gene = 0; gene < N; gene++)
            i[gene] = rand() % N;
        population.push_back(i);
    }
}

int fitness (const Individual & indiv, const int N) {
    static bool first_call = true;
    static int n_pairs = 0;
    int collisions = 0;

    if (first_call) {
        for (int i = N - 1; i > 0; i--)
            n_pairs += i;

        first_call = false;
    }
    /* Down */
    for (int g = N - 1; g > 0; g--)
        for (int c = g - 1; c >= 0; c--)
            if (indiv[g] == indiv[c])
                collisions++;

    /* Down & Left */
    for (int row = 1; row < N; row++)
        for (int col = indiv[row - 1] - 1, i = row; i < N && col >= 0; i++, col--)
            if (indiv[i] == col)
                collisions++;

    /* Down & Right */
    for (int row = 1; row < N; row++)
        for (int col = indiv[row - 1] + 1, i = row; i < N && col < N; i++, col++)
            if (indiv[i] == col)
                collisions++;

    cout << n_pairs - collisions << endl;
    return n_pairs - collisions;
}
