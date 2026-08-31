#include <memory>
#include <utility>

#include "shift/telemetry/Telemetry.hpp"

#include <catch2/catch_test_macros.hpp>

#include "shift/core/FixedTimeUpdater.hpp"
#include "shift/core/Simulation.hpp"
#include "shift/core/SimulationRunner.hpp"
#include "shift/telemetry/EntityDataDefinitions.hpp"
#include "shift/telemetry/TelemetryRecorder.hpp"

TEST_CASE("Telemetry record Entity position", "[telemetry][Telemetry]")
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

    auto recorder = shift::telemetry::ConsoleTelemetryRecorder{};
    auto telemetry = shift::telemetry::Telemetry{recorder};

    // todo: TelemetryRecord only contains double, so Vec3 is incompatible
    // telemetry.observe(shift::telemetry::entity_position);

    telemetry.observe(shift::telemetry::entity_position_x);
    telemetry.observe(shift::telemetry::entity_position_y);
    telemetry.observe(shift::telemetry::entity_position_z);

    simulation.world().add_entity(shift::Entity{});

    runner.set_telemetry(&telemetry);
    runner.run(simulation);

    CHECK(clock.time() == delta);
    CHECK(clock.delta() == delta);
}
