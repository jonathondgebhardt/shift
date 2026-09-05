#include "shift/time/FixedTimeUpdater.hpp"

#include <catch2/catch_test_macros.hpp>

#include "shift/time/Clock.hpp"

TEST_CASE("FixedTimeUpdater update", "[time][FixedTimeUpdater]")
{
    auto clock = shift::time::Clock{};
    REQUIRE(clock.time() == shift::time::SimulationTime{});
    REQUIRE(clock.delta() == shift::time::Duration{});

    constexpr auto duration =
        shift::time::Duration{shift::time::Microseconds{100}};
    auto updater = shift::time::FixedTimeUpdater{duration};
    updater.update(clock);

    CHECK(clock.time() == shift::time::SimulationTime{duration.get()});
    CHECK(clock.delta() == duration);
}
