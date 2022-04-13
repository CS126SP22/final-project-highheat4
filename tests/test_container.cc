#include <catch2/catch.hpp>

#include <animal_container.h>
#include <herbivore.h>

using animal_simulator::AnimalContainer;
const float kTopWall = 0;
const float kLeftWall = 0;
const float kRightWall = 100;
const float kBottomWall = 100;

TEST_CASE("Test wall collisions") {

  SECTION("Top wall collision") {
    std::vector<animal_simulator::Herbivore> animals;
    animals.push_back(animal_simulator::Herbivore(vec2(50, 1), vec2(0, -5), 2, 5, ci::Color("red")));

    AnimalContainer animal_container = AnimalContainer(animals, vec2(kTopWall, kLeftWall), vec2(kBottomWall, kRightWall));
    animal_container.AdvanceOneFrame();

    REQUIRE(animal_container.GetAnimals()[0].GetVelocity().y == 5.0f);
  }

  SECTION("Bottom wall collision") {
    std::vector<animal_simulator::Herbivore> animals;
    animals.push_back(animal_simulator::Herbivore(vec2(50, 99), vec2(0, 5), 2, 5, ci::Color("red")));

    AnimalContainer animal_container = AnimalContainer(animals, vec2(kTopWall, kLeftWall), vec2(kBottomWall, kRightWall));
    animal_container.AdvanceOneFrame();

    REQUIRE(animal_container.GetAnimals()[0].GetVelocity().y == -5.0f);
  }

  SECTION("Left wall collision") {
    std::vector<animal_simulator::Herbivore> animals;
    animals.push_back(animal_simulator::Herbivore(vec2(1, 50), vec2(-5, 0), 2, 5, ci::Color("red")));

    AnimalContainer animal_container = AnimalContainer(animals, vec2(kTopWall, kLeftWall), vec2(kBottomWall, kRightWall));
    animal_container.AdvanceOneFrame();

    REQUIRE(animal_container.GetAnimals()[0].GetVelocity().x == 5.0f);
  }

  SECTION("Right wall collision") {
    std::vector<animal_simulator::Herbivore> animals;
    animals.push_back(animal_simulator::Herbivore(vec2(99, 50), vec2(5, 0), 2, 5, ci::Color("red")));

    AnimalContainer animal_container = AnimalContainer(animals, vec2(kTopWall, kLeftWall), vec2(kBottomWall, kRightWall));
    animal_container.AdvanceOneFrame();

    REQUIRE(animal_container.GetAnimals()[0].GetVelocity().x == -5.0f);
  }
}

TEST_CASE("Herbivore Movement") {
  SECTION("Vertical movement") {
    std::vector<animal_simulator::Herbivore> animals;
    animals.push_back(animal_simulator::Herbivore(vec2(50, 45), vec2(0, 5), 3, 5, ci::Color("red")));

    AnimalContainer animal_container = AnimalContainer(animals, vec2(kTopWall, kLeftWall), vec2(kBottomWall, kRightWall));
    animal_container.AdvanceOneFrame();
    REQUIRE(animal_container.GetAnimals()[0].GetPosition().y == 50);
  }

  SECTION("Horizontal movement") {
    std::vector<animal_simulator::Herbivore> animals;
    animals.push_back(animal_simulator::Herbivore(vec2(45, 50), vec2(5, 0), 3, 5, ci::Color("red")));

    AnimalContainer animal_container = AnimalContainer(animals, vec2(kTopWall, kLeftWall), vec2(kBottomWall, kRightWall));
    animal_container.AdvanceOneFrame();
    REQUIRE(animal_container.GetAnimals()[0].GetPosition().x == 50);
  }
}
