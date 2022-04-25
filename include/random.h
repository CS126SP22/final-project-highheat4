//
// Created by Ayan Bhowmick on 4/12/22.
//
#pragma once

namespace animal_simulator {
  class Random {
    public:
    /**
     * Calculates a random double between fMin and fMax.
     * @param fMin the minimum randomized double that can be returned.
     * @param fMax the maximum randomized double that can be returned.
     * @return A random double between fMin and fMax.
     */
    static double fRand(double fMin, double fMax);

    /**
     * Calculates a random number based off of the reproduction distribution.
     * @param target The number we are trying to generate a number similar to.
     * @return a number similar to the target number.
     */
    static double fReproductionDistribution(double target);
  };
}