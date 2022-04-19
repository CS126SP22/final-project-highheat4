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
  };
}