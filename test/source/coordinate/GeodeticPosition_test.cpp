#include "shift/coordinate/GeodeticPosition.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

TEST_CASE("GeodeticPosition zero initialized", "[coordinate][GeodeticPosition]")
{
    constexpr auto geodetic = shift::coordinate::GeodeticPosition{};
    CHECK_THAT(geodetic.latitude(), Catch::Matchers::WithinRel(0.0));
    CHECK_THAT(geodetic.longitude(), Catch::Matchers::WithinRel(0.0));
    CHECK_THAT(geodetic.altitude(), Catch::Matchers::WithinRel(0.0));
}

TEST_CASE("GeodeticPosition double double", "[coordinate][GeodeticPosition]")
{
    SECTION("valid latitude and longitude")
    {
        constexpr auto latitude = 39.76;
        constexpr auto longitude = -84.19;
        const auto geodetic =
            shift::coordinate::GeodeticPosition{latitude, longitude};
        CHECK_THAT(geodetic.latitude(), Catch::Matchers::WithinRel(latitude));
        CHECK_THAT(geodetic.longitude(), Catch::Matchers::WithinRel(longitude));
    }

    SECTION("throws on invalid latitude")
    {
        constexpr auto longitude = -84.19;

        SECTION("below valid latitude")
        {
            constexpr auto below_latitude = -90.1;
            CHECK_THROWS_WITH((shift::coordinate::GeodeticPosition{
                                  below_latitude, longitude}),
                              Catch::Matchers::ContainsSubstring("latitude"));
        }

        SECTION("above valid latitude")
        {
            constexpr auto above_latitude = 90.1;
            CHECK_THROWS_WITH((shift::coordinate::GeodeticPosition{
                                  above_latitude, longitude}),
                              Catch::Matchers::ContainsSubstring("latitude"));
        }
    }

    SECTION("throws on invalid longitude")
    {
        constexpr auto latitude = 39.76;

        SECTION("below valid longitude")
        {
            constexpr auto below_longitude = -180.1;
            CHECK_THROWS_WITH((shift::coordinate::GeodeticPosition{
                                  latitude, below_longitude}),
                              Catch::Matchers::ContainsSubstring("longitude"));
        }

        SECTION("above valid longitude")
        {
            constexpr auto above_longitude = 180.1;
            CHECK_THROWS_WITH((shift::coordinate::GeodeticPosition{
                                  latitude, above_longitude}),
                              Catch::Matchers::ContainsSubstring("longitude"));
        }
    }
}

TEST_CASE("GeodeticPosition triple double", "[coordinate][GeodeticPosition]")
{
    constexpr auto altitude = 250.0;

    SECTION("valid latitude, longitude, and altitude")
    {
        constexpr auto latitude = 39.76;
        constexpr auto longitude = -84.19;
        const auto geodetic =
            shift::coordinate::GeodeticPosition{latitude, longitude, altitude};
        CHECK_THAT(geodetic.latitude(), Catch::Matchers::WithinRel(latitude));
        CHECK_THAT(geodetic.longitude(), Catch::Matchers::WithinRel(longitude));
        CHECK_THAT(geodetic.altitude(), Catch::Matchers::WithinRel(altitude));
    }

    SECTION("throws on invalid latitude")
    {
        constexpr auto longitude = -84.19;

        SECTION("below valid latitude")
        {
            constexpr auto below_latitude = -90.1;
            CHECK_THROWS_WITH((shift::coordinate::GeodeticPosition{
                                  below_latitude, longitude, altitude}),
                              Catch::Matchers::ContainsSubstring("latitude"));
        }

        SECTION("above valid latitude")
        {
            constexpr auto above_latitude = 90.1;
            CHECK_THROWS_WITH((shift::coordinate::GeodeticPosition{
                                  above_latitude, longitude, altitude}),
                              Catch::Matchers::ContainsSubstring("latitude"));
        }
    }

    SECTION("throws on invalid longitude")
    {
        constexpr auto latitude = 39.76;

        SECTION("below valid longitude")
        {
            constexpr auto below_longitude = -180.1;
            CHECK_THROWS_WITH((shift::coordinate::GeodeticPosition{
                                  latitude, below_longitude, altitude}),
                              Catch::Matchers::ContainsSubstring("longitude"));
        }

        SECTION("above valid longitude")
        {
            constexpr auto above_longitude = 180.1;
            CHECK_THROWS_WITH((shift::coordinate::GeodeticPosition{
                                  latitude, above_longitude, altitude}),
                              Catch::Matchers::ContainsSubstring("longitude"));
        }
    }
}

TEST_CASE("GeodeticPosition operator==", "[coordinate][GeodeticPosition]")
{
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
    CHECK(shift::coordinate::GeodeticPosition{1.0, 2.0, 3.0}
          == shift::coordinate::GeodeticPosition{1.0, 2.0, 3.0});

    CHECK(shift::coordinate::GeodeticPosition{1.0, 2.0, 3.0}
          != shift::coordinate::GeodeticPosition{4.0, 2.0, 3.0});

    CHECK(shift::coordinate::GeodeticPosition{1.0, 2.0, 3.0}
          != shift::coordinate::GeodeticPosition{1.0, 4.0, 3.0});

    CHECK(shift::coordinate::GeodeticPosition{1.0, 2.0, 3.0}
          != shift::coordinate::GeodeticPosition{1.0, 2.0, 4.0});
    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
}

TEST_CASE("Geodetic set_latitude", "[coordinate][GeodeticPosition]")
{
    auto geodetic = shift::coordinate::GeodeticPosition{};
    SECTION("valid latitude")
    {
        geodetic.set_latitude(1.0);
        CHECK_THAT(geodetic.latitude(), Catch::Matchers::WithinRel(1.0));
    }

    SECTION("throws on invalid latitude")
    {
        SECTION("below valid latitude")
        {
            constexpr auto below_latitude = -90.1;
            CHECK_THROWS_WITH((geodetic.set_latitude(below_latitude)),
                              Catch::Matchers::ContainsSubstring("latitude"));
        }

        SECTION("above valid latitude")
        {
            constexpr auto above_latitude = 90.1;
            CHECK_THROWS_WITH((geodetic.set_latitude(above_latitude)),
                              Catch::Matchers::ContainsSubstring("latitude"));
        }
    }
}

TEST_CASE("Geodetic set_longitude", "[coordinate][GeodeticPosition]")
{
    auto geodetic = shift::coordinate::GeodeticPosition{};
    SECTION("valid longitude")
    {
        geodetic.set_longitude(1.0);
        CHECK_THAT(geodetic.longitude(), Catch::Matchers::WithinRel(1.0));
    }

    SECTION("throws on invalid longitude")
    {
        SECTION("below valid longitude")
        {
            constexpr auto below_longitude = -180.1;
            CHECK_THROWS_WITH((geodetic.set_longitude(below_longitude)),
                              Catch::Matchers::ContainsSubstring("longitude"));
        }

        SECTION("above valid longitude")
        {
            constexpr auto above_longitude = 180.1;
            CHECK_THROWS_WITH((geodetic.set_longitude(above_longitude)),
                              Catch::Matchers::ContainsSubstring("longitude"));
        }
    }
}

TEST_CASE("Geodetic set_altitude", "[coordinate][GeodeticPosition]")
{
    auto geodetic = shift::coordinate::GeodeticPosition{};
    geodetic.set_altitude(1.0);
    CHECK_THAT(geodetic.altitude(), Catch::Matchers::WithinRel(1.0));
}
