#include <memory>
#include <stdexcept>
#include <utility>

#include "shift/core/Simulation.hpp"

#include "shift/core/Clock.hpp"
#include "shift/core/SimulationRunner.hpp"
#include "shift/core/TimeUpdater.hpp"

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

    // todo: run until end condition is met
    auto& clock = simulation.clock();
    m_updater->update(clock);
}

}  // namespace shift
