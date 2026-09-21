#pragma once

#include "shift/core/Simulation.hpp"
#include "shift/core/UpdateScheduler.hpp"
#include "shift/core/shift_core_export.hpp"
#include "shift/telemetry/Telemetry.hpp"
#include "shift/time/TimePoint.hpp"

namespace shift
{

class SHIFT_CORE_EXPORT SimulationRunner
{
public:
    auto run(Simulation& simulation, time::TimePoint time_limit) -> void;

    auto set_telemetry(telemetry::Telemetry* telemetry)
    {
        m_telemetry = telemetry;
    }

private:
    telemetry::Telemetry* m_telemetry{};
    UpdateScheduler m_scheduler;
};

}  // namespace shift
