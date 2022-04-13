//
// Created by Ayan Bhowmick on 4/12/22.
//
#include "vegetation.h"

namespace animal_simulator {
    Vegetation::Vegetation() {
        food_quantity_ = kDefaultFoodQuantity;
        growth_rate_ = kDefaultGrowthRate;
    }

    Vegetation::Vegetation(vec2 top_left_corner, vec2 bottom_right_corner) {
        food_quantity_ = kDefaultFoodQuantity;
        growth_rate_ = kDefaultGrowthRate;
        top_left_spawn_ = top_left_corner;
        bottom_right_corner = bottom_right_spawn_;
    }

    void Vegetation::Grow() {
        food_quantity_ += growth_rate_;
    }

    void Vegetation::Draw() {
        ci::gl::color(ci::Color("green"));
        ci::gl::drawSolidCircle(my_position_, food_quantity_);
    }
}