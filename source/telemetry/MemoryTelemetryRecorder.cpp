#include <vector>

#include "shift/telemetry/MemoryTelemetryRecorder.hpp"

#include "shift/telemetry/TelemetryRecord.hpp"

namespace shift::telemetry
{

auto MemoryTelemetryRecorder::record(const TelemetryRecord& record) -> void
{
    m_records.push_back(record);
}

}  // namespace shift::telemetry
