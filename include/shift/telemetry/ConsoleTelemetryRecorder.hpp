#pragma once

#include "shift/core/shift_core_export.hpp"
#include "shift/telemetry/TelemetryRecord.hpp"
#include "shift/telemetry/TelemetryRecorder.hpp"

namespace shift::telemetry
{

class SHIFT_CORE_EXPORT ConsoleTelemetryRecorder : public TelemetryRecorder
{
public:
    auto record(const TelemetryRecord& record) -> void override;
};

}  // namespace shift::telemetry
