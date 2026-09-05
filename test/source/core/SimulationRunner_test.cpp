#include "shift/core/Simulation.hpp"

#include <catch2/catch_test_macros.hpp>

#include "shift/core/SimulationRunner.hpp"
#include "shift/time/Clock.hpp"
#include "shift/time/TimeTypes.hpp"

TEST_CASE("SimulationRunner run", "[core][SimulationRunner]")
{
    const auto delta = shift::time::Duration{shift::time::Microseconds{10}};
    auto runner = shift::SimulationRunner{};

    auto simulation = shift::Simulation{};
    auto& clock = simulation.clock();
    REQUIRE(clock.time() == shift::time::SimulationTime{});
    REQUIRE(clock.delta() == shift::time::Duration{});

    runner.run(simulation);

    CHECK(clock.time().get() == delta.get());
    CHECK(clock.delta() == delta);
}
