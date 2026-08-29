#include "shift/core/TimeConvert.hpp"

#include <catch2/catch_test_macros.hpp>

#include "shift/core/TimeTypes.hpp"

TEST_CASE("seconds_to_useconds", "[core][TimeConvert]")
{
    SECTION("zero seconds")
    {
        CHECK(
            shift::time::convert::seconds_to_useconds(shift::time::Seconds{0.0})
            == shift::time::Microseconds{0});
    }

    SECTION("one second")
    {
        CHECK(
            shift::time::convert::seconds_to_useconds(shift::time::Seconds{1.0})
            == shift::time::Microseconds{1000000});
    }

    SECTION("one and a half seconds")
    {
        CHECK(shift::time::convert::seconds_to_useconds(
                  shift::time::Seconds{1.5})  // NOLINT
              == shift::time::Microseconds{1500000});
    }
}

TEST_CASE("useconds_to_seconds", "[core][TimeConvert]")
{
    SECTION("zero seconds")
    {
        CHECK(shift::time::convert::useconds_to_seconds(
                  shift::time::Microseconds{0})
              == shift::time::Seconds{0.0});
    }

    SECTION("one second")
    {
        CHECK(shift::time::convert::useconds_to_seconds(
                  shift::time::Microseconds{1000000})
              == shift::time::Seconds{1.0});
    }
}

TEST_CASE("minutes_to_seconds", "[core][TimeConvert]")
{
    SECTION("one minute")
    {
        CHECK(
            shift::time::convert::minutes_to_seconds(shift::time::Minutes{1.0})
            == shift::time::Seconds{60.0});  // NOLINT
    }

    SECTION("one and a half minutes")
    {
        CHECK(shift::time::convert::minutes_to_seconds(
                  shift::time::Minutes{1.5})  // NOLINT
              == shift::time::Seconds{90.0});  // NOLINT
    }
}

TEST_CASE("seconds_to_minutes", "[core][TimeConvert]")
{
    SECTION("one minute")
    {
        CHECK(shift::time::convert::seconds_to_minutes(
                  shift::time::Seconds{60.0})  // NOLINT
              == shift::time::Minutes{1.0});
    }

    SECTION("one and a half minutes")
    {
        CHECK(shift::time::convert::seconds_to_minutes(
                  shift::time::Seconds{90.0})  // NOLINT
              == shift::time::Minutes{1.5});  // NOLINT
    }
}

TEST_CASE("hours_to_minutes", "[core][TimeConvert]")
{
    SECTION("one hour")
    {
        CHECK(shift::time::convert::hours_to_minutes(shift::time::Hours{1.0})
              == shift::time::Minutes{60.0});  // NOLINT
    }

    SECTION("one and a half hours")
    {
        CHECK(shift::time::convert::hours_to_minutes(
                  shift::time::Hours{1.5})  // NOLINT
              == shift::time::Minutes{90.0});  // NOLINT
    }
}

TEST_CASE("minutes_to_hours", "[core][TimeConvert]")
{
    SECTION("one hour")
    {
        CHECK(shift::time::convert::minutes_to_hours(
                  shift::time::Minutes{60.0})  // NOLINT
              == shift::time::Hours{1.0});
    }

    SECTION("one and a half hours")
    {
        CHECK(shift::time::convert::minutes_to_hours(
                  shift::time::Minutes{90.0})  // NOLINT
              == shift::time::Hours{1.5});  // NOLINT
    }
}

TEST_CASE("days_to_hours", "[core][TimeConvert]")
{
    SECTION("one day")
    {
        CHECK(shift::time::convert::days_to_hours(shift::time::Days{1.0})
              == shift::time::Hours{24.0});  // NOLINT
    }

    SECTION("one and a half days")
    {
        CHECK(shift::time::convert::days_to_hours(
                  shift::time::Days{1.5})  // NOLINT
              == shift::time::Hours{36.0});  // NOLINT
    }
}

TEST_CASE("hours_to_days", "[core][TimeConvert]")
{
    SECTION("one day")
    {
        CHECK(shift::time::convert::hours_to_days(
                  shift::time::Hours{24.0})  // NOLINT
              == shift::time::Days{1.0});
    }

    SECTION("one and a half days")
    {
        CHECK(shift::time::convert::hours_to_days(
                  shift::time::Hours{36.0})  // NOLINT
              == shift::time::Days{1.5});  // NOLINT
    }
}
