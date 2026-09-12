#include "shift/coordinate/Coordinate.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "shift/coordinate/CoordinateTransform.hpp"
#include "shift/coordinate/EcefPosition.hpp"
#include "shift/coordinate/EnuPosition.hpp"

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

TEST_CASE("ECEF to geodetic", "[coordinate]")
{
    constexpr auto ecef =
        shift::coordinate::EcefPosition{497'037.55, -4'884'763.5, 4'057'696.3};
    const auto geodetic = shift::coordinate::to_geodetic(ecef);

    CHECK_THAT(geodetic.latitude(),
               Catch::Matchers::WithinRel(39.760000147999506));
    CHECK_THAT(geodetic.longitude(),
               Catch::Matchers::WithinRel(-84.18999995390443));
    CHECK_THAT(geodetic.altitude(),
               Catch::Matchers::WithinRel(250.00608094938437));
}

TEST_CASE("ENU to geodetic", "[coordinate]")
{
    // todo: add tests with a non-zero enu
    const auto frame =
        shift::coordinate::EnuFrame{.origin = {39.76, -84.19, 250.0}};
    constexpr auto enu = shift::coordinate::EnuPosition{};
    const auto geodetic = shift::coordinate::to_geodetic(enu, frame);

    CHECK_THAT(geodetic.latitude(),
               Catch::Matchers::WithinRel(frame.origin.latitude()));
    CHECK_THAT(geodetic.longitude(),
               Catch::Matchers::WithinRel(frame.origin.longitude()));
    CHECK_THAT(geodetic.altitude(),
               Catch::Matchers::WithinRel(frame.origin.altitude(), 1e-6));
}

TEST_CASE("geodetic to ECEF", "[coordinate]")
{
    const auto geodetic =
        shift::coordinate::GeodeticPosition{39.76, -84.19, 250.0};
    const auto ecef = shift::coordinate::to_ecef(geodetic);

    CHECK_THAT(ecef.x, Catch::Matchers::WithinRel(497'037.546660842));
    CHECK_THAT(ecef.y, Catch::Matchers::WithinRel(-4'884'763.506205418));
    CHECK_THAT(ecef.z, Catch::Matchers::WithinRel(4'057'696.283478218));
}

TEST_CASE("ENU to ECEF", "[coordinate]")
{
    // todo: add tests with a non-zero enu
    constexpr auto enu = shift::coordinate::EnuPosition{};
    const auto frame =
        shift::coordinate::EnuFrame{.origin = {39.76, -84.19, 250.0}};
    const auto ecef = shift::coordinate::to_ecef(enu, frame);

    CHECK_THAT(ecef.x, Catch::Matchers::WithinRel(497'037.5466608419));
    CHECK_THAT(ecef.y, Catch::Matchers::WithinRel(-4'884'763.506205417));
    CHECK_THAT(ecef.z, Catch::Matchers::WithinRel(4'057'696.2834782195));
}

TEST_CASE("geodetic to ENU", "[coordinate]")
{
    SECTION("ENU frame same as geodetic position")
    {
        const auto geodetic =
            shift::coordinate::GeodeticPosition{39.76, -84.19, 250.0};
        const auto frame = shift::coordinate::EnuFrame{.origin = geodetic};
        const auto enu = shift::coordinate::to_enu(geodetic, frame);

        CHECK_THAT(enu.east, Catch::Matchers::WithinRel(0.0));
        CHECK_THAT(enu.north, Catch::Matchers::WithinRel(0.0));
        CHECK_THAT(enu.up, Catch::Matchers::WithinRel(0.0));
    }

    SECTION("equator, prime meridian")
    {
        const auto frame = shift::coordinate::EnuFrame{.origin = {30.0, 120.0}};
        constexpr auto geodetic = shift::coordinate::GeodeticPosition{};
        const auto enu = shift::coordinate::to_enu(geodetic, frame);

        CHECK_THAT(enu.east, Catch::Matchers::WithinRel(-5'523'628.670817468));
        CHECK_THAT(enu.north, Catch::Matchers::WithinRel(1'613'038.3753132238));
        CHECK_THAT(enu.up, Catch::Matchers::WithinRel(-9'134'611.891368134));
    }
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
