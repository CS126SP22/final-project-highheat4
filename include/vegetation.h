//
// Created by Ayan Bhowmick on 4/12/22.
//
#pragma once

#include "cinder/gl/gl.h"

using glm::vec2;

namespace animal_simulator {

/**
 * The animal object storing position and velocity.
 */
    class Vegetation {
    public:
        Vegetation();

    private:
        /**
         * The amount of food that is stored within the vegetation - scales with size.
         */
        float food_quantity_;

        /**
         * The growth rate of the food.
         */
        float growth_rate_;

        float kDefaultFoodQuantity = 5;
        float kDefaultGrowthRate = 1;
    };
}