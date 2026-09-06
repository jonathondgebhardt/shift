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
#include "shift/time/TimeTypes.hpp"

namespace
{

class TestSystem : public shift::System
{
public:
    explicit TestSystem(shift::time::Duration duration)
        : m_duration{duration}
    {
    }

    auto first_update() -> shift::UpdateResult override
    {
        return shift::UpdateResult::schedule_now();
    }

    auto process([[maybe_unused]] shift::World& world,
                 [[maybe_unused]] shift::time::Clock::TimeStep time_step)
        -> shift::UpdateResult override
    {
        static auto run_once = false;
        if (!run_once) {
            run_once = true;
            return shift::UpdateResult::schedule_after(m_duration);
        }

        return shift::UpdateResult::stop();
    }

private:
    shift::time::Duration m_duration;
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

    runner.run(simulation);

    CHECK(clock.time().get() == duration.get());
    CHECK(clock.delta() == duration);
}
