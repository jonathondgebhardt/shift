#pragma once

#include <string_view>

#include "shift/core/Entity.hpp"
#include "shift/telemetry/TelemetryValue.hpp"
#include "shift/time/SimulationTime.hpp"

namespace shift::telemetry
{

struct TelemetryRecord
{
    time::SimulationTime time;
    EntityUID uid{};
    std::string_view channel;
    TelemetryValue value;
};

}  // namespace shift::telemetry
