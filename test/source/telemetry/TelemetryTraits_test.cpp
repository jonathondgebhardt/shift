#include <string>

#include "shift/telemetry/TelemetryTraits.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

TEST_CASE("TelemetryTraits ToStdStringable", "[telemetry][TelemetryTraits]")
{
    CHECK_THAT(shift::telemetry::TelemetryTraits<int>{}.to_string(0),
               Catch::Matchers::Equals("0"));
}

TEST_CASE("TelemetryTraits ToStringable", "[telemetry][TelemetryTraits]")
{
    struct Stringable
    {
        static auto to_string() -> std::string { return "Stringable"; }
    };

    CHECK_THAT(
        shift::telemetry::TelemetryTraits<Stringable>{}.to_string(Stringable{}),
        Catch::Matchers::Equals("Stringable"));
}
