//
// Created by Ayan Bhowmick on 4/12/22.
//

#include <catch2/catch.hpp>

#include <vegetation.h>
namespace animal_simulator {
    TEST_CASE("Checks vegetation spawn correctness.") {
        SECTION("Passes horizontal spawn check.") {
            for (int i = 0; i < 500; i++) {
                Vegetation vegetation = Vegetation(vec2(0,0), vec2(100,100));
                REQUIRE(vegetation.GetPosition().x > 0);
                REQUIRE(vegetation.GetPosition().x < 100);
            }
        }

        SECTION("Passes vertical spawn check.") {
            for (int i = 0; i < 500; i++) {
                Vegetation vegetation = Vegetation(vec2(0,0), vec2(100,100));
                REQUIRE(vegetation.GetPosition().y > 0);
                REQUIRE(vegetation.GetPosition().y < 100);
            }
        }
    }
}