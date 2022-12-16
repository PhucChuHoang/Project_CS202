#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <cassert>
#include <algorithm>
#include "Constants.h"
namespace Random {
    extern const unsigned ALL_BITS;
    extern std::mt19937 rnd;
    typedef string State;

    void setSeed(unsigned seed);
    void setLevelSeed(int level);
    unsigned next();
    void loadState(State state);
    State getState();
    unsigned getBits(int n);
    float nextFloat01();
    float wnextFloat01(int type);
    unsigned next(unsigned l, unsigned r);
    int next(int l, int r);
    float next(float l, float r);
    float wnext(int type, float l, float r);
}

#endif