#pragma once

#include "shift/core/shift_core_export.hpp"
#include "shift/telemetry/TelemetryRecord.hpp"

namespace shift::telemetry
{

class SHIFT_CORE_EXPORT TelemetryRecorder
{
public:
    TelemetryRecorder() = default;
    TelemetryRecorder(const TelemetryRecorder&) = default;
    TelemetryRecorder(TelemetryRecorder&&) noexcept = default;
    virtual ~TelemetryRecorder() = default;
    auto operator=(const TelemetryRecorder&) -> TelemetryRecorder& = default;
    auto operator=(TelemetryRecorder&&) noexcept -> TelemetryRecorder& =
                                                        default;

    virtual auto record(const TelemetryRecord& record) -> void = 0;
};

}  // namespace shift::telemetry
