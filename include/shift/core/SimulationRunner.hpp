#pragma once

#include "shift/core/Simulation.hpp"
#include "shift/core/shift_core_export.hpp"
#include "shift/telemetry/Telemetry.hpp"
#include "shift/time/TimeUpdater.hpp"

namespace shift
{

class SHIFT_CORE_EXPORT SimulationRunner
{
public:
    explicit SimulationRunner(std::unique_ptr<time::TimeUpdater> updater);

    auto run(Simulation& simulation) -> void;

    auto set_telemetry(telemetry::Telemetry* telemetry)
    {
        m_telemetry = telemetry;
    }

private:
    std::unique_ptr<time::TimeUpdater> m_updater;
    telemetry::Telemetry* m_telemetry{};
};

}  // namespace shift
