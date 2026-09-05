#include <cmath>
#include <memory>

#include "shift/core/Entity.hpp"
#include "shift/core/Simulation.hpp"
#include "shift/core/SimulationRunner.hpp"
#include "shift/core/System.hpp"
#include "shift/core/World.hpp"
#include "shift/logger/Log.hpp"
#include "shift/telemetry/ConsoleTelemetryRecorder.hpp"
#include "shift/telemetry/EntityDataDefinitions.hpp"
#include "shift/telemetry/Telemetry.hpp"
#include "shift/time/Clock.hpp"
#include "shift/time/FixedTimeUpdater.hpp"
#include "shift/time/TimeTypes.hpp"

namespace
{

struct OrbitSystem : shift::System
{
    explicit OrbitSystem(shift::EntityUID uid)
        : uid{uid}
    {
    }

    auto startup() -> void override
    {
        if (uid == shift::EntityUID{}) {
            throw std::runtime_error("uid cannot be empty");
        }

        const auto double_equal = [](const double lhs, const double rhs)
        {
            return std::abs(lhs - rhs) < std::numeric_limits<double>::epsilon();
        };

        if (double_equal(radius, 0.0)) {
            throw std::runtime_error("radius cannot be zero");
        }

        if (double_equal(speed, 0.0)) {
            throw std::runtime_error("speed cannot be zero");
        }
    }

    auto process(shift::World& world, shift::time::Clock::TimeStep time_step)
        -> void override
    {
        // todo: consider abstracting OptionalEntityReference to add unwrap
        auto& entity = world.find_entity(uid).try_unwrap();
        entity.position().x = radius * std::cos(angle);
        entity.position().y = radius * std::sin(angle);

        angle += speed * static_cast<double>(time_step.delta.data());

        constexpr auto two_pi = 2 * std::numbers::pi;
        if (angle > two_pi) {
            angle -= two_pi;
        }
    }

    shift::EntityUID uid;

    double angle{};
    double speed{};
    std::uint8_t radius{};
};

}  // namespace

auto main() -> int
{
    shift::log::info().append("hello from shift_example");

    auto simulation = shift::Simulation{};
    auto& entity = simulation.world().add_entity();

    auto runner =
        shift::SimulationRunner{std::make_unique<shift::time::FixedTimeUpdater>(
            shift::time::Duration{shift::time::Milliseconds{16}})};

    auto telemetry = shift::telemetry::Telemetry{
        std::make_unique<shift::telemetry::ConsoleTelemetryRecorder>()};
    telemetry.observe(shift::telemetry::entity_position);

    runner.set_telemetry(&telemetry);

    auto system = OrbitSystem{entity.uid()};
    system.speed = 1.0;
    system.radius = 10u;
    simulation.add_system(system);

    runner.run(simulation);
    runner.run(simulation);
    runner.run(simulation);
    runner.run(simulation);
    runner.run(simulation);

    return 0;
}
