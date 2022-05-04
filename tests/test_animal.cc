
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

TEST_CASE("Check reproduction within bounds") {
    SECTION("Similar child spawn point") {
        Herbivore animal =
                Herbivore(vec2(1, 50), vec2(0, 5), 2, 5, ci::Color("red"));

        for (int i = 0; i < 500; i++) {
            REQUIRE(abs(animal.Reproduce().GetPosition().x - animal.GetPosition().x) <= animal.GetRadius());
            REQUIRE(abs(animal.Reproduce().GetPosition().y - animal.GetPosition().y) <= animal.GetRadius());
        }
    }

    SECTION("Reproduction color randomization works") {
        Herbivore animal =
                Herbivore(vec2(1, 50), vec2(0, 5), 2, 5, ci::Color("red"));

        for (int i = 0; i < 500; i++) {
            REQUIRE(abs(animal.GetColor().b - animal.Reproduce().GetColor().b) <= animal.GetColor().b / 8);
            REQUIRE(abs(animal.GetColor().g - animal.Reproduce().GetColor().g) <= animal.GetColor().g / 8);
            REQUIRE(abs(animal.GetColor().r - animal.Reproduce().GetColor().r) <= animal.GetColor().r / 8);
        }
    }

    //as reproduction is a single method, checking color and speed changes properly is good enough to show it works overall.
    SECTION("Reproduction speed randomization works") {
        Herbivore animal =
                Herbivore(vec2(1, 50), vec2(0, 5), 2, 5, ci::Color("red"));

        for (int i = 0; i < 500; i++) {
            REQUIRE(abs(animal.GetMaxSpeed() - animal.Reproduce().GetMaxSpeed()) <= animal.GetMaxSpeed() / 8);
        }
    }
}