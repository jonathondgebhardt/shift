#include "shift/telemetry/MemoryTelemetryRecorder.hpp"

#include <catch2/catch_test_macros.hpp>

#include "shift/core/UUID.hpp"
#include "shift/telemetry/TelemetryValue.hpp"

TEST_CASE("MemoryTelemetryRecorder contains records",
          "[telemetry][MemoryTelemetryRecorder]")
{
    auto recorder = shift::telemetry::MemoryTelemetryRecorder{};
    recorder.record({.time = {},
                     .uuid = shift::UUID::build(),
                     .channel = "",
                     .value = shift::telemetry::TelemetryValue{1.0}});
    CHECK(recorder.records().size() == 1);
}
