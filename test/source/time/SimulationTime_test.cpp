#include "shift/time/SimulationTime.hpp"

#include <catch2/catch_test_macros.hpp>

#include "shift/time/TimeTypes.hpp"

TEST_CASE("SimulationTime as", "[time][SimulationTime]")
{
    const auto time = shift::time::Seconds{1};
    const auto sim_time = shift::time::SimulationTime{time};

    CHECK(sim_time.as<shift::time::Minutes>()
          == shift::time::time_cast<shift::time::Minutes>(time));
}

TEST_CASE("SimulationTime + Duration", "[time][SimulationTime]")
{
    constexpr auto time = shift::time::SimulationTime{shift::time::Seconds{0}};
    constexpr auto duration = shift::time::Duration{shift::time::Seconds{1}};
    constexpr auto sum = time + duration;
    CHECK(sum == shift::time::SimulationTime{shift::time::Seconds{1}});
}

TEST_CASE("SimulationTime += Duration", "[time][SimulationTime]")
{
    auto sim_time = shift::time::SimulationTime{shift::time::Seconds{0}};
    constexpr auto duration = shift::time::Duration{shift::time::Seconds{1}};
    sim_time += duration;
    CHECK(sim_time.get() == duration.get());
}

TEST_CASE("SimulationTime - Duration", "[time][SimulationTime]")
{
    constexpr auto time = shift::time::SimulationTime{shift::time::Seconds{1}};
    constexpr auto duration = shift::time::Duration{shift::time::Seconds{1}};
    constexpr auto diff = time - duration;
    CHECK(diff == shift::time::SimulationTime{shift::time::Seconds{0}});
}

TEST_CASE("SimulationTime -= Duration", "[time][SimulationTime]")
{
    auto sim_time = shift::time::SimulationTime{shift::time::Seconds{1}};
    constexpr auto duration = shift::time::Duration{shift::time::Seconds{1}};
    sim_time -= duration;
    CHECK(sim_time == shift::time::SimulationTime{});
}

TEST_CASE("SimulationTime - SimulationTime", "[time][SimulationTime]")
{
    constexpr auto lhs = shift::time::SimulationTime{shift::time::Seconds{1}};
    constexpr auto rhs = shift::time::SimulationTime{shift::time::Seconds{1}};
    constexpr auto diff = lhs - rhs;
    CHECK(diff == shift::time::Duration{shift::time::Seconds{0}});
}
