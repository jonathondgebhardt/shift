#include "shift/coordinate/Coordinate.hpp"

#include <catch2/catch_test_macros.hpp>

#include "shift/coordinate/CoordinateTransform.hpp"
#include "shift/coordinate/EcefPosition.hpp"
#include "shift/math/Utilities.hpp"

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

TEST_CASE("ECEF to geodetic", "[coordinate]")
{
    constexpr auto ecef = shift::coordinate::EcefPosition{
        .x = 497037.55, .y = -4884763.5, .z = 4057696.3};
    const auto geodetic = shift::coordinate::to_geodetic(ecef);

    CHECK(
        shift::math::floating_point_eq(geodetic.latitude, 39.760000147999506));
    CHECK(
        shift::math::floating_point_eq(geodetic.longitude, -84.18999995390443));
    CHECK(
        shift::math::floating_point_eq(geodetic.altitude, 250.00608094938437));
}

TEST_CASE("ENU to geodetic", "[coordinate]")
{
    // todo: add tests with a non-zero enu
    constexpr auto frame = shift::coordinate::EnuFrame{
        .origin = {.latitude = 39.76, .longitude = -84.19, .altitude = 250.0}};
    constexpr auto enu = shift::coordinate::EnuPosition{};
    const auto geodetic = shift::coordinate::to_geodetic(enu, frame);

    CHECK(shift::math::floating_point_eq(
        geodetic.latitude, frame.origin.latitude, 1e-6));
    CHECK(shift::math::floating_point_eq(
        geodetic.longitude, frame.origin.longitude, 1e-6));
    CHECK(shift::math::floating_point_eq(
        geodetic.altitude, frame.origin.altitude, 1e-6));
}

TEST_CASE("geodetic to ECEF", "[coordinate]")
{
    constexpr auto geodetic = shift::coordinate::GeodeticPosition{
        .latitude = 39.76, .longitude = -84.19, .altitude = 250.0};
    const auto ecef = shift::coordinate::to_ecef(geodetic);

    CHECK(shift::math::floating_point_eq(ecef.x, 497'037.546660842));
    CHECK(shift::math::floating_point_eq(ecef.y, -4'884'763.506205418));
    CHECK(shift::math::floating_point_eq(ecef.z, 4'057'696.283478218));
}

TEST_CASE("ENU to ECEF", "[coordinate]")
{
    // todo: add tests with a non-zero enu
    constexpr auto enu = shift::coordinate::EnuPosition{};
    constexpr auto frame = shift::coordinate::EnuFrame{
        .origin = {.latitude = 39.76, .longitude = -84.19, .altitude = 250.0}};
    const auto ecef = shift::coordinate::to_ecef(enu, frame);

    // 497037.5466608419, -4884763.506205417, 4057696.2834782195
    CHECK(shift::math::floating_point_eq(ecef.x, 497'037.5466608419));
    CHECK(shift::math::floating_point_eq(ecef.y, -4'884'763.506205417));
    CHECK(shift::math::floating_point_eq(ecef.z, 4'057'696.2834782195));
}

TEST_CASE("geodetic to ENU", "[coordinate]")
{
    SECTION("ENU frame same as geodetic position")
    {
        constexpr auto geodetic = shift::coordinate::GeodeticPosition{
            .latitude = 39.76, .longitude = -84.19, .altitude = 250.0};
        constexpr auto frame = shift::coordinate::EnuFrame{.origin = geodetic};
        const auto enu = shift::coordinate::to_enu(geodetic, frame);

        CHECK(shift::math::floating_point_eq(enu.east, 0.0));
        CHECK(shift::math::floating_point_eq(enu.north, 0.0));
        CHECK(shift::math::floating_point_eq(enu.up, 0.0));
    }

    SECTION("equator, prime meridian")
    {
        constexpr auto frame = shift::coordinate::EnuFrame{
            .origin = {.latitude = 30.0, .longitude = 120.0}};
        constexpr auto geodetic = shift::coordinate::GeodeticPosition{};
        const auto enu = shift::coordinate::to_enu(geodetic, frame);

        CHECK(shift::math::floating_point_eq(enu.east, -5'523'628.670817468));
        CHECK(shift::math::floating_point_eq(
            enu.north, 1'613'038.3753132238, 1e-5));
        CHECK(shift::math::floating_point_eq(enu.up, -9'134'611.891368134));
    }
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
