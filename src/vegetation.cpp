//
// Created by Ayan Bhowmick on 4/12/22.
//
#include "vegetation.h"
#include "random.h"

namespace animal_simulator {

    Vegetation::Vegetation(glm::vec2 top_left_corner, glm::vec2 bottom_right_corner) {
        food_quantity_ = kDefaultFoodQuantity;
        growth_rate_ = kDefaultGrowthRate;
        my_position_ = vec2(Random::fRand(top_left_corner.x, bottom_right_corner.x),
                            Random::fRand(top_left_corner.y, bottom_right_corner.y));
    }

    void Vegetation::Grow() {
        food_quantity_ += growth_rate_;
    }

    void Vegetation::Draw() const {
        ci::gl::color(ci::Color("green"));
        ci::gl::drawSolidCircle(my_position_, food_quantity_);
    }

    vec2 Vegetation::GetPosition() const {
        return my_position_;
    }

    float Vegetation::GetSize() const {
        return food_quantity_;
    }

    bool Vegetation::Eaten(float amount_eaten) {
        food_quantity_ -= amount_eaten;
        return (food_quantity_ < 0);
    }
}