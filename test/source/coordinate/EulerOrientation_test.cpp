#include "shift/coordinate/EulerOrientation.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

TEST_CASE("EulerOrientation zero initialized", "[coordinate][EulerOrientation]")
{
    const auto orientation = shift::coordinate::EulerOrientation{};
    CHECK_THAT(orientation.yaw(), Catch::Matchers::WithinRel(0.0f));
    CHECK_THAT(orientation.pitch(), Catch::Matchers::WithinRel(0.0f));
    CHECK_THAT(orientation.roll(), Catch::Matchers::WithinRel(0.0f));
}

TEST_CASE("EulerOrientation triple float", "[coordinate][EulerOrientation]")
{
    const auto orientation =
        shift::coordinate::EulerOrientation{1.0f, 2.0f, 3.0f};
    CHECK_THAT(orientation.yaw(), Catch::Matchers::WithinRel(1.0f));
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers,
    // readability-magic-numbers)
    CHECK_THAT(orientation.pitch(), Catch::Matchers::WithinRel(2.0f));
    CHECK_THAT(orientation.roll(), Catch::Matchers::WithinRel(3.0f));
    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers,
    // readability-magic-numbers)
}

TEST_CASE("EulerOrientation set_yaw", "[coordinate][EulerOrientation]")
{
    auto orientation = shift::coordinate::EulerOrientation{};
    orientation.set_yaw(1.0f);
    CHECK_THAT(orientation.yaw(), Catch::Matchers::WithinRel(1.0f));
}

TEST_CASE("EulerOrientation set_pitch", "[coordinate][EulerOrientation]")
{
    auto orientation = shift::coordinate::EulerOrientation{};
    orientation.set_pitch(1.0f);
    CHECK_THAT(orientation.pitch(), Catch::Matchers::WithinRel(1.0f));
}

TEST_CASE("EulerOrientation set_roll", "[coordinate][EulerOrientation]")
{
    auto orientation = shift::coordinate::EulerOrientation{};
    orientation.set_roll(1.0f);
    CHECK_THAT(orientation.roll(), Catch::Matchers::WithinRel(1.0f));
}
