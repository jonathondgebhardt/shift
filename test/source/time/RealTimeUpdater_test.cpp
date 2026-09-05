#include <thread>

#include "shift/time/RealTimeUpdater.hpp"

#include <catch2/catch_test_macros.hpp>

#include "shift/time/Clock.hpp"
#include "shift/time/SimulationTime.hpp"
#include "shift/time/TimeTypes.hpp"

TEST_CASE("RealTimeUpdater update", "[time][RealTimeUpdater]")
{
    auto clock = shift::time::Clock{};
    REQUIRE(clock.time() == shift::time::SimulationTime{});
    REQUIRE(clock.delta() == shift::time::Duration{});

    auto updater = shift::time::RealTimeUpdater{};
    updater.startup();

    constexpr auto wait_time = shift::time::Milliseconds{10};
    std::this_thread::sleep_for(wait_time);

    updater.update(clock);

    CHECK(clock.time().get() >= wait_time);
    CHECK(clock.delta().get() >= wait_time);
}
