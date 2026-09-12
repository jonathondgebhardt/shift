#include <cmath>

#include "shift/math/Vec3.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

TEST_CASE("Vec3 zero initialized", "[math][Vec3]")
{
    constexpr auto vec = shift::math::Vec3{};
    CHECK_THAT(vec.x, Catch::Matchers::WithinRel(0.0));
    CHECK_THAT(vec.y, Catch::Matchers::WithinRel(0.0));
    CHECK_THAT(vec.z, Catch::Matchers::WithinRel(0.0));
}

TEST_CASE("Vec3 single double", "[math][Vec3]")
{
    constexpr auto vec = shift::math::Vec3{1.0};
    CHECK_THAT(vec.x, Catch::Matchers::WithinRel(1.0));
    CHECK_THAT(vec.y, Catch::Matchers::WithinRel(1.0));
    CHECK_THAT(vec.z, Catch::Matchers::WithinRel(1.0));
}

TEST_CASE("Vec3 triple double", "[math][Vec3]")
{
    constexpr auto vec = shift::math::Vec3{1.0, 2.0, 3.0};
    CHECK_THAT(vec.x, Catch::Matchers::WithinRel(1.0));
    CHECK_THAT(vec.y, Catch::Matchers::WithinRel(2.0));
    CHECK_THAT(vec.z, Catch::Matchers::WithinRel(3.0));
}

TEST_CASE("Vec3 operator==", "[math][Vec3]")
{
    CHECK(shift::math::Vec3{1.0, 2.0, 3.0} == shift::math::Vec3{1.0, 2.0, 3.0});
    CHECK(shift::math::Vec3{1.0, 2.0, 3.0} != shift::math::Vec3{4.0, 2.0, 3.0});
    CHECK(shift::math::Vec3{1.0, 2.0, 3.0} != shift::math::Vec3{1.0, 4.0, 3.0});
    CHECK(shift::math::Vec3{1.0, 2.0, 3.0} != shift::math::Vec3{1.0, 2.0, 4.0});
}

TEST_CASE("Vec3 operator+", "[math][Vec3]")
{
    constexpr auto lhs = shift::math::Vec3{1.0, 2.0, 3.0};
    constexpr auto rhs = lhs;
    constexpr auto result = lhs + rhs;
    CHECK_THAT(result.x, Catch::Matchers::WithinRel(2.0));
    CHECK_THAT(result.y, Catch::Matchers::WithinRel(4.0));
    CHECK_THAT(result.z, Catch::Matchers::WithinRel(6.0));
}

TEST_CASE("Vec3 operator+=", "[math][Vec3]")
{
    auto lhs = shift::math::Vec3{1.0, 2.0, 3.0};
    constexpr auto rhs = shift::math::Vec3{1.0, 2.0, 3.0};
    lhs += rhs;
    CHECK_THAT(lhs.x, Catch::Matchers::WithinRel(2.0));
    CHECK_THAT(lhs.y, Catch::Matchers::WithinRel(4.0));
    CHECK_THAT(lhs.z, Catch::Matchers::WithinRel(6.0));
}

TEST_CASE("Vec3 operator-", "[math][Vec3]")
{
    constexpr auto lhs = shift::math::Vec3{1.0, 2.0, 3.0};
    constexpr auto rhs = lhs;
    const auto result = lhs - rhs;
    CHECK_THAT(result.x, Catch::Matchers::WithinRel(0.0));
    CHECK_THAT(result.y, Catch::Matchers::WithinRel(0.0));
    CHECK_THAT(result.z, Catch::Matchers::WithinRel(0.0));
}

TEST_CASE("Vec3 operator-=", "[math][Vec3]")
{
    auto lhs = shift::math::Vec3{1.0, 2.0, 3.0};
    constexpr auto rhs = shift::math::Vec3{1.0, 2.0, 3.0};
    lhs -= rhs;
    CHECK_THAT(lhs.x, Catch::Matchers::WithinRel(0.0));
    CHECK_THAT(lhs.y, Catch::Matchers::WithinRel(0.0));
    CHECK_THAT(lhs.z, Catch::Matchers::WithinRel(0.0));
}

TEST_CASE("Vec3 operator*", "[math][Vec3]")
{
    constexpr auto vec = shift::math::Vec3{1.0, 2.0, 3.0};
    constexpr auto result = vec * 2.0;
    CHECK_THAT(result.x, Catch::Matchers::WithinRel(2.0));
    CHECK_THAT(result.y, Catch::Matchers::WithinRel(4.0));
    CHECK_THAT(result.z, Catch::Matchers::WithinRel(6.0));
}

TEST_CASE("Vec3 operator*=", "[math][Vec3]")
{
    auto vec = shift::math::Vec3{1.0, 2.0, 3.0};
    vec *= 2.0;
    CHECK_THAT(vec.x, Catch::Matchers::WithinRel(2.0));
    CHECK_THAT(vec.y, Catch::Matchers::WithinRel(4.0));
    CHECK_THAT(vec.z, Catch::Matchers::WithinRel(6.0));
}

TEST_CASE("Vec3 operator/", "[math][Vec3]")
{
    constexpr auto vec = shift::math::Vec3{2.0, 4.0, 6.0};
    constexpr auto result = vec / 2.0;
    CHECK_THAT(result.x, Catch::Matchers::WithinRel(1.0));
    CHECK_THAT(result.y, Catch::Matchers::WithinRel(2.0));
    CHECK_THAT(result.z, Catch::Matchers::WithinRel(3.0));

    SECTION("divide by zero")
    {
        CHECK_THROWS(vec / 0.0);
    }
}

TEST_CASE("Vec3 operator/=", "[math][Vec3]")
{
    auto vec = shift::math::Vec3{2.0, 4.0, 6.0};
    vec /= 2.0;
    CHECK_THAT(vec.x, Catch::Matchers::WithinRel(1.0));
    CHECK_THAT(vec.y, Catch::Matchers::WithinRel(2.0));
    CHECK_THAT(vec.z, Catch::Matchers::WithinRel(3.0));

    SECTION("divide by zero")
    {
        CHECK_THROWS(vec /= 0.0);
    }
}

TEST_CASE("Vec3 magnitude", "[math][Vec3]")
{
    constexpr auto vec = shift::math::Vec3{1.0, 2.0, 3.0};
    CHECK_THAT(vec.magnitude(),
               Catch::Matchers::WithinRel(std::sqrt(14.0), 1e-6));
}

TEST_CASE("Vec3 distance", "[math][Vec3]")
{
    constexpr auto lhs = shift::math::Vec3{1.0, 2.0, 3.0};
    constexpr auto rhs = shift::math::Vec3{2.0, 4.0, 6.0};
    CHECK_THAT(shift::math::Vec3::distance(lhs, rhs),
               Catch::Matchers::WithinRel(lhs.magnitude()));
}

TEST_CASE("Vec3 dot", "[math][Vec3]")
{
    constexpr auto lhs = shift::math::Vec3{1.0, 2.0, 3.0};
    constexpr auto rhs = shift::math::Vec3{3.0, 4.0, 5.0};
    CHECK_THAT(shift::math::Vec3::dot(lhs, rhs),
               Catch::Matchers::WithinRel(26.0));
}

TEST_CASE("Vec3 cross", "[math][Vec3]")
{
    constexpr auto lhs = shift::math::Vec3{1.0, 2.0, 3.0};
    constexpr auto rhs = shift::math::Vec3{3.0, 4.0, 5.0};

    constexpr auto cross = shift::math::Vec3::cross(lhs, rhs);
    CHECK_THAT(cross.x, Catch::Matchers::WithinRel(-2.0));
    CHECK_THAT(cross.y, Catch::Matchers::WithinRel(4.0));
    CHECK_THAT(cross.z, Catch::Matchers::WithinRel(-2.0));
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
