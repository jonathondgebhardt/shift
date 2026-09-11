#include "shift/coordinate/EcefPosition.hpp"

#include <catch2/catch_test_macros.hpp>

#include "shift/coordinate/EcefVector.hpp"
#include "shift/math/Utilities.hpp"

TEST_CASE("EcefPosition zero initialized", "[coordinate][EcefPosition]")
{
    constexpr auto position = shift::coordinate::EcefPosition{};
    CHECK(shift::math::floating_point_eq(position.x, 0.0));
    CHECK(shift::math::floating_point_eq(position.y, 0.0));
    CHECK(shift::math::floating_point_eq(position.z, 0.0));
}

TEST_CASE("EcefPosition single double", "[coordinate][EcefPosition]")
{
    constexpr auto position = shift::coordinate::EcefPosition{1.0};
    CHECK(shift::math::floating_point_eq(position.x, 1.0));
    CHECK(shift::math::floating_point_eq(position.y, 1.0));
    CHECK(shift::math::floating_point_eq(position.z, 1.0));
}

TEST_CASE("EcefPosition triple double", "[coordinate][EcefPosition]")
{
    constexpr auto position = shift::coordinate::EcefPosition{1.0, 2.0, 3.0};
    CHECK(shift::math::floating_point_eq(position.x, 1.0));
    CHECK(shift::math::floating_point_eq(position.y, 2.0));
    CHECK(shift::math::floating_point_eq(position.z, 3.0));
}

TEST_CASE("EcefPosition operator==", "[coordinate][EcefPosition]")
{
    CHECK(shift::coordinate::EcefPosition{1.0}
          == shift::coordinate::EcefPosition{1.0});
    CHECK(shift::coordinate::EcefPosition{0.0}
          != shift::coordinate::EcefPosition{1.0});
}

TEST_CASE("EcefPosition operator+", "[coordinate][EcefPosition]")
{
    constexpr auto position = shift::coordinate::EcefPosition{};
    constexpr auto vector = shift::coordinate::EcefVector{1.0, 2.0, 3.0};
    constexpr auto result = position + vector;
    CHECK(shift::math::floating_point_eq(result.x, vector.x));
    CHECK(shift::math::floating_point_eq(result.y, vector.y));
    CHECK(shift::math::floating_point_eq(result.z, vector.z));
}

TEST_CASE("EcefPosition operator+=", "[coordinate][EcefPosition]")
{
    auto position = shift::coordinate::EcefPosition{};
    constexpr auto vector = shift::coordinate::EcefVector{1.0, 2.0, 3.0};
    position += vector;
    CHECK(shift::math::floating_point_eq(position.x, vector.x));
    CHECK(shift::math::floating_point_eq(position.y, vector.y));
    CHECK(shift::math::floating_point_eq(position.z, vector.z));
}

TEST_CASE("EcefPosition operator-", "[coordinate][EcefPosition]")
{
    constexpr auto position = shift::coordinate::EcefPosition{1.0, 2.0, 3.0};

    SECTION("EcefVector")
    {
        constexpr auto vector =
            shift::coordinate::EcefVector{position.x, position.y, position.z};
        CHECK(position - vector == shift::coordinate::EcefPosition{});
    }

    SECTION("EcefPosition")
    {
        constexpr auto vector =
            shift::coordinate::EcefPosition{position.x, position.y, position.z};
        CHECK(position - vector == shift::coordinate::EcefVector{});
    }
}

TEST_CASE("EcefPosition operator-=", "[coordinate][EcefPosition]")
{
    auto position = shift::coordinate::EcefPosition{1.0, 2.0, 3.0};
    const auto vector =
        shift::coordinate::EcefVector{position.x, position.y, position.z};
    position -= vector;
    CHECK(position == shift::coordinate::EcefPosition{});
}
