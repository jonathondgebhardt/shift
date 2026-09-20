#include <memory>
#include <utility>

#include "shift/core/Simulation.hpp"

#include <catch2/catch_test_macros.hpp>

#include "shift/core/SimulationRunner.hpp"
#include "shift/core/System.hpp"
#include "shift/core/Systems.hpp"
#include "shift/core/UpdateResult.hpp"
#include "shift/core/World.hpp"
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

    shift::time::Duration delta;
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
    auto system = std::make_unique<TestSystem>(duration);
    simulation.systems().add_system(std::move(system));

    runner.run(simulation,
               shift::time::SimulationTime{shift::time::Seconds{1}});

    CHECK(clock.time().get() == duration.get());
    CHECK(clock.delta() == duration);
}
