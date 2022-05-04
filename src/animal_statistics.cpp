//
// Created by Ayan Bhowmick on 5/3/22.
//

#include "animal_statistics.h"

namespace animal_simulator {
    AnimalStatistics::AnimalStatistics() {
        has_clicked_ = false;
    }

    AnimalStatistics::AnimalStatistics(animal_simulator::Herbivore herbivore) {
        has_clicked_ = true;
        herbivore_ = herbivore;
    }

    bool AnimalStatistics::GetReadyStatus() const {
        return has_clicked_;
    }

    void AnimalStatistics::Draw() const {
        float kOffset = 15;
        vec2 write_position = kStatStartingPosition;

        ci::gl::drawString(
        "Position is: " + std::to_string(herbivore_.GetPosition().x) + ", "
        + std::to_string(herbivore_.GetPosition().y), write_position);

        write_position.y = write_position.y + kOffset;
        ci::gl::drawString(
                "Max health is: " + std::to_string(herbivore_.GetMaxHealth()), write_position);

        write_position.y = write_position.y + kOffset;
        ci::gl::drawString(
                "Current health is: " + std::to_string(herbivore_.GetHealth()), write_position);

        write_position.y = write_position.y + kOffset;
        ci::gl::drawString(
                "Max speed is: " + std::to_string(herbivore_.GetMaxSpeed()), write_position);

        write_position.y = write_position.y + kOffset;
        ci::gl::drawString(
                "Current speed is: " + std::to_string(herbivore_.GetSpeed()), write_position);

        write_position.y = write_position.y + kOffset;
        ci::gl::drawString(
                "Growth rate is: " + std::to_string(herbivore_.GetGrowthRate()), write_position);

        write_position.y = write_position.y + kOffset;
        ci::gl::drawString(
                "Size is: " + std::to_string(herbivore_.GetRadius()), write_position);

        write_position.y = write_position.y + kOffset;
        ci::gl::drawString(
                "Eat rate is: " + std::to_string(herbivore_.GetEatRate()), write_position);

        write_position.y = write_position.y + kOffset;
        ci::gl::drawString(
                "Color is: blue - " + std::to_string(herbivore_.GetColor().b)
                + " green - " + std::to_string(herbivore_.GetColor().g)
                + " red - " + std::to_string(herbivore_.GetColor().r), write_position);
    }
}