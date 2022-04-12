
//
// Created by Ayan Bhowmick on 3/23/22.
//

//
// Created by Ayan Bhowmick on 3/23/22.
//
#include <catch2/catch.hpp>

#include <particle.h>

const float kWallTop = 0;
const float kWallLeft = 0;
const float kWallRight = 100;
const float kWallBottom = 100;
using namespace idealgas;
TEST_CASE("Test wall collision") {
  SECTION("Wall collision detection confirmed") {
    Particle particle =
        Particle(vec2(50, 1), vec2(0, -5), 2, 5, ci::Color("red"));
    particle.CheckContainerCollision(kWallLeft, kWallRight, kWallTop, kWallBottom);

    REQUIRE(particle.GetVelocity().y == 5.0f);
  }
}

TEST_CASE("Test particle collision") {
  SECTION("Particle approaching particle2 detected") {
    Particle particle =
        Particle(vec2(50, 1), vec2(0, 5), 2, 5, ci::Color("red"));
    Particle particle2 =
        Particle(vec2(50, 50), vec2(0, -5), 2, 5, ci::Color("red"));

    REQUIRE(particle.ApproachesOtherParticle(particle2));
  }

  SECTION("Particle touching particle2 detected") {
    Particle particle =
        Particle(vec2(50, 1), vec2(0, 5), 2, 5, ci::Color("red"));
    Particle particle2 =
        Particle(vec2(50, 2), vec2(0, -5), 2, 5, ci::Color("red"));

    REQUIRE(particle.IsTouchingParticles(particle2));
  }

  SECTION("Touching particle velocities are switched") {
    Particle particle =
        Particle(vec2(50, 1), vec2(0, 5), 2, 5, ci::Color("red"));
    Particle particle2 =
        Particle(vec2(50, 2), vec2(0, -5), 2, 5, ci::Color("red"));

    REQUIRE(particle.CalculateCollisionResults(particle2)[0][1] == -5);
  }
}

TEST_CASE("Test particle distance calculation") {
  SECTION("Horizontal distance tested") {
    Particle particle =
        Particle(vec2(50, 1), vec2(0, 5), 2, 5, ci::Color("red"));
    Particle particle2 =
        Particle(vec2(50, 2), vec2(0, -5), 2, 5, ci::Color("red"));

    REQUIRE(particle.CalculateDistance(particle2) == 1);
  }

  SECTION("Vertical distance tested") {
    Particle particle =
        Particle(vec2(1, 50), vec2(0, 5), 2, 5, ci::Color("red"));
    Particle particle2 =
        Particle(vec2(2, 50), vec2(0, -5), 2, 5, ci::Color("red"));

    REQUIRE(particle.CalculateDistance(particle2) == 1);
  }
}