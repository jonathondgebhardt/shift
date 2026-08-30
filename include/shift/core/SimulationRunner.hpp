#pragma once

#include "shift/core/Simulation.hpp"
#include "shift/core/TimeUpdater.hpp"
#include "shift/core/shift_core_export.hpp"

namespace shift
{

class SHIFT_CORE_EXPORT SimulationRunner
{
public:
    SimulationRunner(Simulation simulation,
                     std::unique_ptr<TimeUpdater> updater);

    auto run() -> void;

    auto simulation() -> Simulation& { return m_simulation; }

private:
    Simulation m_simulation;
    std::unique_ptr<TimeUpdater> m_updater;
};

}  // namespace shift
