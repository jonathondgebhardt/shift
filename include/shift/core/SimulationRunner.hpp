#pragma once

#include "shift/core/Simulation.hpp"
#include "shift/core/UpdateScheduler.hpp"
#include "shift/core/shift_core_export.hpp"
#include "shift/telemetry/Telemetry.hpp"

namespace shift
{

class SHIFT_CORE_EXPORT SimulationRunner
{
public:
    auto run(Simulation& simulation) -> void;

    auto set_telemetry(telemetry::Telemetry* telemetry)
    {
        m_telemetry = telemetry;
    }

private:
    telemetry::Telemetry* m_telemetry{};
    UpdateScheduler m_scheduler;
};

}  // namespace shift
