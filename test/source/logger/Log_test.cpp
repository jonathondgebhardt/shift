#include "shift/logger/Log.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Log does the logging", "[core][Log]")
{
    SECTION("trace")
    {
        auto msg = shift::log::trace();
        msg.append("hello {}", "trace");
    }
    SECTION("debug")
    {
        auto msg = shift::log::debug();
        msg.append("hello {}", "debug");
    }
    SECTION("info")
    {
        auto msg = shift::log::info();
        msg.append("hello {}", "info");
    }
    SECTION("warning")
    {
        auto msg = shift::log::warning();
        msg.append("hello {}", "warning");
    }
    SECTION("error")
    {
        auto msg = shift::log::error();
        msg.append("hello {}", "error");
    }
    SECTION("critical")
    {
        auto msg = shift::log::critical();
        msg.append("hello {}", "critical");
    }
}
