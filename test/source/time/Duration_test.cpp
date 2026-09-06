#include "shift/time/Duration.hpp"

#include <catch2/catch_test_macros.hpp>

#include "shift/time/TimeTypes.hpp"

TEST_CASE("Duration + Duration", "[time][Duration]")
{
    constexpr auto lhs = shift::time::Duration{shift::time::Seconds{0}};
    constexpr auto rhs = shift::time::Duration{shift::time::Seconds{1}};
    constexpr auto sum = lhs + rhs;
    CHECK(sum == shift::time::Duration{shift::time::Seconds{1}});
}

TEST_CASE("Duration += Duration", "[time][Duration]")
{
    auto lhs = shift::time::Duration{shift::time::Seconds{0}};
    constexpr auto rhs = shift::time::Duration{shift::time::Seconds{1}};
    lhs += rhs;
    CHECK(lhs == shift::time::Duration{shift::time::Seconds{1}});
}

TEST_CASE("Duration - Duration", "[time][Duration]")
{
    constexpr auto lhs = shift::time::Duration{shift::time::Seconds{1}};
    constexpr auto rhs = shift::time::Duration{shift::time::Seconds{1}};
    constexpr auto sum = lhs - rhs;
    CHECK(sum == shift::time::Duration{shift::time::Seconds{0}});
}

TEST_CASE("Duration -= Duration", "[time][Duration]")
{
    auto lhs = shift::time::Duration{shift::time::Seconds{1}};
    constexpr auto rhs = shift::time::Duration{shift::time::Seconds{1}};
    lhs -= rhs;
    CHECK(lhs == shift::time::Duration{shift::time::Seconds{0}});
}
