#include <cmath>

#include "shift/math/Vec3.hpp"

#include <catch2/catch_test_macros.hpp>

#include "shift/math/Utilities.hpp"

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

TEST_CASE("Vec3 zero initialized", "[math][Vec3]")
{
    constexpr auto vec = shift::math::Vec3{};
    CHECK(shift::math::floating_point_eq(vec.x, 0.0));
    CHECK(shift::math::floating_point_eq(vec.y, 0.0));
    CHECK(shift::math::floating_point_eq(vec.z, 0.0));
}

TEST_CASE("Vec3 single double", "[math][Vec3]")
{
    constexpr auto vec = shift::math::Vec3{1.0};
    CHECK(shift::math::floating_point_eq(vec.x, 1.0));
    CHECK(shift::math::floating_point_eq(vec.y, 1.0));
    CHECK(shift::math::floating_point_eq(vec.z, 1.0));
}

TEST_CASE("Vec3 triple double", "[math][Vec3]")
{
    constexpr auto vec = shift::math::Vec3{1.0, 2.0, 3.0};
    CHECK(shift::math::floating_point_eq(vec.x, 1.0));
    CHECK(shift::math::floating_point_eq(vec.y, 2.0));
    CHECK(shift::math::floating_point_eq(vec.z, 3.0));
}

TEST_CASE("Vec3 operator+", "[math][Vec3]")
{
    constexpr auto lhs = shift::math::Vec3{1.0, 2.0, 3.0};
    constexpr auto rhs = lhs;
    CHECK(lhs + rhs == shift::math::Vec3{2.0, 4.0, 6.0});
}

TEST_CASE("Vec3 operator+=", "[math][Vec3]")
{
    auto lhs = shift::math::Vec3{1.0, 2.0, 3.0};
    constexpr auto rhs = shift::math::Vec3{1.0, 2.0, 3.0};
    lhs += rhs;
    CHECK(lhs == shift::math::Vec3{2.0, 4.0, 6.0});
}

TEST_CASE("Vec3 operator-", "[math][Vec3]")
{
    constexpr auto lhs = shift::math::Vec3{1.0, 2.0, 3.0};
    constexpr auto rhs = lhs;
    CHECK(lhs - rhs == shift::math::Vec3{});
}

TEST_CASE("Vec3 operator-=", "[math][Vec3]")
{
    auto lhs = shift::math::Vec3{1.0, 2.0, 3.0};
    constexpr auto rhs = shift::math::Vec3{1.0, 2.0, 3.0};
    lhs -= rhs;
    CHECK(lhs == shift::math::Vec3{});
}

TEST_CASE("Vec3 operator*", "[math][Vec3]")
{
    constexpr auto vec = shift::math::Vec3{1.0, 2.0, 3.0};
    CHECK(vec * 2.0 == shift::math::Vec3{2.0, 4.0, 6.0});
}

TEST_CASE("Vec3 operator*=", "[math][Vec3]")
{
    auto vec = shift::math::Vec3{1.0, 2.0, 3.0};
    vec *= 2.0;
    CHECK(vec == shift::math::Vec3{2.0, 4.0, 6.0});
}

TEST_CASE("Vec3 operator/", "[math][Vec3]")
{
    constexpr auto vec = shift::math::Vec3{2.0, 4.0, 6.0};
    CHECK(vec / 2.0 == shift::math::Vec3{1.0, 2.0, 3.0});

    SECTION("divide by zero")
    {
        CHECK_THROWS(vec / 0.0);
    }
}

TEST_CASE("Vec3 operator/=", "[math][Vec3]")
{
    auto vec = shift::math::Vec3{2.0, 4.0, 6.0};
    vec /= 2.0;
    CHECK(vec == shift::math::Vec3{1.0, 2.0, 3.0});

    SECTION("divide by zero")
    {
        CHECK_THROWS(vec /= 0.0);
    }
}

TEST_CASE("Vec3 magnitude", "[math][Vec3]")
{
    constexpr auto vec = shift::math::Vec3{1.0, 2.0, 3.0};
    CHECK(
        shift::math::floating_point_eq(vec.magnitude(), std::sqrt(14.0), 1e6));
}

TEST_CASE("Vec3 distance", "[math][Vec3]")
{
    constexpr auto lhs = shift::math::Vec3{1.0, 2.0, 3.0};
    constexpr auto rhs = shift::math::Vec3{2.0, 4.0, 6.0};
    CHECK(shift::math::floating_point_eq(shift::math::Vec3::distance(lhs, rhs),
                                         lhs.magnitude()));
}

TEST_CASE("Vec3 dot", "[math][Vec3]")
{
    constexpr auto lhs = shift::math::Vec3{1.0, 2.0, 3.0};
    constexpr auto rhs = shift::math::Vec3{3.0, 4.0, 5.0};
    CHECK(
        shift::math::floating_point_eq(shift::math::Vec3::dot(lhs, rhs), 26.0));
}

TEST_CASE("Vec3 cross", "[math][Vec3]")
{
    constexpr auto lhs = shift::math::Vec3{1.0, 2.0, 3.0};
    constexpr auto rhs = shift::math::Vec3{3.0, 4.0, 5.0};
    CHECK(shift::math::Vec3::cross(lhs, rhs)
          == shift::math::Vec3{-2.0, 4.0, -2.0});
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
