#include "shift/time/TimePoint.hpp"

#include <catch2/catch_test_macros.hpp>

#include "shift/time/TimeTypes.hpp"

TEST_CASE("TimePoint as", "[time][TimePoint]")
{
    constexpr auto time = shift::time::Seconds{1};
    const auto sim_time = shift::time::TimePoint{time};

    CHECK(sim_time.as<shift::time::Minutes>()
          == shift::time::time_cast<shift::time::Minutes>(time));
}

TEST_CASE("TimePoint + Duration", "[time][TimePoint]")
{
    constexpr auto time = shift::time::TimePoint{shift::time::Seconds{0}};
    constexpr auto duration = shift::time::Duration{shift::time::Seconds{1}};
    constexpr auto sum = time + duration;
    CHECK(sum == shift::time::TimePoint{shift::time::Seconds{1}});
}

TEST_CASE("TimePoint += Duration", "[time][TimePoint]")
{
    auto sim_time = shift::time::TimePoint{shift::time::Seconds{0}};
    constexpr auto duration = shift::time::Duration{shift::time::Seconds{1}};
    sim_time += duration;
    CHECK(sim_time.get() == duration.get());
}

TEST_CASE("TimePoint - Duration", "[time][TimePoint]")
{
    constexpr auto time = shift::time::TimePoint{shift::time::Seconds{1}};
    constexpr auto duration = shift::time::Duration{shift::time::Seconds{1}};
    constexpr auto diff = time - duration;
    CHECK(diff == shift::time::TimePoint{shift::time::Seconds{0}});
}

TEST_CASE("TimePoint -= Duration", "[time][TimePoint]")
{
    auto sim_time = shift::time::TimePoint{shift::time::Seconds{1}};
    constexpr auto duration = shift::time::Duration{shift::time::Seconds{1}};
    sim_time -= duration;
    CHECK(sim_time == shift::time::TimePoint{});
}

TEST_CASE("TimePoint - TimePoint", "[time][TimePoint]")
{
    constexpr auto lhs = shift::time::TimePoint{shift::time::Seconds{1}};
    constexpr auto rhs = shift::time::TimePoint{shift::time::Seconds{1}};
    constexpr auto diff = lhs - rhs;
    CHECK(diff == shift::time::Duration{shift::time::Seconds{0}});
}
