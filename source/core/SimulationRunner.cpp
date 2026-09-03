#include <algorithm>
#include <memory>
#include <stdexcept>
#include <utility>

#include "shift/core/Simulation.hpp"

#include "shift/core/Clock.hpp"
#include "shift/core/SimulationRunner.hpp"
#include "shift/core/System.hpp"
#include "shift/core/TimeUpdater.hpp"
#include "shift/logger/Log.hpp"

namespace shift
{

SimulationRunner::SimulationRunner(std::unique_ptr<TimeUpdater> updater)
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

    m_updater->startup();

    std::ranges::for_each(simulation.systems(),
                          [](System& system) { system.startup(); });

    shift::log::warning().append("not running zero frame");
    // record zero frame
    // if (m_telemetry != nullptr) {
    //     m_telemetry->sample({}, simulation.world());
    // }

    // todo: run until end condition is met
    auto& clock = simulation.clock();
    auto time_step = m_updater->update(clock);

    std::ranges::for_each(simulation.systems(),
                          [&](System& system)
                          { system.process(simulation.world(), time_step); });

    if (m_telemetry != nullptr) {
        m_telemetry->sample(time_step.time, simulation.world());
    }
}

}  // namespace shift
