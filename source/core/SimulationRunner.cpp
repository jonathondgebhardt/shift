#include <algorithm>
#include <memory>
#include <stdexcept>
#include <utility>

#include "shift/core/Simulation.hpp"

#include "shift/core/SimulationRunner.hpp"
#include "shift/core/System.hpp"
#include "shift/logger/Log.hpp"
#include "shift/time/Clock.hpp"
#include "shift/time/TimeUpdater.hpp"

namespace shift
{

SimulationRunner::SimulationRunner(std::unique_ptr<time::TimeUpdater> updater)
    : m_updater{std::move(updater)}
{
    if (m_updater == nullptr) {
        throw std::runtime_error(
            "SimulationRunner must have valid TimeUpdater");
    }
}

auto SimulationRunner::run(Simulation& simulation) -> void
{
    if (m_updater == nullptr) {
        throw std::runtime_error("cannot run Simulation without TimeUpdater");
    }

    shift::log::trace().append("starting up time updater");
    m_updater->startup();

    shift::log::trace().append("starting up systems");
    std::ranges::for_each(
        simulation.systems(),
        // todo: pass entire simulation? maybe world and services?
        [](System& system) { system.startup(); });

    shift::log::warning().append("not running zero frame");
    shift::log::trace().append("sampling world");
    // record zero frame
    // if (m_telemetry != nullptr) {
    //     m_telemetry->sample({}, simulation.world());
    // }

    shift::log::trace().append("running simulation");
    auto& clock = simulation.clock();
    auto time_step = m_updater->update(clock);

    std::ranges::for_each(
        simulation.systems(),
        [&](System& system)
        // todo: pass entire simulation? maybe world and services?
        { system.process(simulation.world(), time_step); });

    if (m_telemetry != nullptr) {
        m_telemetry->sample(time_step.time, simulation.world());
    }

    // todo: run until end condition is met

    shift::log::trace().append("shutting down simulation");
}

}  // namespace shift
