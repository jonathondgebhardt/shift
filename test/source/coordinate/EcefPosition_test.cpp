#include "shift/coordinate/EcefPosition.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "shift/coordinate/EcefVector.hpp"

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
TEST_CASE("EcefPosition zero initialized", "[coordinate][EcefPosition]")
{
    constexpr auto position = shift::coordinate::EcefPosition{};
    CHECK_THAT(position.x, Catch::Matchers::WithinRel(0.0));
    CHECK_THAT(position.y, Catch::Matchers::WithinRel(0.0));
    CHECK_THAT(position.z, Catch::Matchers::WithinRel(0.0));
}

TEST_CASE("EcefPosition single double", "[coordinate][EcefPosition]")
{
    constexpr auto position = shift::coordinate::EcefPosition{1.0};
    CHECK_THAT(position.x, Catch::Matchers::WithinRel(1.0));
    CHECK_THAT(position.y, Catch::Matchers::WithinRel(1.0));
    CHECK_THAT(position.z, Catch::Matchers::WithinRel(1.0));
}

TEST_CASE("EcefPosition triple double", "[coordinate][EcefPosition]")
{
    constexpr auto position = shift::coordinate::EcefPosition{1.0, 2.0, 3.0};
    CHECK_THAT(position.x, Catch::Matchers::WithinRel(1.0));
    CHECK_THAT(position.y, Catch::Matchers::WithinRel(2.0));
    CHECK_THAT(position.z, Catch::Matchers::WithinRel(3.0));
}

TEST_CASE("EcefPosition operator==", "[coordinate][EcefPosition]")
{
    CHECK(shift::coordinate::EcefPosition{1.0, 2.0, 3.0}
          == shift::coordinate::EcefPosition{1.0, 2.0, 3.0});

    CHECK(shift::coordinate::EcefPosition{1.0, 2.0, 3.0}
          != shift::coordinate::EcefPosition{4.0, 2.0, 3.0});

    CHECK(shift::coordinate::EcefPosition{1.0, 2.0, 3.0}
          != shift::coordinate::EcefPosition{1.0, 4.0, 3.0});

    CHECK(shift::coordinate::EcefPosition{1.0, 2.0, 3.0}
          != shift::coordinate::EcefPosition{1.0, 2.0, 4.0});
}

TEST_CASE("EcefPosition operator+", "[coordinate][EcefPosition]")
{
    constexpr auto position = shift::coordinate::EcefPosition{};
    constexpr auto vector = shift::coordinate::EcefVector{1.0, 2.0, 3.0};
    constexpr auto result = position + vector;
    CHECK_THAT(result.x, Catch::Matchers::WithinRel(vector.x));
    CHECK_THAT(result.y, Catch::Matchers::WithinRel(vector.y));
    CHECK_THAT(result.z, Catch::Matchers::WithinRel(vector.z));
}

TEST_CASE("EcefPosition operator+=", "[coordinate][EcefPosition]")
{
    auto position = shift::coordinate::EcefPosition{};
    constexpr auto vector = shift::coordinate::EcefVector{1.0, 2.0, 3.0};
    position += vector;
    CHECK_THAT(position.x, Catch::Matchers::WithinRel(vector.x));
    CHECK_THAT(position.y, Catch::Matchers::WithinRel(vector.y));
    CHECK_THAT(position.z, Catch::Matchers::WithinRel(vector.z));
}

TEST_CASE("EcefPosition operator-", "[coordinate][EcefPosition]")
{
    constexpr auto position = shift::coordinate::EcefPosition{1.0, 2.0, 3.0};

    SECTION("EcefVector")
    {
        constexpr auto vector =
            shift::coordinate::EcefVector{position.x, position.y, position.z};

        constexpr auto result = position - vector;
        CHECK_THAT(result.x, Catch::Matchers::WithinRel(0.0));
        CHECK_THAT(result.y, Catch::Matchers::WithinRel(0.0));
        CHECK_THAT(result.z, Catch::Matchers::WithinRel(0.0));
    }

    SECTION("EcefPosition")
    {
        constexpr auto other_position = position;
        constexpr auto result = position - other_position;
        CHECK_THAT(result.x, Catch::Matchers::WithinRel(0.0));
        CHECK_THAT(result.y, Catch::Matchers::WithinRel(0.0));
        CHECK_THAT(result.z, Catch::Matchers::WithinRel(0.0));
    }
}

TEST_CASE("EcefPosition operator-=", "[coordinate][EcefPosition]")
{
    auto position = shift::coordinate::EcefPosition{1.0, 2.0, 3.0};
    const auto vector =
        shift::coordinate::EcefVector{position.x, position.y, position.z};
    position -= vector;
    CHECK_THAT(position.x, Catch::Matchers::WithinRel(0.0));
    CHECK_THAT(position.y, Catch::Matchers::WithinRel(0.0));
    CHECK_THAT(position.z, Catch::Matchers::WithinRel(0.0));
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
