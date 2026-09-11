#include <cmath>

#include "shift/coordinate/EcefVector.hpp"

#include <catch2/catch_test_macros.hpp>

#include "shift/math/Utilities.hpp"

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

TEST_CASE("EcefVector zero initialized", "[coordinate][EcefVector]")
{
    constexpr auto vec = shift::coordinate::EcefVector{};
    CHECK(shift::math::floating_point_eq(vec.x, 0.0));
    CHECK(shift::math::floating_point_eq(vec.y, 0.0));
    CHECK(shift::math::floating_point_eq(vec.z, 0.0));
}

TEST_CASE("EcefVector single double", "[coordinate][EcefVector]")
{
    constexpr auto vec = shift::coordinate::EcefVector{1.0};
    CHECK(shift::math::floating_point_eq(vec.x, 1.0));
    CHECK(shift::math::floating_point_eq(vec.y, 1.0));
    CHECK(shift::math::floating_point_eq(vec.z, 1.0));
}

TEST_CASE("EcefVector triple double", "[coordinate][EcefVector]")
{
    constexpr auto vec = shift::coordinate::EcefVector{1.0, 2.0, 3.0};
    CHECK(shift::math::floating_point_eq(vec.x, 1.0));
    CHECK(shift::math::floating_point_eq(vec.y, 2.0));
    CHECK(shift::math::floating_point_eq(vec.z, 3.0));
}

TEST_CASE("EcefVector operator+", "[coordinate][EcefVector]")
{
    constexpr auto lhs = shift::coordinate::EcefVector{1.0, 2.0, 3.0};
    constexpr auto rhs = lhs;
    CHECK(lhs + rhs == shift::coordinate::EcefVector{2.0, 4.0, 6.0});
}

TEST_CASE("EcefVector operator+=", "[coordinate][EcefVector]")
{
    auto lhs = shift::coordinate::EcefVector{1.0, 2.0, 3.0};
    constexpr auto rhs = shift::coordinate::EcefVector{1.0, 2.0, 3.0};
    lhs += rhs;
    CHECK(lhs == shift::coordinate::EcefVector{2.0, 4.0, 6.0});
}

TEST_CASE("EcefVector operator-", "[coordinate][EcefVector]")
{
    constexpr auto lhs = shift::coordinate::EcefVector{1.0, 2.0, 3.0};
    constexpr auto rhs = lhs;
    CHECK(lhs - rhs == shift::coordinate::EcefVector{});
}

TEST_CASE("EcefVector operator-=", "[coordinate][EcefVector]")
{
    auto lhs = shift::coordinate::EcefVector{1.0, 2.0, 3.0};
    constexpr auto rhs = shift::coordinate::EcefVector{1.0, 2.0, 3.0};
    lhs -= rhs;
    CHECK(lhs == shift::coordinate::EcefVector{});
}

TEST_CASE("EcefVector operator*", "[coordinate][EcefVector]")
{
    constexpr auto vec = shift::coordinate::EcefVector{1.0, 2.0, 3.0};
    CHECK(vec * 2.0 == shift::coordinate::EcefVector{2.0, 4.0, 6.0});
}

TEST_CASE("EcefVector operator*=", "[coordinate][EcefVector]")
{
    auto vec = shift::coordinate::EcefVector{1.0, 2.0, 3.0};
    vec *= 2.0;
    CHECK(vec == shift::coordinate::EcefVector{2.0, 4.0, 6.0});
}

TEST_CASE("EcefVector operator/", "[coordinate][EcefVector]")
{
    constexpr auto vec = shift::coordinate::EcefVector{2.0, 4.0, 6.0};
    CHECK(vec / 2.0 == shift::coordinate::EcefVector{1.0, 2.0, 3.0});

    SECTION("divide by zero")
    {
        CHECK_THROWS(vec / 0.0);
    }
}

TEST_CASE("EcefVector operator/=", "[coordinate][EcefVector]")
{
    auto vec = shift::coordinate::EcefVector{2.0, 4.0, 6.0};
    vec /= 2.0;
    CHECK(vec == shift::coordinate::EcefVector{1.0, 2.0, 3.0});

    SECTION("divide by zero")
    {
        CHECK_THROWS(vec /= 0.0);
    }
}

TEST_CASE("EcefVector unary -", "[coordinate][EcefVector]")
{
    constexpr auto vec = shift::coordinate::EcefVector{1.0, 2.0, 3.0};
    CHECK(-vec == shift::coordinate::EcefVector{-1.0, -2.0, -3.0});
}

TEST_CASE("EcefVector magnitude", "[coordinate][EcefVector]")
{
    constexpr auto vec = shift::coordinate::EcefVector{1.0, 2.0, 3.0};
    CHECK(
        shift::math::floating_point_eq(vec.magnitude(), std::sqrt(14.0), 1e-6));
}

TEST_CASE("EcefVector distance", "[coordinate][EcefVector]")
{
    constexpr auto lhs = shift::coordinate::EcefVector{1.0, 2.0, 3.0};
    constexpr auto rhs = shift::coordinate::EcefVector{2.0, 4.0, 6.0};
    CHECK(shift::math::floating_point_eq(
        shift::coordinate::EcefVector::distance(lhs, rhs), lhs.magnitude()));
}

TEST_CASE("EcefVector dot", "[coordinate][EcefVector]")
{
    constexpr auto lhs = shift::coordinate::EcefVector{1.0, 2.0, 3.0};
    constexpr auto rhs = shift::coordinate::EcefVector{3.0, 4.0, 5.0};
    CHECK(shift::math::floating_point_eq(
        shift::coordinate::EcefVector::dot(lhs, rhs), 26.0));
}

TEST_CASE("EcefVector cross", "[coordinate][EcefVector]")
{
    constexpr auto lhs = shift::coordinate::EcefVector{1.0, 2.0, 3.0};
    constexpr auto rhs = shift::coordinate::EcefVector{3.0, 4.0, 5.0};
    CHECK(shift::coordinate::EcefVector::cross(lhs, rhs)
          == shift::coordinate::EcefVector{-2.0, 4.0, -2.0});
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
