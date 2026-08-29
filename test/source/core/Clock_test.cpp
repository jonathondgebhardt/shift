#include <string>

#include "shift/core/Clock.hpp"

#include "catch2/catch_test_macros.hpp"
#include "shift/core/TimeTypes.hpp"

TEST_CASE("Clock type", "[core][Clock]")
{
    CHECK(std::string{shift::Clock{}.type()} == "Clock");
}

TEST_CASE("Clock tick no updater", "[core][Clock]")
{
    auto clock = shift::Clock{};
    const auto frame = clock.tick();
    constexpr auto zero_time = shift::time::Microseconds{};
    CHECK(frame.time == zero_time);
    CHECK(frame.delta == zero_time);
    CHECK(clock.time() == zero_time);
    CHECK(clock.delta() == zero_time);
}
