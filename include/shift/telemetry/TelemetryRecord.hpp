#pragma once

#include <string_view>

#include "shift/core/TimeTypes.hpp"
#include "shift/core/UUID.hpp"

namespace shift::telemetry
{

struct TelemetryRecord
{
    time::Microseconds time;
    UUID uuid;
    std::string_view channel;
    double value;
};

}  // namespace shift::telemetry
