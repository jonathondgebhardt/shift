#pragma once

#include <string_view>

#include "shift/core/Entity.hpp"
#include "shift/core/SimulationTime.hpp"
#include "shift/telemetry/TelemetryValue.hpp"

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
