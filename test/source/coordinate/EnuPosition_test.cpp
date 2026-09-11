#include "shift/coordinate/EnuPosition.hpp"

#include <catch2/catch_test_macros.hpp>

#include "shift/coordinate/EnuVector.hpp"
#include "shift/math/Utilities.hpp"

TEST_CASE("EnuPosition zero initialized", "[coordinate][EnuPosition]")
{
    constexpr auto position = shift::coordinate::EnuPosition{};
    CHECK(shift::math::floating_point_eq(position.east, 0.0));
    CHECK(shift::math::floating_point_eq(position.north, 0.0));
    CHECK(shift::math::floating_point_eq(position.up, 0.0));
}

TEST_CASE("EnuPosition single double", "[coordinate][EnuPosition]")
{
    constexpr auto position = shift::coordinate::EnuPosition{1.0};
    CHECK(shift::math::floating_point_eq(position.east, 1.0));
    CHECK(shift::math::floating_point_eq(position.north, 1.0));
    CHECK(shift::math::floating_point_eq(position.up, 1.0));
}

TEST_CASE("EnuPosition triple double", "[coordinate][EnuPosition]")
{
    constexpr auto position = shift::coordinate::EnuPosition{1.0, 2.0, 3.0};
    CHECK(shift::math::floating_point_eq(position.east, 1.0));
    CHECK(shift::math::floating_point_eq(position.north, 2.0));
    CHECK(shift::math::floating_point_eq(position.up, 3.0));
}

TEST_CASE("EnuPosition operator==", "[coordinate][EnuPosition]")
{
    CHECK(shift::coordinate::EnuPosition{1.0}
          == shift::coordinate::EnuPosition{1.0});
    CHECK(shift::coordinate::EnuPosition{0.0}
          != shift::coordinate::EnuPosition{1.0});
}

TEST_CASE("EnuPosition operator+", "[coordinate][EnuPosition]")
{
    constexpr auto position = shift::coordinate::EnuPosition{};
    constexpr auto vector = shift::coordinate::EnuVector{1.0, 2.0, 3.0};
    constexpr auto result = position + vector;
    CHECK(shift::math::floating_point_eq(result.east, vector.east));
    CHECK(shift::math::floating_point_eq(result.north, vector.north));
    CHECK(shift::math::floating_point_eq(result.up, vector.up));
}

TEST_CASE("EnuPosition operator+=", "[coordinate][EnuPosition]")
{
    auto position = shift::coordinate::EnuPosition{};
    constexpr auto vector = shift::coordinate::EnuVector{1.0, 2.0, 3.0};
    position += vector;
    CHECK(shift::math::floating_point_eq(position.east, vector.east));
    CHECK(shift::math::floating_point_eq(position.north, vector.north));
    CHECK(shift::math::floating_point_eq(position.up, vector.up));
}

TEST_CASE("EnuPosition operator-", "[coordinate][EnuPosition]")
{
    constexpr auto position = shift::coordinate::EnuPosition{1.0, 2.0, 3.0};

    SECTION("EnuVector")
    {
        constexpr auto vector = shift::coordinate::EnuVector{
            position.east, position.north, position.up};
        CHECK(position - vector == shift::coordinate::EnuPosition{});
    }

    SECTION("EnuPosition")
    {
        constexpr auto vector = shift::coordinate::EnuPosition{
            position.east, position.north, position.up};
        CHECK(position - vector == shift::coordinate::EnuVector{});
    }
}

TEST_CASE("EnuPosition operator-=", "[coordinate][EnuPosition]")
{
    auto position = shift::coordinate::EnuPosition{1.0, 2.0, 3.0};
    const auto vector = shift::coordinate::EnuVector{
        position.east, position.north, position.up};
    position -= vector;
    CHECK(position == shift::coordinate::EnuPosition{});
}
