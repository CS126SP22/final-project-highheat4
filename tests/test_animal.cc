
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
    animal
    .CheckContainerCollision(kWallLeft, kWallRight, kWallTop, kWallBottom);

    REQUIRE(animal
    .GetVelocity().y == 5.0f);
  }
}

TEST_CASE("Test animal"
          " collision") {
  SECTION("Herbivore approaching animal"
          "2 detected") {
    Herbivore animal =
        Herbivore(vec2(50, 1), vec2(0, 5), 2, 5, ci::Color("red"));
    Herbivore animal_2 =
        Herbivore(vec2(50, 50), vec2(0, -5), 2, 5, ci::Color("red"));

    REQUIRE(animal.ApproachesOtherAnimal(animal_2));
  }

  SECTION("Herbivore touching animal"
          "2 detected") {
    Herbivore animal =
        Herbivore(vec2(50, 1), vec2(0, 5), 2, 5, ci::Color("red"));
    Herbivore animal_2 =
        Herbivore(vec2(50, 2), vec2(0, -5), 2, 5, ci::Color("red"));

    REQUIRE(animal.IsTouchingAnimal(animal_2));
  }

  SECTION("Touching animal"
          " velocities are switched") {
    Herbivore animal =
        Herbivore(vec2(50, 1), vec2(0, 5), 2, 5, ci::Color("red"));
    Herbivore animal_2 =
        Herbivore(vec2(50, 2), vec2(0, -5), 2, 5, ci::Color("red"));

    REQUIRE(animal
    .CalculateCollisionResults(animal_2)[0][1] == -5);
  }
}

TEST_CASE("Test animal"
          " distance calculation") {
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