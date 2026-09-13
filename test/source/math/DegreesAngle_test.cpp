#include "shift/math/DegreesAngle.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

TEST_CASE("DegreesAngle zero initialized", "[math][DegreesAngle]")
{
    constexpr auto angle = shift::math::DegreesAngle{};
    CHECK_THAT(angle.angle(), Catch::Matchers::WithinRel(0.0f));
}

TEST_CASE("DegreesAngle parameterized ctor", "[math][DegreesAngle]")
{
    SECTION("within bounds")
    {
        const auto angle = shift::math::DegreesAngle{1.0f};
        CHECK_THAT(angle.angle(), Catch::Matchers::WithinRel(1.0f));
    }

    SECTION("above bounds")
    {
        const auto angle = shift::math::DegreesAngle{361.0f};
        CHECK_THAT(angle.angle(), Catch::Matchers::WithinRel(1.0f));
    }

    SECTION("below bounds")
    {
        const auto angle = shift::math::DegreesAngle{-1.0f};
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers,
        // readability-magic-numbers)
        CHECK_THAT(angle.angle(), Catch::Matchers::WithinRel(359.0f));
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers,
        // readability-magic-numbers)
    }
}

TEST_CASE("DegreesAngle set_angle", "[math][DegreesAngle]")
{
    SECTION("within bounds")
    {
        auto angle = shift::math::DegreesAngle{};
        angle.set_angle(1.0f);
        CHECK_THAT(angle.angle(), Catch::Matchers::WithinRel(1.0f));
    }

    SECTION("above bounds")
    {
        auto angle = shift::math::DegreesAngle{};
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers,
        // readability-magic-numbers)
        angle.set_angle(361.0f);
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers,
        // readability-magic-numbers)
        CHECK_THAT(angle.angle(), Catch::Matchers::WithinRel(1.0f));
    }

    SECTION("below bounds")
    {
        auto angle = shift::math::DegreesAngle{};
        angle.set_angle(-1.0f);
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers,
        // readability-magic-numbers)
        CHECK_THAT(angle.angle(), Catch::Matchers::WithinRel(359.0f));
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers,
        // readability-magic-numbers)
    }
}

TEST_CASE("DegreesAngle operator+", "[math][DegreesAngle]")
{
    SECTION("within bounds")
    {
        constexpr auto lhs = shift::math::DegreesAngle{};
        const auto rhs = shift::math::DegreesAngle{1.0f};
        const auto result = lhs + rhs;
        CHECK_THAT(result.angle(), Catch::Matchers::WithinRel(1.0f));
    }

    SECTION("above bounds")
    {
        const auto lhs = shift::math::DegreesAngle{359.0f};
        const auto rhs = shift::math::DegreesAngle{1.0f};
        const auto result = lhs + rhs;
        CHECK_THAT(result.angle(), Catch::Matchers::WithinRel(0.0f));
    }
}

TEST_CASE("DegreesAngle operator+=", "[math][DegreesAngle]")
{
    SECTION("within bounds")
    {
        auto lhs = shift::math::DegreesAngle{};
        const auto rhs = shift::math::DegreesAngle{1.0f};
        lhs += rhs;
        CHECK_THAT(lhs.angle(), Catch::Matchers::WithinRel(1.0f));
    }

    SECTION("above bounds")
    {
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers,
        // readability-magic-numbers)
        auto lhs = shift::math::DegreesAngle{359.0f};
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers,
        // readability-magic-numbers)
        const auto rhs = shift::math::DegreesAngle{1.0f};
        lhs += rhs;
        CHECK_THAT(lhs.angle(), Catch::Matchers::WithinRel(0.0f));
    }
}

TEST_CASE("DegreesAngle operator-", "[math][DegreesAngle]")
{
    SECTION("within bounds")
    {
        const auto lhs = shift::math::DegreesAngle{1.0f};
        const auto rhs = shift::math::DegreesAngle{1.0f};
        const auto result = lhs - rhs;
        CHECK_THAT(result.angle(), Catch::Matchers::WithinRel(0.0f));
    }

    SECTION("below bounds")
    {
        constexpr auto lhs = shift::math::DegreesAngle{};
        const auto rhs = shift::math::DegreesAngle{1.0f};
        const auto result = lhs - rhs;
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers,
        // readability-magic-numbers)
        CHECK_THAT(result.angle(), Catch::Matchers::WithinRel(359.0f));
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers,
        // readability-magic-numbers)
    }
}

TEST_CASE("DegreesAngle operator-=", "[math][DegreesAngle]")
{
    SECTION("within bounds")
    {
        auto lhs = shift::math::DegreesAngle{1.0f};
        const auto rhs = shift::math::DegreesAngle{1.0f};
        lhs -= rhs;
        CHECK_THAT(lhs.angle(), Catch::Matchers::WithinRel(0.0f));
    }

    SECTION("above bounds")
    {
        auto lhs = shift::math::DegreesAngle{};
        const auto rhs = shift::math::DegreesAngle{1.0f};
        lhs -= rhs;
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers,
        // readability-magic-numbers)
        CHECK_THAT(lhs.angle(), Catch::Matchers::WithinRel(359.0f));
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers,
        // readability-magic-numbers)
    }
}

TEST_CASE("DegreesAngle to_string", "[math][DegreesAngle]")
{
    const auto angle = shift::math::DegreesAngle{1.0};
    CHECK_THAT(angle.to_string(), Catch::Matchers::StartsWith("1.0"));
}
