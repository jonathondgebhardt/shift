#include "shift/coordinate/Coordinate.hpp"

#include <catch2/catch_test_macros.hpp>

#include "shift/coordinate/CoordinateTransform.hpp"
#include "shift/coordinate/EcefPosition.hpp"
#include "shift/coordinate/EnuPosition.hpp"
#include "shift/math/Utilities.hpp"

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

TEST_CASE("ECEF to geodetic", "[coordinate]")
{
    constexpr auto ecef =
        shift::coordinate::EcefPosition{497'037.55, -4'884'763.5, 4'057'696.3};
    const auto geodetic = shift::coordinate::to_geodetic(ecef);
    CHECK(geodetic
          == shift::coordinate::GeodeticPosition{
              39.760000147999506, -84.18999995390443, 250.00608094938437});
}

TEST_CASE("ENU to geodetic", "[coordinate]")
{
    // todo: add tests with a non-zero enu
    const auto frame =
        shift::coordinate::EnuFrame{.origin = {39.76, -84.19, 250.0}};
    constexpr auto enu = shift::coordinate::EnuPosition{};
    const auto geodetic = shift::coordinate::to_geodetic(enu, frame);

    CHECK(shift::math::floating_point_eq(
        geodetic.latitude(), frame.origin.latitude(), 1e-6));
    CHECK(shift::math::floating_point_eq(
        geodetic.longitude(), frame.origin.longitude(), 1e-6));
    CHECK(shift::math::floating_point_eq(
        geodetic.altitude(), frame.origin.altitude(), 1e-6));
}

TEST_CASE("geodetic to ECEF", "[coordinate]")
{
    const auto geodetic =
        shift::coordinate::GeodeticPosition{39.76, -84.19, 250.0};
    const auto ecef = shift::coordinate::to_ecef(geodetic);

    CHECK(ecef
          == shift::coordinate::EcefPosition{
              497'037.546660842, -4'884'763.506205418, 4'057'696.283478218});
}

TEST_CASE("ENU to ECEF", "[coordinate]")
{
    // todo: add tests with a non-zero enu
    constexpr auto enu = shift::coordinate::EnuPosition{};
    const auto frame =
        shift::coordinate::EnuFrame{.origin = {39.76, -84.19, 250.0}};
    const auto ecef = shift::coordinate::to_ecef(enu, frame);

    CHECK(ecef
          == shift::coordinate::EcefPosition{
              497'037.5466608419, -4'884'763.506205417, 4'057'696.2834782195});
}

TEST_CASE("geodetic to ENU", "[coordinate]")
{
    SECTION("ENU frame same as geodetic position")
    {
        const auto geodetic =
            shift::coordinate::GeodeticPosition{39.76, -84.19, 250.0};
        const auto frame = shift::coordinate::EnuFrame{.origin = geodetic};
        const auto enu = shift::coordinate::to_enu(geodetic, frame);

        CHECK(shift::math::floating_point_eq(enu.east, 0.0));
        CHECK(shift::math::floating_point_eq(enu.north, 0.0));
        CHECK(shift::math::floating_point_eq(enu.up, 0.0));
    }

    SECTION("equator, prime meridian")
    {
        const auto frame = shift::coordinate::EnuFrame{.origin = {30.0, 120.0}};
        constexpr auto geodetic = shift::coordinate::GeodeticPosition{};
        const auto enu = shift::coordinate::to_enu(geodetic, frame);

        CHECK(shift::math::floating_point_eq(enu.east, -5'523'628.670817468));
        CHECK(shift::math::floating_point_eq(
            enu.north, 1'613'038.3753132238, 1e-5));
        CHECK(shift::math::floating_point_eq(enu.up, -9'134'611.891368134));
    }
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
