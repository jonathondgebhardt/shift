#include <memory>
#include <utility>

#include "shift/telemetry/MemoryTelemetryRecorder.hpp"

#include <catch2/catch_test_macros.hpp>

#include "shift/core/FixedTimeUpdater.hpp"
#include "shift/core/Simulation.hpp"
#include "shift/core/SimulationRunner.hpp"
#include "shift/telemetry/EntityDataDefinitions.hpp"
#include "shift/telemetry/Telemetry.hpp"

TEST_CASE("MemoryTelemetryRecorder contains records",
          "[telemetry][MemoryTelemetryRecorder]")
{
    const auto delta = shift::time::Microseconds{10};
    auto updater =
        std::make_unique<shift::FixedTimeUpdater<shift::time::Microseconds>>(
            delta);
    auto runner = shift::SimulationRunner{std::move(updater)};

    auto simulation = shift::Simulation{};
    auto& clock = simulation.clock();
    REQUIRE(clock.time() == shift::time::Microseconds{});
    REQUIRE(clock.delta() == shift::time::Microseconds{});

    auto recorder = shift::telemetry::MemoryTelemetryRecorder{};
    auto telemetry = shift::telemetry::Telemetry{recorder};
    telemetry.observe(shift::telemetry::entity_position);

    simulation.world().add_entity();

    runner.set_telemetry(&telemetry);
    runner.run(simulation);

    REQUIRE(clock.time() == delta);
    REQUIRE(clock.delta() == delta);

    CHECK(recorder.records().size() == 2);
}
