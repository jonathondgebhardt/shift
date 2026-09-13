#include "shift/math/DegreesAngle.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

TEST_CASE("Angle zero initialized", "[math][Angle]")
{
    constexpr auto angle = shift::math::DegreesAngle{};
    CHECK_THAT(angle.angle(), Catch::Matchers::WithinRel(0.0f));
}

TEST_CASE("Angle parameterized ctor", "[math][Angle]")
{
    const auto angle = shift::math::DegreesAngle{1.0f};
    CHECK_THAT(angle.angle(), Catch::Matchers::WithinRel(1.0f));
}

TEST_CASE("Angle to_string", "[math][Angle]")
{
    const auto angle = shift::math::DegreesAngle{1.0};
    CHECK_THAT(angle.to_string(), Catch::Matchers::StartsWith("1.0"));
}
