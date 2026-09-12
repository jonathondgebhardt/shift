#include "shift/coordinate/EnuPosition.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "shift/coordinate/EnuVector.hpp"

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
TEST_CASE("EnuPosition zero initialized", "[coordinate][EnuPosition]")
{
    constexpr auto enu = shift::coordinate::EnuPosition{};
    CHECK_THAT(enu.east, Catch::Matchers::WithinRel(0.0));
    CHECK_THAT(enu.north, Catch::Matchers::WithinRel(0.0));
    CHECK_THAT(enu.up, Catch::Matchers::WithinRel(0.0));
}

TEST_CASE("EnuPosition single double", "[coordinate][EnuPosition]")
{
    constexpr auto enu = shift::coordinate::EnuPosition{1.0};
    CHECK_THAT(enu.east, Catch::Matchers::WithinRel(1.0));
    CHECK_THAT(enu.north, Catch::Matchers::WithinRel(1.0));
    CHECK_THAT(enu.up, Catch::Matchers::WithinRel(1.0));
}

TEST_CASE("EnuPosition triple double", "[coordinate][EnuPosition]")
{
    constexpr auto enu = shift::coordinate::EnuPosition{1.0, 2.0, 3.0};
    CHECK_THAT(enu.east, Catch::Matchers::WithinRel(1.0));
    CHECK_THAT(enu.north, Catch::Matchers::WithinRel(2.0));
    CHECK_THAT(enu.up, Catch::Matchers::WithinRel(3.0));
}

TEST_CASE("EnuPosition operator==", "[coordinate][EnuPosition]")
{
    CHECK(shift::coordinate::EnuPosition{1.0, 2.0, 3.0}
          == shift::coordinate::EnuPosition{1.0, 2.0, 3.0});

    CHECK(shift::coordinate::EnuPosition{1.0, 2.0, 3.0}
          != shift::coordinate::EnuPosition{4.0, 2.0, 3.0});

    CHECK(shift::coordinate::EnuPosition{1.0, 2.0, 3.0}
          != shift::coordinate::EnuPosition{1.0, 4.0, 3.0});

    CHECK(shift::coordinate::EnuPosition{1.0, 2.0, 3.0}
          != shift::coordinate::EnuPosition{1.0, 2.0, 4.0});
}

TEST_CASE("EnuPosition operator+", "[coordinate][EnuPosition]")
{
    constexpr auto position = shift::coordinate::EnuPosition{};
    constexpr auto vector = shift::coordinate::EnuVector{1.0, 2.0, 3.0};
    constexpr auto result = position + vector;
    CHECK_THAT(result.east, Catch::Matchers::WithinRel(vector.east));
    CHECK_THAT(result.north, Catch::Matchers::WithinRel(vector.north));
    CHECK_THAT(result.up, Catch::Matchers::WithinRel(vector.up));
}

TEST_CASE("EnuPosition operator+=", "[coordinate][EnuPosition]")
{
    auto position = shift::coordinate::EnuPosition{};
    constexpr auto vector = shift::coordinate::EnuVector{1.0, 2.0, 3.0};
    position += vector;
    CHECK_THAT(position.east, Catch::Matchers::WithinRel(vector.east));
    CHECK_THAT(position.north, Catch::Matchers::WithinRel(vector.north));
    CHECK_THAT(position.up, Catch::Matchers::WithinRel(vector.up));
}

TEST_CASE("EnuPosition operator-", "[coordinate][EnuPosition]")
{
    constexpr auto position = shift::coordinate::EnuPosition{1.0, 2.0, 3.0};

    SECTION("EnuVector")
    {
        constexpr auto vector = shift::coordinate::EnuVector{
            position.east, position.north, position.up};
        constexpr auto result = position - vector;
        CHECK_THAT(result.east, Catch::Matchers::WithinRel(0.0));
        CHECK_THAT(result.north, Catch::Matchers::WithinRel(0.0));
        CHECK_THAT(result.up, Catch::Matchers::WithinRel(0.0));
    }

    SECTION("EnuPosition")
    {
        constexpr auto other_position = position;
        constexpr auto result = position - other_position;
        CHECK_THAT(result.east, Catch::Matchers::WithinRel(0.0));
        CHECK_THAT(result.north, Catch::Matchers::WithinRel(0.0));
        CHECK_THAT(result.up, Catch::Matchers::WithinRel(0.0));
    }
}

TEST_CASE("EnuPosition operator-=", "[coordinate][EnuPosition]")
{
    auto position = shift::coordinate::EnuPosition{1.0, 2.0, 3.0};
    const auto vector = shift::coordinate::EnuVector{
        position.east, position.north, position.up};
    position -= vector;
    CHECK_THAT(position.east, Catch::Matchers::WithinRel(0.0));
    CHECK_THAT(position.north, Catch::Matchers::WithinRel(0.0));
    CHECK_THAT(position.up, Catch::Matchers::WithinRel(0.0));
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
