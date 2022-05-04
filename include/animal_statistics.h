//
// Created by Ayan Bhowmick on 5/3/22.
//
#include "herbivore.h"
#pragma once
namespace animal_simulator {
    /**
     * A class used to display animal statistics.
     */
    class AnimalStatistics {
    public:
        /**
         * Basic initializer for the statistics class.
         */
        AnimalStatistics();

        /**
         * Initializes the statistics class.
         * @param herbivore the herbivore whose statistics we will display.
         */
        AnimalStatistics(animal_simulator::Herbivore herbivore);

        /**
         * Draws the statistics.
         */
        void Draw() const;

        /**
         * @return whether we are ready to display status.
         */
        bool GetReadyStatus() const;

    private:
        /**
         * The herbivore whose statistics we will be displaying.
         */
        animal_simulator::Herbivore herbivore_;

        /**
         * The location of the statistics on the screen.
         */
        vec2 kStatStartingPosition = vec2(100, 640);

        /**
         * Checks whether stats should be displayed or not (stats will be displayed upon clicking).
         */
        bool has_clicked_ = false;
    };
}