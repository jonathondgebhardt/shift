#pragma once

#include <span>
#include <vector>

#include "shift/core/shift_core_export.hpp"
#include "shift/telemetry/TelemetryRecord.hpp"
#include "shift/telemetry/TelemetryRecorder.hpp"

namespace shift::telemetry
{

class SHIFT_CORE_EXPORT MemoryTelemetryRecorder : public TelemetryRecorder
{
public:
    auto record(const TelemetryRecord& record) -> void override;

    auto records() const noexcept -> std::span<const TelemetryRecord>
    {
        return m_records;
    }

private:
    std::vector<TelemetryRecord> m_records;
};

}  // namespace shift::telemetry
