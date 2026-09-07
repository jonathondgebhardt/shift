#include <limits>

#include "shift/math/Utilities.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("floating_point_eq", "[math][Utilities]")
{
    constexpr auto zero = 0.0;
    CHECK(shift::math::floating_point_eq(zero, zero));

    const auto next_after_zero =
        zero + std::numeric_limits<decltype(zero)>::epsilon();
    CHECK(!shift::math::floating_point_eq(zero, next_after_zero));
}
