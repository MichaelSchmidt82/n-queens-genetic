#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include "globals.h"
#include "set_once.h"

class Individual {
    public:
        Individual();
        Individual(int N, const Sequence & s = nullptr);
        Individual(const Individual & mother, const Individual & father);
        ~Individual();

        bool operator< (const Individual & rhs) const;
        bool operator> (const Individual & rhs) const;
        bool operator> (double rhs) const;
        int operator[] (int i) const;

        int queen_pairs() const;
        bool solution() const { return N_PAIRS == queen_pairs();}
        double fitness () const { return m_Fitness; }
        void printer() const;

        double set_fitness (double sum, double start);
        void mutate();
    private:
        mutable int m_NonAttackingPairs;
        mutable double m_Fitness;
        Sequence sequence;

        static int N;
        static SetOnce<int> N_PAIRS;
};

struct IndividualPtrCompare {
	bool operator()(const IndividualPtr lhs, const IndividualPtr rhs) const { return *lhs > *rhs; }
};

#endif // !INDIVIDUAL_H
