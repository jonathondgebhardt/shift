#include <thread>

#include "shift/core/RealTimeUpdater.hpp"

#include <catch2/catch_test_macros.hpp>

#include "shift/core/SimulationTime.hpp"
#include "shift/core/TimeTypes.hpp"

TEST_CASE("RealTimeUpdater update", "[core][RealTimeUpdater]")
{
    auto clock = shift::Clock{};
    REQUIRE(clock.time() == shift::time::SimulationTime{});
    REQUIRE(clock.delta() == shift::time::Microseconds{});

    auto updater = shift::RealTimeUpdater{};
    updater.startup();

    constexpr auto wait_time = shift::time::Milliseconds{10};
    std::this_thread::sleep_for(wait_time);

    updater.update(clock);

    CHECK(clock.time() >= shift::time::SimulationTime{wait_time});
    CHECK(clock.delta() >= wait_time);
}
