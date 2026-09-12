#include <typeinfo>

#include "shift/telemetry/TelemetryValue.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

TEST_CASE("TelemetryValue is", "[telemetry][TelemetryValue]")
{
    const auto double_value = shift::telemetry::TelemetryValue{1.0};
    CHECK(double_value.is<double>());
    CHECK(!double_value.is<float>());
}

TEST_CASE("TelemetryValue get", "[telemetry][TelemetryValue]")
{
    const auto double_value = shift::telemetry::TelemetryValue{1.0};
    CHECK_THAT(double_value.get<double>(), Catch::Matchers::WithinRel(1.0));
    CHECK_THROWS_AS(double_value.get<float>(), std::bad_cast);
}

TEST_CASE("TelemetryValue type", "[telemetry][TelemetryValue]")
{
    const auto double_value = shift::telemetry::TelemetryValue{1.0};
    CHECK(double_value.type() == std::type_index(typeid(double)));
    CHECK(double_value.type() != std::type_index(typeid(float)));
}

TEST_CASE("TelemetryValue to_string", "[telemetry][TelemetryValue]")
{
    const auto double_value = shift::telemetry::TelemetryValue{1.0};
    CHECK_THAT(double_value.to_string(), Catch::Matchers::StartsWith("1.0"));
}

TEST_CASE("TelemetryValue copy ctor", "[telemetry][TelemetryValue]")
{
    const auto value = shift::telemetry::TelemetryValue{1};
    const auto other_value = shift::telemetry::TelemetryValue{value};
    CHECK(value.get<int>() == other_value.get<int>());
}

TEST_CASE("TelemetryValue copy assignment", "[telemetry][TelemetryValue]")
{
    auto value = shift::telemetry::TelemetryValue{1};

    SECTION("true copy")
    {
        // NOLINTNEXTLINE(performance-unnecessary-copy-initialization)
        const auto other_value = value;
        CHECK(value.get<int>() == other_value.get<int>());
    }

    SECTION("copy self")
    {
        // NOLINTNEXTLINE(clang-diagnostic-self-assign-overloaded)
        value = value;
        CHECK(value.get<int>() == 1);
    }
}
