#include <string>

#include "shift/core/Clock.hpp"

#include "catch2/catch_test_macros.hpp"

TEST_CASE("Clock type", "[core][Clock]")
{
    CHECK(std::string{shift::Clock{}.type()} == "Clock");
}

TEST_CASE("Clock tick no updater", "[core][Clock]")
{
    CHECK_THROWS(shift::Clock{}.tick());
}
