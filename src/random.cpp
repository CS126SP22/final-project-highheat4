//
// Created by Ayan Bhowmick on 4/12/22.
//
#include <cstdlib>
#include "random.h"

namespace animal_simulator {
//// Source: Stackoverflow
    double Random::fRand(double fMin, double fMax) {
        double f = (double) rand() / RAND_MAX;
        return fMin + f * (fMax - fMin);
    }
}