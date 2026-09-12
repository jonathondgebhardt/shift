#include <cmath>

#include "shift/coordinate/EcefVector.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

TEST_CASE("EcefVector zero initialized", "[coordinate][EcefVector]")
{
    constexpr auto vec = shift::coordinate::EcefVector{};
    CHECK_THAT(vec.x, Catch::Matchers::WithinRel(0.0));
    CHECK_THAT(vec.y, Catch::Matchers::WithinRel(0.0));
    CHECK_THAT(vec.z, Catch::Matchers::WithinRel(0.0));
}

TEST_CASE("EcefVector single double", "[coordinate][EcefVector]")
{
    constexpr auto vec = shift::coordinate::EcefVector{1.0};
    CHECK_THAT(vec.x, Catch::Matchers::WithinRel(1.0));
    CHECK_THAT(vec.y, Catch::Matchers::WithinRel(1.0));
    CHECK_THAT(vec.z, Catch::Matchers::WithinRel(1.0));
}

TEST_CASE("EcefVector triple double", "[coordinate][EcefVector]")
{
    constexpr auto vec = shift::coordinate::EcefVector{1.0, 2.0, 3.0};
    CHECK_THAT(vec.x, Catch::Matchers::WithinRel(1.0));
    CHECK_THAT(vec.y, Catch::Matchers::WithinRel(2.0));
    CHECK_THAT(vec.z, Catch::Matchers::WithinRel(3.0));
}

TEST_CASE("EcefVector operator==", "[coordinate][EcefVector]")
{
    CHECK(shift::coordinate::EcefVector{1.0, 2.0, 3.0}
          == shift::coordinate::EcefVector{1.0, 2.0, 3.0});

    CHECK(shift::coordinate::EcefVector{1.0, 2.0, 3.0}
          != shift::coordinate::EcefVector{4.0, 2.0, 3.0});

    CHECK(shift::coordinate::EcefVector{1.0, 2.0, 3.0}
          != shift::coordinate::EcefVector{1.0, 4.0, 3.0});

    CHECK(shift::coordinate::EcefVector{1.0, 2.0, 3.0}
          != shift::coordinate::EcefVector{1.0, 2.0, 4.0});
}

TEST_CASE("EcefVector operator+", "[coordinate][EcefVector]")
{
    constexpr auto lhs = shift::coordinate::EcefVector{1.0, 2.0, 3.0};
    constexpr auto rhs = lhs;

    constexpr auto result = lhs + rhs;
    CHECK_THAT(result.x, Catch::Matchers::WithinRel(2.0));
    CHECK_THAT(result.y, Catch::Matchers::WithinRel(4.0));
    CHECK_THAT(result.z, Catch::Matchers::WithinRel(6.0));
}

TEST_CASE("EcefVector operator+=", "[coordinate][EcefVector]")
{
    auto lhs = shift::coordinate::EcefVector{1.0, 2.0, 3.0};
    constexpr auto rhs = shift::coordinate::EcefVector{1.0, 2.0, 3.0};

    lhs += rhs;
    CHECK_THAT(lhs.x, Catch::Matchers::WithinRel(2.0));
    CHECK_THAT(lhs.y, Catch::Matchers::WithinRel(4.0));
    CHECK_THAT(lhs.z, Catch::Matchers::WithinRel(6.0));
}

TEST_CASE("EcefVector operator-", "[coordinate][EcefVector]")
{
    constexpr auto lhs = shift::coordinate::EcefVector{1.0, 2.0, 3.0};
    constexpr auto rhs = lhs;
    constexpr auto result = lhs - rhs;
    CHECK_THAT(result.x, Catch::Matchers::WithinRel(0.0));
    CHECK_THAT(result.y, Catch::Matchers::WithinRel(0.0));
    CHECK_THAT(result.z, Catch::Matchers::WithinRel(0.0));
}

TEST_CASE("EcefVector operator-=", "[coordinate][EcefVector]")
{
    auto lhs = shift::coordinate::EcefVector{1.0, 2.0, 3.0};
    constexpr auto rhs = shift::coordinate::EcefVector{1.0, 2.0, 3.0};
    lhs -= rhs;
    CHECK_THAT(lhs.x, Catch::Matchers::WithinRel(0.0));
    CHECK_THAT(lhs.y, Catch::Matchers::WithinRel(0.0));
    CHECK_THAT(lhs.z, Catch::Matchers::WithinRel(0.0));
}

TEST_CASE("EcefVector operator*", "[coordinate][EcefVector]")
{
    constexpr auto vec = shift::coordinate::EcefVector{1.0, 2.0, 3.0};
    constexpr auto result = vec * 2.0;
    CHECK_THAT(result.x, Catch::Matchers::WithinRel(2.0));
    CHECK_THAT(result.y, Catch::Matchers::WithinRel(4.0));
    CHECK_THAT(result.z, Catch::Matchers::WithinRel(6.0));
}

TEST_CASE("EcefVector operator*=", "[coordinate][EcefVector]")
{
    auto vec = shift::coordinate::EcefVector{1.0, 2.0, 3.0};
    vec *= 2.0;
    CHECK_THAT(vec.x, Catch::Matchers::WithinRel(2.0));
    CHECK_THAT(vec.y, Catch::Matchers::WithinRel(4.0));
    CHECK_THAT(vec.z, Catch::Matchers::WithinRel(6.0));
}

TEST_CASE("EcefVector operator/", "[coordinate][EcefVector]")
{
    constexpr auto vec = shift::coordinate::EcefVector{2.0, 4.0, 6.0};
    const auto result = vec / 2.0;
    CHECK_THAT(result.x, Catch::Matchers::WithinRel(1.0));
    CHECK_THAT(result.y, Catch::Matchers::WithinRel(2.0));
    CHECK_THAT(result.z, Catch::Matchers::WithinRel(3.0));

    SECTION("divide by zero")
    {
        CHECK_THROWS(vec / 0.0);
    }
}

TEST_CASE("EcefVector operator/=", "[coordinate][EcefVector]")
{
    auto vec = shift::coordinate::EcefVector{2.0, 4.0, 6.0};
    vec /= 2.0;
    CHECK_THAT(vec.x, Catch::Matchers::WithinRel(1.0));
    CHECK_THAT(vec.y, Catch::Matchers::WithinRel(2.0));
    CHECK_THAT(vec.z, Catch::Matchers::WithinRel(3.0));

    SECTION("divide by zero")
    {
        CHECK_THROWS(vec /= 0.0);
    }
}

TEST_CASE("EcefVector unary -", "[coordinate][EcefVector]")
{
    constexpr auto vec = shift::coordinate::EcefVector{1.0, 2.0, 3.0};
    constexpr auto negated = -vec;
    CHECK_THAT(negated.x, Catch::Matchers::WithinRel(-1.0));
    CHECK_THAT(negated.y, Catch::Matchers::WithinRel(-2.0));
    CHECK_THAT(negated.z, Catch::Matchers::WithinRel(-3.0));
}

TEST_CASE("EcefVector magnitude", "[coordinate][EcefVector]")
{
    constexpr auto vec = shift::coordinate::EcefVector{1.0, 2.0, 3.0};
    CHECK_THAT(vec.magnitude(),
               Catch::Matchers::WithinRel(std::sqrt(14.0), 1e-6));
}

TEST_CASE("EcefVector distance", "[coordinate][EcefVector]")
{
    constexpr auto lhs = shift::coordinate::EcefVector{1.0, 2.0, 3.0};
    constexpr auto rhs = shift::coordinate::EcefVector{2.0, 4.0, 6.0};
    CHECK_THAT(shift::coordinate::EcefVector::distance(lhs, rhs),
               Catch::Matchers::WithinRel(lhs.magnitude()));
}

TEST_CASE("EcefVector dot", "[coordinate][EcefVector]")
{
    constexpr auto lhs = shift::coordinate::EcefVector{1.0, 2.0, 3.0};
    constexpr auto rhs = shift::coordinate::EcefVector{3.0, 4.0, 5.0};
    CHECK_THAT(shift::coordinate::EcefVector::dot(lhs, rhs),
               Catch::Matchers::WithinRel(26.0));
}

TEST_CASE("EcefVector cross", "[coordinate][EcefVector]")
{
    constexpr auto lhs = shift::coordinate::EcefVector{1.0, 2.0, 3.0};
    constexpr auto rhs = shift::coordinate::EcefVector{3.0, 4.0, 5.0};

    constexpr auto cross = shift::coordinate::EcefVector::cross(lhs, rhs);
    CHECK_THAT(cross.x, Catch::Matchers::WithinRel(-2.0));
    CHECK_THAT(cross.y, Catch::Matchers::WithinRel(4.0));
    CHECK_THAT(cross.z, Catch::Matchers::WithinRel(-2.0));
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
