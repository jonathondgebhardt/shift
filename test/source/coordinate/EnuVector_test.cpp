#include <cmath>

#include "shift/coordinate/EnuVector.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

TEST_CASE("EnuVector zero initialized", "[coordinate][EnuVector]")
{
    constexpr auto vec = shift::coordinate::EnuVector{};
    CHECK_THAT(vec.east, Catch::Matchers::WithinRel(0.0));
    CHECK_THAT(vec.north, Catch::Matchers::WithinRel(0.0));
    CHECK_THAT(vec.up, Catch::Matchers::WithinRel(0.0));
}

TEST_CASE("EnuVector single double", "[coordinate][EnuVector]")
{
    constexpr auto vec = shift::coordinate::EnuVector{1.0};
    CHECK_THAT(vec.east, Catch::Matchers::WithinRel(1.0));
    CHECK_THAT(vec.north, Catch::Matchers::WithinRel(1.0));
    CHECK_THAT(vec.up, Catch::Matchers::WithinRel(1.0));
}

TEST_CASE("EnuVector triple double", "[coordinate][EnuVector]")
{
    constexpr auto vec = shift::coordinate::EnuVector{1.0, 2.0, 3.0};
    CHECK_THAT(vec.east, Catch::Matchers::WithinRel(1.0));
    CHECK_THAT(vec.north, Catch::Matchers::WithinRel(2.0));
    CHECK_THAT(vec.up, Catch::Matchers::WithinRel(3.0));
}

TEST_CASE("EnuVector operator==", "[coordinate][EnuVector]")
{
    CHECK(shift::coordinate::EnuVector{1.0, 2.0, 3.0}
          == shift::coordinate::EnuVector{1.0, 2.0, 3.0});

    CHECK(shift::coordinate::EnuVector{1.0, 2.0, 3.0}
          != shift::coordinate::EnuVector{4.0, 2.0, 3.0});

    CHECK(shift::coordinate::EnuVector{1.0, 2.0, 3.0}
          != shift::coordinate::EnuVector{1.0, 4.0, 3.0});

    CHECK(shift::coordinate::EnuVector{1.0, 2.0, 3.0}
          != shift::coordinate::EnuVector{1.0, 2.0, 4.0});
}

TEST_CASE("EnuVector operator+", "[coordinate][EnuVector]")
{
    constexpr auto lhs = shift::coordinate::EnuVector{1.0, 2.0, 3.0};
    constexpr auto rhs = lhs;
    constexpr auto result = lhs + rhs;
    CHECK_THAT(result.east, Catch::Matchers::WithinRel(2.0));
    CHECK_THAT(result.north, Catch::Matchers::WithinRel(4.0));
    CHECK_THAT(result.up, Catch::Matchers::WithinRel(6.0));
}

TEST_CASE("EnuVector operator+=", "[coordinate][EnuVector]")
{
    auto lhs = shift::coordinate::EnuVector{1.0, 2.0, 3.0};
    constexpr auto rhs = shift::coordinate::EnuVector{1.0, 2.0, 3.0};
    lhs += rhs;
    CHECK_THAT(lhs.east, Catch::Matchers::WithinRel(2.0));
    CHECK_THAT(lhs.north, Catch::Matchers::WithinRel(4.0));
    CHECK_THAT(lhs.up, Catch::Matchers::WithinRel(6.0));
}

TEST_CASE("EnuVector operator-", "[coordinate][EnuVector]")
{
    constexpr auto lhs = shift::coordinate::EnuVector{1.0, 2.0, 3.0};
    constexpr auto rhs = lhs;
    constexpr auto result = lhs - rhs;
    CHECK_THAT(result.east, Catch::Matchers::WithinRel(0.0));
    CHECK_THAT(result.north, Catch::Matchers::WithinRel(0.0));
    CHECK_THAT(result.up, Catch::Matchers::WithinRel(0.0));
}

TEST_CASE("EnuVector operator-=", "[coordinate][EnuVector]")
{
    auto lhs = shift::coordinate::EnuVector{1.0, 2.0, 3.0};
    constexpr auto rhs = shift::coordinate::EnuVector{1.0, 2.0, 3.0};
    lhs -= rhs;
    CHECK_THAT(lhs.east, Catch::Matchers::WithinRel(0.0));
    CHECK_THAT(lhs.north, Catch::Matchers::WithinRel(0.0));
    CHECK_THAT(lhs.up, Catch::Matchers::WithinRel(0.0));
}

TEST_CASE("EnuVector operator*", "[coordinate][EnuVector]")
{
    constexpr auto vec = shift::coordinate::EnuVector{1.0, 2.0, 3.0};
    constexpr auto result = vec * 2.0;
    CHECK_THAT(result.east, Catch::Matchers::WithinRel(2.0));
    CHECK_THAT(result.north, Catch::Matchers::WithinRel(4.0));
    CHECK_THAT(result.up, Catch::Matchers::WithinRel(6.0));
}

TEST_CASE("EnuVector operator*=", "[coordinate][EnuVector]")
{
    auto vec = shift::coordinate::EnuVector{1.0, 2.0, 3.0};
    vec *= 2.0;
    CHECK_THAT(vec.east, Catch::Matchers::WithinRel(2.0));
    CHECK_THAT(vec.north, Catch::Matchers::WithinRel(4.0));
    CHECK_THAT(vec.up, Catch::Matchers::WithinRel(6.0));
}

TEST_CASE("EnuVector operator/", "[coordinate][EnuVector]")
{
    constexpr auto vec = shift::coordinate::EnuVector{2.0, 4.0, 6.0};
    const auto result = vec / 2.0;
    CHECK_THAT(result.east, Catch::Matchers::WithinRel(1.0));
    CHECK_THAT(result.north, Catch::Matchers::WithinRel(2.0));
    CHECK_THAT(result.up, Catch::Matchers::WithinRel(3.0));

    SECTION("divide by zero")
    {
        CHECK_THROWS(vec / 0.0);
    }
}

TEST_CASE("EnuVector operator/=", "[coordinate][EnuVector]")
{
    auto vec = shift::coordinate::EnuVector{2.0, 4.0, 6.0};
    vec /= 2.0;
    CHECK_THAT(vec.east, Catch::Matchers::WithinRel(1.0));
    CHECK_THAT(vec.north, Catch::Matchers::WithinRel(2.0));
    CHECK_THAT(vec.up, Catch::Matchers::WithinRel(3.0));

    SECTION("divide by zero")
    {
        CHECK_THROWS(vec /= 0.0);
    }
}

TEST_CASE("EnuVector unary -", "[coordinate][EnuVector]")
{
    constexpr auto vec = shift::coordinate::EnuVector{1.0, 2.0, 3.0};
    constexpr auto negated = -vec;
    CHECK_THAT(negated.east, Catch::Matchers::WithinRel(-1.0));
    CHECK_THAT(negated.north, Catch::Matchers::WithinRel(-2.0));
    CHECK_THAT(negated.up, Catch::Matchers::WithinRel(-3.0));
}

TEST_CASE("EnuVector magnitude", "[coordinate][EnuVector]")
{
    constexpr auto vec = shift::coordinate::EnuVector{1.0, 2.0, 3.0};
    CHECK_THAT(vec.magnitude(),
               Catch::Matchers::WithinRel(std::sqrt(14.0), 1e-6));
}

TEST_CASE("EnuVector distance", "[coordinate][EnuVector]")
{
    constexpr auto lhs = shift::coordinate::EnuVector{1.0, 2.0, 3.0};
    constexpr auto rhs = shift::coordinate::EnuVector{2.0, 4.0, 6.0};
    CHECK_THAT(shift::coordinate::EnuVector::distance(lhs, rhs),
               Catch::Matchers::WithinRel(lhs.magnitude()));
}

TEST_CASE("EnuVector dot", "[coordinate][EnuVector]")
{
    constexpr auto lhs = shift::coordinate::EnuVector{1.0, 2.0, 3.0};
    constexpr auto rhs = shift::coordinate::EnuVector{3.0, 4.0, 5.0};
    CHECK_THAT(shift::coordinate::EnuVector::dot(lhs, rhs),
               Catch::Matchers::WithinRel(26.0));
}

TEST_CASE("EnuVector cross", "[coordinate][EnuVector]")
{
    constexpr auto lhs = shift::coordinate::EnuVector{1.0, 2.0, 3.0};
    constexpr auto rhs = shift::coordinate::EnuVector{3.0, 4.0, 5.0};

    constexpr auto cross = shift::coordinate::EnuVector::cross(lhs, rhs);
    CHECK_THAT(cross.east, Catch::Matchers::WithinRel(-2.0));
    CHECK_THAT(cross.north, Catch::Matchers::WithinRel(4.0));
    CHECK_THAT(cross.up, Catch::Matchers::WithinRel(-2.0));
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
