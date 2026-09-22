#include <memory>

#include "shift/telemetry/Telemetry.hpp"

#include <catch2/catch_test_macros.hpp>

#include "shift/telemetry/TelemetryRecord.hpp"
#include "shift/telemetry/TelemetryRecorder.hpp"

TEST_CASE("Telemetry shutdown", "[telemetry][Telemetry]")
{
    struct TestTelemetryRecorder : shift::telemetry::TelemetryRecorder
    {
        auto record([[maybe_unused]] const shift::telemetry::TelemetryRecord&
                        record) -> void override
        {
        }

        auto shutdown() -> void override { was_shutdown = true; }

        bool was_shutdown{};
    };

    auto telemetry =
        shift::telemetry::Telemetry{std::make_unique<TestTelemetryRecorder>()};
    telemetry.shutdown();
    CHECK(dynamic_cast<TestTelemetryRecorder*>(telemetry.recorder())
              ->was_shutdown);
}
