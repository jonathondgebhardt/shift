#pragma once

#include "shift/telemetry/TelemetryRecord.hpp"
#include "shift/telemetry/TelemetryRecorder.hpp"

namespace shift::telemetry
{

class ConsoleTelemetryRecorder : public TelemetryRecorder
{
public:
    auto record(const TelemetryRecord& record) -> void override;
};

}  // namespace shift::telemetry
