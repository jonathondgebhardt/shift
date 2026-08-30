#include "shift/core/FixedTimeUpdater.hpp"

#include <catch2/catch_test_macros.hpp>

#include "shift/core/Clock.hpp"
#include "shift/core/TimeTypes.hpp"

TEST_CASE("FixedTimeUpdater update", "[core][FixedTimeUpdater]")
{
    auto clock = shift::Clock{};
    REQUIRE(clock.time() == shift::time::Microseconds{});
    REQUIRE(clock.delta() == shift::time::Microseconds{});

    constexpr auto delta = shift::time::Microseconds{100};
    auto updater = shift::FixedTimeUpdater{delta};
    updater.update(clock);

    CHECK(clock.time() == delta);
    CHECK(clock.delta() == delta);
}
