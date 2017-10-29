#include "individual.h"
#include "set_once.h"

int Individual::N(-1);
SetOnce<int> Individual::N_PAIRS(-1);

Individual::Individual() {

    sequence = new Gene[N];
    for (int i = 0; i < N; i++)
        sequence[i] = rand() % N;

    m_NonAttackingPairs = -1;
    m_Fitness = -1;
    queen_pairs();
}

Individual::Individual(int _N, const Sequence & s) {
    int pair_count = 0;

    N = _N;

    for (int i = N - 1; i > 0; i--)
        pair_count += i;
    N_PAIRS = pair_count;

    sequence = new Gene[N];

    if (s)
        for (int i = 0; i < N; i++)
            sequence[i] = s[i];
    else
        for (int i = 0; i < N; i++)
            sequence[i] = rand() % N;

    m_NonAttackingPairs = -1;
    m_Fitness = -1;
    queen_pairs();
}

Individual::Individual(const Individual & mother, const Individual & father) {
    int cutoff = rand() % N;
    bool order = rand() % 2;

    sequence = new Gene[N];

    if (cutoff == 0)
        cutoff++;
    if (cutoff == N - 1)
        cutoff--;

        if (order) {
        for (int i = 0; i < cutoff; i++)
            sequence[i] = mother.sequence[i];
        for (int i = cutoff; i < N; i++)
            sequence[i] = father.sequence[i];
    } else {
        for (int i = 0; i < cutoff; i++)
            sequence[i] = father.sequence[i];
        for (int i = cutoff; i < N; i++)
            sequence[i] = mother.sequence[i];
    }

    m_NonAttackingPairs = -1;
    m_Fitness = -1;
    queen_pairs();
}

bool Individual::operator< (const Individual & rhs) const {
    int t = this->queen_pairs();
    int r = rhs.queen_pairs();
    return t < r;
}

bool Individual::operator> (const Individual & rhs) const {
    int t = this->queen_pairs();
    int r = rhs.queen_pairs();
    return t > r;
}

bool Individual::operator> (double rhs) const {
    return (this->fitness() > rhs);
}

int Individual::operator[] (int i) const {
    if (i >= 0 && i < N)
        return sequence[i];
}

Individual::~Individual() {
    if (sequence)
        delete [] sequence;
}

int Individual::queen_pairs() const {
    int collisions = 0;

    if (m_NonAttackingPairs == -1) {
        /* Down */
        for (int g = N - 1; g > 0; g--)
            for (int c = g - 1; c >= 0; c--)
                if (sequence[g] == sequence[c])
                    collisions++;
        /* Down & Left */
        for (int row = 1; row < N; row++)
            for (int col = sequence[row - 1] - 1, i = row; i < N && col >= 0; i++, col--)
                if (sequence[i] == col)
                    collisions++;
        /* Down & Right */
        for (int row = 1; row < N; row++)
            for (int col = sequence[row - 1] + 1, i = row; i < N && col < N; i++, col++)
                if (sequence[i] == col)
                    collisions++;

        m_NonAttackingPairs = N_PAIRS - collisions;
    }
    return m_NonAttackingPairs;
}

double Individual::set_fitness(double sum, double start) {
    if (m_Fitness == -1)
        m_Fitness = start - (double(queen_pairs()) / sum);
    return m_Fitness;
}

void Individual::printer() const {
    for (int i = 0; i < N; i++)
        cout << sequence[i];

    cout << " (" << m_NonAttackingPairs << ")" << endl;
}

void Individual::mutate() {
    sequence[rand() % N] = rand() % N;

    m_NonAttackingPairs = -1;
    m_Fitness = -1;
    queen_pairs();
}
