#pragma once

#include <iostream>
#include <span>

#include "shift/core/UUID.hpp"
#include "shift/telemetry/TelemetryRecord.hpp"

namespace shift::telemetry
{

class TelemetryRecorder
{
public:
    TelemetryRecorder() = default;
    TelemetryRecorder(const TelemetryRecorder&) = default;
    TelemetryRecorder(TelemetryRecorder&&) noexcept = default;
    virtual ~TelemetryRecorder() = default;
    auto operator=(const TelemetryRecorder&) -> TelemetryRecorder& = default;
    auto operator=(TelemetryRecorder&&) noexcept
        -> TelemetryRecorder& = default;

    virtual auto record(const TelemetryRecord& record) -> void = 0;
};

// todo: move these implementations into their own file
class ConsoleTelemetryRecorder : public TelemetryRecorder
{
public:
    auto record(const TelemetryRecord& record) -> void override
    {
        // std::println("t={} entity={} channel={} value={}",
        //              record.time,
        //              record.uuid.to_string(),
        //              record.channel,
        //              record.value);

        std::cout << "t=" << record.time.count()
                  << " entity=" << record.uuid.to_string()
                  << " channel=" << record.channel << " value=" << record.value
                  << '\n';
    }
};

class MemoryTelemetryRecorder : public TelemetryRecorder
{
public:
    auto record(const TelemetryRecord& record) -> void override
    {
        m_records.push_back(record);
    }

    auto records() const noexcept -> std::span<const TelemetryRecord>
    {
        return m_records;
    }

private:
    std::vector<TelemetryRecord> m_records;
};

}  // namespace shift::telemetry
