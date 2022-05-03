//
// Created by Ayan Bhowmick on 5/3/22.
//
#include "herbivore.h"
#pragma once
namespace animal_simulator {
    class AnimalStatistics {
    public:
        AnimalStatistics(animal_simulator::Herbivore herbivore);

        void Draw() const;

        bool GetClicked();

    private:
        animal_simulator::Herbivore herbivore_;
        vec2 kStatStartingPosition;
        bool has_clicked_ = false;
    };
}