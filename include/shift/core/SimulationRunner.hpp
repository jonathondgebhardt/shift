#pragma once

#include "shift/core/Simulation.hpp"
#include "shift/core/TimeUpdater.hpp"
#include "shift/core/shift_core_export.hpp"

namespace shift
{

class SHIFT_CORE_EXPORT SimulationRunner
{
public:
    explicit SimulationRunner(std::unique_ptr<TimeUpdater> updater);

    auto run(Simulation& simulation) -> void;

private:
    std::unique_ptr<TimeUpdater> m_updater;
};

}  // namespace shift
