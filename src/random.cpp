//
// Created by Ayan Bhowmick on 4/12/22.
//
#include <cstdlib>
#include "random.h"

namespace animal_simulator {
//// Source: Stackoverflow
    double Random::fRand(double fMin, double fMax) {
        bool is_negative = false;
        if (fMin < 0) {
            fMin = abs(fMin);
            fMax = abs(fMax);
            is_negative = true;
        }
        double f = (double) rand() / RAND_MAX;
        if (is_negative)
            return - (fMin + f * (fMax - fMin));
        return fMin + f * (fMax - fMin);
    }

    double Random::fReproductionDistribution(double number) {
        double kDivisor = 8;
        double to_return = fRand(number - (number / kDivisor), number + (number / kDivisor));
        return to_return;
    }
}