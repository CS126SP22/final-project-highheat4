//
// Created by Ayan Bhowmick on 4/12/22.
//
#pragma once

#include "cinder/gl/gl.h"

using glm::vec2;

namespace animal_simulator {

/**
 * The vegetation object storing data regarding the food source as well as growth rates etc.
 */
    class Vegetation {
    public:

        /**
         * Basic constructor for vegetation class.
         * @param top_left_corner The bounds that vegetation object can spawn in, top left corner
         * @param bottom_right_corner The bounds that vegetation object can spawn in, bottom right corner
         */
        Vegetation(vec2 top_left_corner, vec2 bottom_right_corner);

        /**
         * Increases vegetation size by its growth rate.
         */
        void Grow();

        //Basic getters.
        vec2 GetPosition() const;
        float GetSize() const;

        /**
         * Draws the current vegetation unit.
         */
        void Draw() const;

    private:
        /**
         * Current position of vegetation.
         */
        glm::vec2 my_position_;

        /**
         * The amount of food that is stored within the vegetation - scales with size.
         */
        float food_quantity_;

        /**
         * The growth rate of the food.
         */
        float growth_rate_;

        /**
         * Default food quantity and growth rate.
         */
        float kDefaultFoodQuantity = 1;
        float kDefaultGrowthRate = 0.25;
    };
}