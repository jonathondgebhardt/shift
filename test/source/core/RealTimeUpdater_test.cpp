#include <thread>

#include "shift/core/RealTimeUpdater.hpp"

#include <catch2/catch_test_macros.hpp>

#include "shift/core/TimeTypes.hpp"

TEST_CASE("RealTimeUpdater next_time", "[core][RealTimeUpdater]")
{
    auto clock = shift::Clock{};
    REQUIRE(clock.time() == shift::time::Microseconds{});
    REQUIRE(clock.delta() == shift::time::Microseconds{});

    auto updater = shift::RealTimeUpdater{};

    constexpr auto wait_time = shift::time::Milliseconds{10};
    std::this_thread::sleep_for(wait_time);

    updater.update(clock);

    CHECK(clock.time() >= wait_time);
    CHECK(clock.delta() >= wait_time);
}
