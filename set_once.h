/*
Author:         Michael Schmidt
Description:    Solve N Queens using a genetic algorithm
*/

#ifndef SET_ONCE_H
#define SET_ONCE_H

#include "globals.h"

template <typename T, typename Counter = unsigned char>
class SetOnce {
    public:
        SetOnce(const T& initval = T(), const Counter& initcount = 1) : val(initval), counter(initcount) {}
        SetOnce(const SetOnce&) = default;

        SetOnce<T, Counter>& operator=(const T& newval) {
            if (counter) {
                --counter;
                val = newval;
                return *this;
            }
            else throw "reassignment...";
        }
        operator const T&() const { return val; }
    protected:
        T val;
        Counter counter;
};
#endif // !SET_ONCE_H
