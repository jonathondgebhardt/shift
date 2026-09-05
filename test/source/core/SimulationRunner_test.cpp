#include <memory>
#include <utility>

#include "shift/core/Simulation.hpp"

#include <catch2/catch_test_macros.hpp>

#include "shift/core/SimulationRunner.hpp"
#include "shift/time/Clock.hpp"
#include "shift/time/FixedTimeUpdater.hpp"
#include "shift/time/TimeTypes.hpp"

TEST_CASE("SimulationRunner run", "[core][SimulationRunner]")
{
    const auto delta = shift::time::Duration{shift::time::Microseconds{10}};
    auto updater = std::make_unique<shift::time::FixedTimeUpdater>(delta);
    auto runner = shift::SimulationRunner{std::move(updater)};

    auto simulation = shift::Simulation{};
    auto& clock = simulation.clock();
    REQUIRE(clock.time() == shift::time::SimulationTime{});
    REQUIRE(clock.delta() == shift::time::Duration{});

    runner.run(simulation);

    CHECK(clock.time().get() == delta.get());
    CHECK(clock.delta() == delta);
}

TEST_CASE("SimulationRunner no updater", "[core][SimulationRunner]")
{
    CHECK_THROWS(shift::SimulationRunner{nullptr});
}
