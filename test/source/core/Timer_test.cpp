#include <cmath>
#include <thread>

#include "shift/core/Timer.hpp"

#include <catch2/catch_test_macros.hpp>

#include "shift/core/TimeTypes.hpp"

TEST_CASE("Timer elapsed", "[core][Timer]")
{
    auto timer = shift::Timer{};
    timer.reset();

    constexpr auto sleep_time = shift::time::Microseconds{10};

    std::this_thread::sleep_for(sleep_time);
    const auto elapsed = timer.elapsed();

    std::this_thread::sleep_for(sleep_time);
    CHECK(elapsed < timer.elapsed());
}

TEST_CASE("Timer tick", "[core][Timer]")
{
    auto timer = shift::Timer{};
    timer.reset();

    constexpr auto sleep_time = shift::time::Milliseconds{10};

    std::this_thread::sleep_for(sleep_time);
    const auto tick_1 = timer.tick();

    std::this_thread::sleep_for(sleep_time);
    const auto tick_2 = timer.tick();

    const auto delta =
        shift::time::Microseconds{std::abs(tick_1.count() - tick_2.count())};
    CHECK(delta < sleep_time);
}
