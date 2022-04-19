
//
// Created by Ayan Bhowmick on 3/23/22.
//

//
// Created by Ayan Bhowmick on 3/23/22.
//
#include <catch2/catch.hpp>

#include <herbivore.h>

const float kWallTop = 0;
const float kWallLeft = 0;
const float kWallRight = 100;
const float kWallBottom = 100;
using namespace animal_simulator;
TEST_CASE("Test wall collision") {
  SECTION("Wall collision detection confirmed") {
    Herbivore animal =
        Herbivore(vec2(50, 1), vec2(0, -5), 2, 5, ci::Color("red"));
    animal.CheckContainerCollision(kWallLeft, kWallRight, kWallTop, kWallBottom);

    REQUIRE(animal.GetVelocity().y == 5.0f);
  }
}

TEST_CASE("Test animal distance calculation") {
  SECTION("Horizontal distance tested") {
    Herbivore animal =
        Herbivore(vec2(50, 1), vec2(0, 5), 2, 5, ci::Color("red"));
    Herbivore animal_2 =
        Herbivore(vec2(50, 2), vec2(0, -5), 2, 5, ci::Color("red"));

    REQUIRE(animal.CalculateDistance(animal_2) == 1);
  }

  SECTION("Vertical distance tested") {
    Herbivore animal =
        Herbivore(vec2(1, 50), vec2(0, 5), 2, 5, ci::Color("red"));
    Herbivore animal_2 =
        Herbivore(vec2(2, 50), vec2(0, -5), 2, 5, ci::Color("red"));

    REQUIRE(animal.CalculateDistance(animal_2) == 1);
  }
}

TEST_CASE("Energy implementation tested") {
    SECTION("Animal movement at first move is normal.") {
        Herbivore animal =
                Herbivore(vec2(1, 50), vec2(0, 5), 2, 5, ci::Color("red"));

        animal.Move();
        REQUIRE(animal.GetPosition() == vec2(1,55));
    }

    SECTION("Animal movement at second move is zero due to zero energy.") {
        Herbivore animal =
                Herbivore(vec2(1, 50), vec2(0, 5), 2, 5, ci::Color("red"));

        animal.Move();
        animal.Move();
        REQUIRE(animal.GetPosition() == vec2(1,55));
    }
}