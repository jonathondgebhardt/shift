#include <thread>

#include "shift/core/RealTimeUpdater.hpp"

#include <catch2/catch_test_macros.hpp>

#include "shift/core/TimeConvert.hpp"
#include "shift/core/TimeTypes.hpp"

TEST_CASE("RealTimeUpdater type", "[core][RealTimeUpdater]")
{
    CHECK(std::string{shift::RealTimeUpdater{}.type()} == "RealTimeUpdater");
}

TEST_CASE("RealTimeUpdater next_time", "[core][RealTimeUpdater]")
{
    auto updater = shift::RealTimeUpdater{};

    constexpr auto wait_time = shift::time::Milliseconds{10};

    // todo: let updater know to start timer

    std::this_thread::sleep_for(wait_time);
    const auto next_time = updater.next_time();
    CHECK(shift::time::convert::time_cast<shift::time::Milliseconds>(next_time)
          == wait_time);
}
