#include <thread>

#include "shift/time/Timer.hpp"

#include <catch2/catch_test_macros.hpp>

#include "shift/time/TimeTypes.hpp"

TEST_CASE("Timer elapsed", "[time][Timer]")
{
    auto timer = shift::time::Timer{};
    timer.reset();

    constexpr auto sleep_time = shift::time::Microseconds{10};

    std::this_thread::sleep_for(sleep_time);
    const auto elapsed = timer.elapsed();

    std::this_thread::sleep_for(sleep_time);
    CHECK(elapsed < timer.elapsed());
}

// disable this test because it's not implemented very well.
// my goal was to make sure time elapses after reset and tick.
TEST_CASE("Timer tick", "[time][Timer][.]")
{
    auto timer = shift::time::Timer{};
    timer.reset();

    constexpr auto sleep_time =
        shift::time::Duration{shift::time::Milliseconds{10}};

    std::this_thread::sleep_for(sleep_time.get());
    const auto tick_1 = timer.tick();

    std::this_thread::sleep_for(sleep_time.get());
    const auto tick_2 = timer.tick();

    const auto delta = tick_2 - tick_1;
    CHECK(delta < sleep_time);
}
