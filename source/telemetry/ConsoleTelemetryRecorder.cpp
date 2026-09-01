#include <iostream>

#include "shift/telemetry/ConsoleTelemetryRecorder.hpp"

#include "shift/core/UUID.hpp"
#include "shift/telemetry/TelemetryRecord.hpp"

namespace shift::telemetry
{

auto ConsoleTelemetryRecorder::record(const TelemetryRecord& record) -> void
{
    // std::println("t={} entity={} channel={} value={}",
    //              record.time,
    //              record.uuid.to_string(),
    //              record.channel,
    //              record.value);

    std::cout << "t=" << record.time.count()
              << " entity=" << record.uuid.to_string()
              << " channel=" << record.channel
              << " value=" << record.value.to_string() << '\n';
}

}  // namespace shift::telemetry
