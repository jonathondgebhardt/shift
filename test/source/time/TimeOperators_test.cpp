#include <catch2/catch_test_macros.hpp>

#include "shift/time/Duration.hpp"
#include "shift/time/SimulationTime.hpp"

// todo: delete this file

TEST_CASE("SimulationTime + Duration", "[time][SimulationTime][Duration]")
{
    constexpr auto time = shift::time::SimulationTime{shift::time::Seconds{0}};
    constexpr auto duration = shift::time::Duration{shift::time::Seconds{1}};
    constexpr auto sum = time + duration;
    CHECK(sum == shift::time::SimulationTime{shift::time::Seconds{1}});
}

TEST_CASE("SimulationTime - Duration", "[time][SimulationTime][Duration]")
{
    constexpr auto time = shift::time::SimulationTime{shift::time::Seconds{1}};
    constexpr auto duration = shift::time::Duration{shift::time::Seconds{1}};
    constexpr auto diff = time - duration;
    CHECK(diff == shift::time::SimulationTime{shift::time::Seconds{0}});
}

TEST_CASE("SimulationTime - SimulationTime", "[time][SimulationTime]")
{
    constexpr auto lhs = shift::time::SimulationTime{shift::time::Seconds{1}};
    constexpr auto rhs = shift::time::SimulationTime{shift::time::Seconds{1}};
    constexpr auto diff = lhs - rhs;
    CHECK(diff == shift::time::Duration{shift::time::Seconds{0}});
}

TEST_CASE("Duration + Duration", "[time][SimulationTime]")
{
    constexpr auto lhs = shift::time::Duration{shift::time::Seconds{0}};
    constexpr auto rhs = shift::time::Duration{shift::time::Seconds{1}};
    constexpr auto sum = lhs + rhs;
    CHECK(sum == shift::time::Duration{shift::time::Seconds{1}});
}

TEST_CASE("Duration - Duration", "[time][SimulationTime]")
{
    constexpr auto lhs = shift::time::Duration{shift::time::Seconds{1}};
    constexpr auto rhs = shift::time::Duration{shift::time::Seconds{1}};
    constexpr auto sum = lhs - rhs;
    CHECK(sum == shift::time::Duration{shift::time::Seconds{0}});
}
