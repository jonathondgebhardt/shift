#include "shift/math/Angle.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

TEST_CASE("Angle zero initialized", "[math][Angle]")
{
    constexpr auto angle = shift::math::Angle{};
    CHECK_THAT(angle.angle(), Catch::Matchers::WithinRel(0.0f));
}

TEST_CASE("Angle parameterized ctor", "[math][Angle]")
{
    const auto angle = shift::math::Angle{1.0f};
    CHECK_THAT(angle.angle(), Catch::Matchers::WithinRel(1.0f));
}
