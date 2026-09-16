#pragma once

#include <optional>

#include "shift/core/Simulation.hpp"
#include "shift/core/UpdateScheduler.hpp"
#include "shift/core/shift_core_export.hpp"
#include "shift/telemetry/Telemetry.hpp"
#include "shift/time/SimulationTime.hpp"

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

    auto set_time_limit(time::SimulationTime time_limit) -> void
    {
        m_time_limit = time_limit;
    }

private:
    telemetry::Telemetry* m_telemetry{};
    UpdateScheduler m_scheduler;
    std::optional<time::SimulationTime> m_time_limit;
};

}  // namespace shift
