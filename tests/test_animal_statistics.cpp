//
// Created by Ayan Bhowmick on 5/3/22.
//

#include <catch2/catch.hpp>
#include "animal_statistics.h"
using namespace animal_simulator;
TEST_CASE("Animal statistics clicked boolean works properly.") {

    SECTION("Check unclicked before proper initialization.") {
        AnimalStatistics stats = AnimalStatistics();
        REQUIRE_FALSE(stats.GetReadyStatus());
    }

    SECTION("Check clicked after reassignment.") {
        AnimalStatistics stats = AnimalStatistics();
        Herbivore herb = Herbivore();
        stats = AnimalStatistics(herb);
        REQUIRE(stats.GetReadyStatus());
    }
}