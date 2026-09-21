#pragma once

#include <string_view>

#include "shift/core/Entity.hpp"
#include "shift/telemetry/TelemetryValue.hpp"
#include "shift/time/TimePoint.hpp"

namespace shift::telemetry
{

struct TelemetryRecord
{
    time::TimePoint time;
    EntityUID uid{};
    std::string_view channel;
    TelemetryValue value;
};

}  // namespace shift::telemetry
