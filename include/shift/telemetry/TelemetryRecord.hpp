#pragma once

#include <string_view>

#include "shift/core/TimeTypes.hpp"
#include "shift/core/UUID.hpp"
#include "shift/telemetry/TelemetryValue.hpp"

namespace shift::telemetry
{

struct TelemetryRecord
{
    time::Microseconds time{};
    UUID uuid;
    std::string_view channel;
    TelemetryValue value;
};

}  // namespace shift::telemetry
