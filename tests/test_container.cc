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

    AnimalContainer gas_container = AnimalContainer(animals, vec2(kTopWall, kLeftWall), vec2(kBottomWall, kRightWall));
    gas_container.AdvanceOneFrame();

    REQUIRE(gas_container.GetParticles()[0].GetVelocity().y == 5.0f);
  }

  SECTION("Bottom wall collision") {
    std::vector<animal_simulator::Herbivore> animals;
    animals.push_back(animal_simulator::Herbivore(vec2(50, 99), vec2(0, 5), 2, 5, ci::Color("red")));

    AnimalContainer gas_container = AnimalContainer(animals, vec2(kTopWall, kLeftWall), vec2(kBottomWall, kRightWall));
    gas_container.AdvanceOneFrame();

    REQUIRE(gas_container.GetParticles()[0].GetVelocity().y == -5.0f);
  }

  SECTION("Left wall collision") {
    std::vector<animal_simulator::Herbivore> animals;
    animals.push_back(animal_simulator::Herbivore(vec2(1, 50), vec2(-5, 0), 2, 5, ci::Color("red")));

    AnimalContainer gas_container = AnimalContainer(animals, vec2(kTopWall, kLeftWall), vec2(kBottomWall, kRightWall));
    gas_container.AdvanceOneFrame();

    REQUIRE(gas_container.GetParticles()[0].GetVelocity().x == 5.0f);
  }

  SECTION("Right wall collision") {
    std::vector<animal_simulator::Herbivore> animals;
    animals.push_back(animal_simulator::Herbivore(vec2(99, 50), vec2(5, 0), 2, 5, ci::Color("red")));

    AnimalContainer gas_container = AnimalContainer(animals, vec2(kTopWall, kLeftWall), vec2(kBottomWall, kRightWall));
    gas_container.AdvanceOneFrame();

    REQUIRE(gas_container.GetParticles()[0].GetVelocity().x == -5.0f);
  }
}

TEST_CASE("Test animal collisions") {
  SECTION("Horizontal animal collision") {
    std::vector<animal_simulator::Herbivore> animals;
    animals.push_back(animal_simulator::Herbivore(vec2(49, 50), vec2(5, 0), 3, 5, ci::Color("red")));
    animals.push_back(animal_simulator::Herbivore(vec2(51, 50), vec2(-5, 0), 3, 5, ci::Color("red")));

    AnimalContainer gas_container = AnimalContainer(animals, vec2(kTopWall, kLeftWall), vec2(kBottomWall, kRightWall));
    gas_container.AdvanceOneFrame();
    REQUIRE(gas_container.GetParticles()[0].GetVelocity().x == -5.0f);
    REQUIRE(gas_container.GetParticles()[1].GetVelocity().x == 5.0f);
  }

  SECTION("Verticle animal collision") {
    std::vector<animal_simulator::Herbivore> animals;
    animals.push_back(animal_simulator::Herbivore(vec2(50, 49), vec2(0, 5), 3, 5, ci::Color("red")));
    animals.push_back(animal_simulator::Herbivore(vec2(50, 51), vec2(0, -5), 3, 5, ci::Color("red")));

    AnimalContainer gas_container = AnimalContainer(animals, vec2(kTopWall, kLeftWall), vec2(kBottomWall, kRightWall));
    gas_container.AdvanceOneFrame();
    REQUIRE(gas_container.GetParticles()[0].GetVelocity().y == -5.0f);
    REQUIRE(gas_container.GetParticles()[1].GetVelocity().y == 5.0f);
  }

  SECTION("Touching animals moving away from each other maintain their original velocities") {
    std::vector<animal_simulator::Herbivore> animals;
    animals.push_back(animal_simulator::Herbivore(vec2(50, 49), vec2(0, -5), 3, 5, ci::Color("red")));
    animals.push_back(animal_simulator::Herbivore(vec2(50, 51), vec2(0, 5), 3, 5, ci::Color("red")));

    AnimalContainer gas_container = AnimalContainer(animals, vec2(kTopWall, kLeftWall), vec2(kBottomWall, kRightWall));
    gas_container.AdvanceOneFrame();
    REQUIRE(gas_container.GetParticles()[0].GetVelocity().y == -5.0f);
    REQUIRE(gas_container.GetParticles()[1].GetVelocity().y == 5.0f);
  }

  SECTION("Non-touching animals moving closer to each other maintain their original velocities") {
    std::vector<animal_simulator::Herbivore> animals;
    animals.push_back(animal_simulator::Herbivore(vec2(50, 45), vec2(0, 5), 3, 5, ci::Color("red")));
    animals.push_back(animal_simulator::Herbivore(vec2(50, 55), vec2(0, -5), 3, 5, ci::Color("red")));

    AnimalContainer gas_container = AnimalContainer(animals, vec2(kTopWall, kLeftWall), vec2(kBottomWall, kRightWall));
    gas_container.AdvanceOneFrame();
    REQUIRE(gas_container.GetParticles()[0].GetVelocity().y == 5.0f);
    REQUIRE(gas_container.GetParticles()[1].GetVelocity().y == -5.0f);
  }

  SECTION("Multiple animal collisions all detected") {
    std::vector<animal_simulator::Herbivore> animals;
    animals.push_back(animal_simulator::Herbivore(vec2(50, 49), vec2(1, 5), 3, 5, ci::Color("red")));
    animals.push_back(animal_simulator::Herbivore(vec2(50, 51), vec2(1, -5), 3, 5, ci::Color("red")));
    animals.push_back(animal_simulator::Herbivore(vec2(51, 50), vec2(-5, 1), 3, 5, ci::Color("red")));

    AnimalContainer gas_container = AnimalContainer(animals, vec2(kTopWall, kLeftWall), vec2(kBottomWall, kRightWall));
    gas_container.AdvanceOneFrame();

    //shows that velocities of ALL animals changed, not just 2 of the three after one frame
    REQUIRE(gas_container.GetParticles()[0].GetVelocity() != vec2(1, 5));
    REQUIRE(gas_container.GetParticles()[1].GetVelocity() != vec2(1, -5));
    REQUIRE(gas_container.GetParticles()[2].GetVelocity() != vec2(-5, 1));
  }
}

TEST_CASE("Herbivore Movement") {
  SECTION("Vertical movement") {
    std::vector<animal_simulator::Herbivore> animals;
    animals.push_back(animal_simulator::Herbivore(vec2(50, 45), vec2(0, 5), 3, 5, ci::Color("red")));

    AnimalContainer gas_container = AnimalContainer(animals, vec2(kTopWall, kLeftWall), vec2(kBottomWall, kRightWall));
    gas_container.AdvanceOneFrame();
    REQUIRE(gas_container.GetParticles()[0].GetPosition().y == 50);
  }

  SECTION("Horizontal movement") {
    std::vector<animal_simulator::Herbivore> animals;
    animals.push_back(animal_simulator::Herbivore(vec2(45, 50), vec2(5, 0), 3, 5, ci::Color("red")));

    AnimalContainer gas_container = AnimalContainer(animals, vec2(kTopWall, kLeftWall), vec2(kBottomWall, kRightWall));
    gas_container.AdvanceOneFrame();
    REQUIRE(gas_container.GetParticles()[0].GetPosition().x == 50);
  }
}

/*
TODO: Rename this test file. You'll also need to modify CMakeLists.txt.

You can (and should) create more test files; this project is too big
for all tests to be in the same file. Remember that, for each file (foo.cc)
containing non-trivial code, you should have a corresponding test file
(foo_test.cc)

Make sure to add any files that you create to CMakeLists.txt.

TODO Delete this comment and the placeholder test before submitting your code.
*/
