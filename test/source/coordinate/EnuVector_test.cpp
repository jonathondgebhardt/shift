#include <cmath>

#include "shift/coordinate/EnuVector.hpp"

#include <catch2/catch_test_macros.hpp>

#include "shift/math/Utilities.hpp"

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

TEST_CASE("EnuVector zero initialized", "[coordinate][EnuVector]")
{
    constexpr auto vec = shift::coordinate::EnuVector{};
    CHECK(shift::math::floating_point_eq(vec.east, 0.0));
    CHECK(shift::math::floating_point_eq(vec.north, 0.0));
    CHECK(shift::math::floating_point_eq(vec.up, 0.0));
}

TEST_CASE("EnuVector single double", "[coordinate][EnuVector]")
{
    constexpr auto vec = shift::coordinate::EnuVector{1.0};
    CHECK(shift::math::floating_point_eq(vec.east, 1.0));
    CHECK(shift::math::floating_point_eq(vec.north, 1.0));
    CHECK(shift::math::floating_point_eq(vec.up, 1.0));
}

TEST_CASE("EnuVector triple double", "[coordinate][EnuVector]")
{
    constexpr auto vec = shift::coordinate::EnuVector{1.0, 2.0, 3.0};
    CHECK(shift::math::floating_point_eq(vec.east, 1.0));
    CHECK(shift::math::floating_point_eq(vec.north, 2.0));
    CHECK(shift::math::floating_point_eq(vec.up, 3.0));
}

TEST_CASE("EnuVector operator==", "[coordinate][EnuVector]")
{
    CHECK(shift::coordinate::EnuVector{1.0}
          == shift::coordinate::EnuVector{1.0});
    CHECK(shift::coordinate::EnuVector{0.0}
          != shift::coordinate::EnuVector{1.0});
}

TEST_CASE("EnuVector operator+", "[coordinate][EnuVector]")
{
    constexpr auto lhs = shift::coordinate::EnuVector{1.0, 2.0, 3.0};
    constexpr auto rhs = lhs;
    CHECK(lhs + rhs == shift::coordinate::EnuVector{2.0, 4.0, 6.0});
}

TEST_CASE("EnuVector operator+=", "[coordinate][EnuVector]")
{
    auto lhs = shift::coordinate::EnuVector{1.0, 2.0, 3.0};
    constexpr auto rhs = shift::coordinate::EnuVector{1.0, 2.0, 3.0};
    lhs += rhs;
    CHECK(lhs == shift::coordinate::EnuVector{2.0, 4.0, 6.0});
}

TEST_CASE("EnuVector operator-", "[coordinate][EnuVector]")
{
    constexpr auto lhs = shift::coordinate::EnuVector{1.0, 2.0, 3.0};
    constexpr auto rhs = lhs;
    CHECK(lhs - rhs == shift::coordinate::EnuVector{});
}

TEST_CASE("EnuVector operator-=", "[coordinate][EnuVector]")
{
    auto lhs = shift::coordinate::EnuVector{1.0, 2.0, 3.0};
    constexpr auto rhs = shift::coordinate::EnuVector{1.0, 2.0, 3.0};
    lhs -= rhs;
    CHECK(lhs == shift::coordinate::EnuVector{});
}

TEST_CASE("EnuVector operator*", "[coordinate][EnuVector]")
{
    constexpr auto vec = shift::coordinate::EnuVector{1.0, 2.0, 3.0};
    CHECK(vec * 2.0 == shift::coordinate::EnuVector{2.0, 4.0, 6.0});
}

TEST_CASE("EnuVector operator*=", "[coordinate][EnuVector]")
{
    auto vec = shift::coordinate::EnuVector{1.0, 2.0, 3.0};
    vec *= 2.0;
    CHECK(vec == shift::coordinate::EnuVector{2.0, 4.0, 6.0});
}

TEST_CASE("EnuVector operator/", "[coordinate][EnuVector]")
{
    constexpr auto vec = shift::coordinate::EnuVector{2.0, 4.0, 6.0};
    CHECK(vec / 2.0 == shift::coordinate::EnuVector{1.0, 2.0, 3.0});

    SECTION("divide by zero")
    {
        CHECK_THROWS(vec / 0.0);
    }
}

TEST_CASE("EnuVector operator/=", "[coordinate][EnuVector]")
{
    auto vec = shift::coordinate::EnuVector{2.0, 4.0, 6.0};
    vec /= 2.0;
    CHECK(vec == shift::coordinate::EnuVector{1.0, 2.0, 3.0});

    SECTION("divide by zero")
    {
        CHECK_THROWS(vec /= 0.0);
    }
}

TEST_CASE("EnuVector unary -", "[coordinate][EnuVector]")
{
    constexpr auto vec = shift::coordinate::EnuVector{1.0, 2.0, 3.0};
    CHECK(-vec == shift::coordinate::EnuVector{-1.0, -2.0, -3.0});
}

TEST_CASE("EnuVector magnitude", "[coordinate][EnuVector]")
{
    constexpr auto vec = shift::coordinate::EnuVector{1.0, 2.0, 3.0};
    CHECK(
        shift::math::floating_point_eq(vec.magnitude(), std::sqrt(14.0), 1e-6));
}

TEST_CASE("EnuVector distance", "[coordinate][EnuVector]")
{
    constexpr auto lhs = shift::coordinate::EnuVector{1.0, 2.0, 3.0};
    constexpr auto rhs = shift::coordinate::EnuVector{2.0, 4.0, 6.0};
    CHECK(shift::math::floating_point_eq(
        shift::coordinate::EnuVector::distance(lhs, rhs), lhs.magnitude()));
}

TEST_CASE("EnuVector dot", "[coordinate][EnuVector]")
{
    constexpr auto lhs = shift::coordinate::EnuVector{1.0, 2.0, 3.0};
    constexpr auto rhs = shift::coordinate::EnuVector{3.0, 4.0, 5.0};
    CHECK(shift::math::floating_point_eq(
        shift::coordinate::EnuVector::dot(lhs, rhs), 26.0));
}

TEST_CASE("EnuVector cross", "[coordinate][EnuVector]")
{
    constexpr auto lhs = shift::coordinate::EnuVector{1.0, 2.0, 3.0};
    constexpr auto rhs = shift::coordinate::EnuVector{3.0, 4.0, 5.0};
    CHECK(shift::coordinate::EnuVector::cross(lhs, rhs)
          == shift::coordinate::EnuVector{-2.0, 4.0, -2.0});
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
