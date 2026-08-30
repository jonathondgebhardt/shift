#include <memory>
#include <utility>

#include "shift/core/Simulation.hpp"

#include <catch2/catch_test_macros.hpp>

#include "shift/core/Clock.hpp"
#include "shift/core/FixedTimeUpdater.hpp"
#include "shift/core/SimulationRunner.hpp"
#include "shift/core/TimeTypes.hpp"

TEST_CASE("SimulationRunner run", "[core][SimulationRunner]")
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

    runner.run(simulation);

    CHECK(clock.time() == delta);
    CHECK(clock.delta() == delta);
}
