#include "shift/core/Entity.hpp"
#include "shift/core/FixedTimeUpdater.hpp"
#include "shift/core/Simulation.hpp"
#include "shift/core/SimulationRunner.hpp"
#include "shift/core/TimeTypes.hpp"
#include "shift/core/World.hpp"
#include "shift/logger/Log.hpp"
#include "shift/telemetry/ConsoleTelemetryRecorder.hpp"
#include "shift/telemetry/EntityDataDefinitions.hpp"
#include "shift/telemetry/Telemetry.hpp"

auto main() -> int
{
    shift::log::info().append("hello from shift_example");

    auto simulation = shift::Simulation{};
    simulation.world().add_entity(shift::Entity{});

    auto runner = shift::SimulationRunner{
        std::make_unique<shift::FixedTimeUpdater<shift::time::Milliseconds>>(
            shift::time::Milliseconds{10})};

    auto recorder = shift::telemetry::ConsoleTelemetryRecorder{};
    auto telemetry = shift::telemetry::Telemetry{recorder};
    telemetry.observe(shift::telemetry::entity_position_x);
    telemetry.observe(shift::telemetry::entity_position_y);
    telemetry.observe(shift::telemetry::entity_position_z);

    runner.set_telemetry(&telemetry);

    runner.run(simulation);

    return 0;
}
