#include "shift/core/UpdateResult.hpp"

#include <catch2/catch_test_macros.hpp>

#include "shift/time/Duration.hpp"
#include "shift/time/TimePoint.hpp"
#include "shift/time/TimeTypes.hpp"

TEST_CASE("UpdateResult schedule_at", "[core][UpdateResult]")
{
    constexpr auto time = shift::time::TimePoint{shift::time::Seconds{1}};
    constexpr auto update_result = shift::UpdateResult::schedule_at(time);
    CHECK(!update_result.stopped());

    const auto next_time = update_result.next_time(shift::time::TimePoint{});
    REQUIRE(next_time);
    // NOLINTNEXTLINE(bugprone-unchecked-optional-access)
    CHECK(*next_time == time);
}

TEST_CASE("UpdateResult schedule_after", "[core][UpdateResult]")
{
    constexpr auto duration = shift::time::Duration{shift::time::Seconds{1}};
    constexpr auto update_result =
        shift::UpdateResult::schedule_after(duration);
    CHECK(!update_result.stopped());

    const auto next_time = update_result.next_time(shift::time::TimePoint{});
    REQUIRE(next_time);
    // NOLINTNEXTLINE(bugprone-unchecked-optional-access)
    CHECK(next_time->data() == duration.data());
}

TEST_CASE("UpdateResult schedule_now", "[core][UpdateResult]")
{
    constexpr auto update_result = shift::UpdateResult::schedule_now();
    CHECK(!update_result.stopped());

    const auto next_time = update_result.next_time(shift::time::TimePoint{});
    REQUIRE(next_time);

    // NOLINTNEXTLINE(bugprone-unchecked-optional-access)
    CHECK(*next_time == shift::time::TimePoint{});
}

TEST_CASE("UpdateResult stop", "[core][UpdateResult]")
{
    constexpr auto update_result = shift::UpdateResult::stop();
    CHECK(update_result.stopped());
    CHECK(!update_result.next_time(shift::time::TimePoint{}));
}
