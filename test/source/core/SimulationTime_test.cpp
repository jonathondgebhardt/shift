#include "shift/core/SimulationTime.hpp"

#include <catch2/catch_test_macros.hpp>

#include "shift/core/TimeConvert.hpp"
#include "shift/core/TimeTypes.hpp"

TEST_CASE("SimulationTime as", "[core][SimulationTime]")
{
    const auto time = shift::time::Seconds{1};
    const auto sim_time = shift::SimulationTime{shift::time::Seconds{1}};

    namespace tc = shift::time::convert;

    CHECK(sim_time.as<shift::time::Microseconds>()
          == tc::time_cast<shift::time::Microseconds>(time));
    CHECK(sim_time.as<shift::time::Milliseconds>()
          == tc::time_cast<shift::time::Milliseconds>(time));
    CHECK(sim_time.as<shift::time::Seconds>() == time);
    CHECK(sim_time.as<shift::time::Minutes>()
          == tc::time_cast<shift::time::Minutes>(time));
    CHECK(sim_time.as<shift::time::Hours>()
          == tc::time_cast<shift::time::Hours>(time));
    CHECK(sim_time.as<shift::time::Days>()
          == tc::time_cast<shift::time::Days>(time));
}

TEST_CASE("SimulationTime operator==", "[core][SimulationTime]")
{
    const auto time = shift::time::Seconds{1};
    const auto sim_time = shift::SimulationTime{shift::time::Seconds{1}};

    namespace tc = shift::time::convert;

    CHECK(sim_time == tc::time_cast<shift::time::Microseconds>(time));
    CHECK(sim_time == tc::time_cast<shift::time::Milliseconds>(time));
    CHECK(sim_time == time);
    CHECK(sim_time == tc::time_cast<shift::time::Minutes>(time));
    CHECK(sim_time == tc::time_cast<shift::time::Hours>(time));
    CHECK(sim_time == tc::time_cast<shift::time::Days>(time));
}

TEST_CASE("SimulationTime operator+", "[core][SimulationTime]")
{
    const auto sim_time = shift::SimulationTime{shift::time::Seconds{0}};

    SECTION("SimulationTime")
    {
        const auto next_sim_time =
            sim_time + shift::SimulationTime{shift::time::Seconds{1}};
        CHECK(next_sim_time.as<shift::time::Seconds>()
              == shift::time::Seconds{1});
    }

    SECTION("TimeType")
    {
        const auto next_sim_time = sim_time + shift::time::Seconds{1};
        CHECK(next_sim_time.as<shift::time::Seconds>()
              == shift::time::Seconds{1});
    }
}

TEST_CASE("SimulationTime operator+=", "[core][SimulationTime]")
{
    auto sim_time = shift::SimulationTime{shift::time::Seconds{0}};

    SECTION("SimulationTime")
    {
        sim_time += shift::SimulationTime{shift::time::Seconds{1}};
        CHECK(sim_time.as<shift::time::Seconds>() == shift::time::Seconds{1});
    }

    SECTION("TimeType")
    {
        sim_time += shift::time::Seconds{1};
        CHECK(sim_time.as<shift::time::Seconds>() == shift::time::Seconds{1});
    }
}

TEST_CASE("SimulationTime operator-", "[core][SimulationTime]")
{
    const auto sim_time = shift::SimulationTime{shift::time::Seconds{1}};

    SECTION("SimulationTime")
    {
        const auto next_sim_time =
            sim_time - shift::SimulationTime{shift::time::Seconds{1}};
        CHECK(next_sim_time.as<shift::time::Seconds>()
              == shift::time::Seconds{0});
    }

    SECTION("TimeType")
    {
        const auto next_sim_time = sim_time - shift::time::Seconds{1};
        CHECK(next_sim_time.as<shift::time::Seconds>()
              == shift::time::Seconds{0});
    }
}

TEST_CASE("SimulationTime operator-=", "[core][SimulationTime]")
{
    auto sim_time = shift::SimulationTime{shift::time::Seconds{1}};

    SECTION("SimulationTime")
    {
        sim_time -= shift::SimulationTime{shift::time::Seconds{1}};
        CHECK(sim_time.as<shift::time::Seconds>() == shift::time::Seconds{0});
    }

    SECTION("TimeType")
    {
        sim_time -= shift::time::Seconds{1};
        CHECK(sim_time.as<shift::time::Seconds>() == shift::time::Seconds{0});
    }
}
