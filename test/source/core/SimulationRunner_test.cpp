#include <memory>
#include <utility>

#include "shift/core/Simulation.hpp"

#include <catch2/catch_test_macros.hpp>

#include "shift/core/SimulationRunner.hpp"
#include "shift/core/System.hpp"
#include "shift/core/Systems.hpp"
#include "shift/core/UpdateResult.hpp"
#include "shift/core/World.hpp"
#include "shift/telemetry/TelemetryRecord.hpp"
#include "shift/telemetry/TelemetryRecorder.hpp"
#include "shift/time/Clock.hpp"
#include "shift/time/Duration.hpp"
#include "shift/time/SimulationTime.hpp"
#include "shift/time/TimeTypes.hpp"

namespace
{

struct TestSystem : public shift::System
{
    explicit TestSystem(shift::time::Duration duration)
        : delta{duration}
    {
    }

    auto first_update() -> shift::UpdateResult override
    {
        was_first_update_checked = true;
        return shift::UpdateResult::schedule_now();
    }

    auto update([[maybe_unused]] shift::World& world,
                [[maybe_unused]] shift::time::Clock::TimeStep time_step)
        -> shift::UpdateResult override
    {
        static auto run_once = false;
        if (!run_once) {
            run_once = true;
            return shift::UpdateResult::schedule_after(delta);
        }

        return shift::UpdateResult::stop();
    }

    auto startup([[maybe_unused]] const shift::World& world) -> void override
    {
        was_started_up = true;
    }

    auto shutdown([[maybe_unused]] const shift::World& world) -> void override
    {
        was_shutdown = true;
    }

    shift::time::Duration delta;
    bool was_first_update_checked{};
    bool was_started_up{};
    bool was_shutdown{};
};

struct TestTelemetryRecorder : public shift::telemetry::TelemetryRecorder
{
    auto record(
        [[maybe_unused]] const shift::telemetry::TelemetryRecord& record)
        -> void override
    {
    }

    auto shutdown() -> void override { was_shutdown = true; }

    bool was_shutdown{};
};

}  // namespace

TEST_CASE("SimulationRunner run", "[core][SimulationRunner]")
{
    auto simulation = shift::Simulation{};

    auto& clock = simulation.clock();
    REQUIRE(clock.time() == shift::time::SimulationTime{});
    REQUIRE(clock.delta() == shift::time::Duration{});

    auto runner = shift::SimulationRunner{};

    constexpr auto duration = shift::time::Duration{shift::time::Seconds{1}};

    {
        auto system = std::make_unique<TestSystem>(duration);
        simulation.systems().add_system(std::move(system));
    }

    auto* system =
        dynamic_cast<TestSystem*>(simulation.systems().systems().back().get());
    REQUIRE(system != nullptr);

    auto telemetry =
        shift::telemetry::Telemetry{std::make_unique<TestTelemetryRecorder>()};
    runner.set_telemetry(&telemetry);

    runner.run(simulation,
               shift::time::SimulationTime{shift::time::Seconds{1}});

    CHECK(clock.time().get() == duration.get());
    CHECK(clock.delta() == duration);

    CHECK(system->was_first_update_checked);
    CHECK(system->was_started_up);
    CHECK(system->was_shutdown);

    CHECK(dynamic_cast<TestTelemetryRecorder*>(telemetry.recorder())
              ->was_shutdown);
}
