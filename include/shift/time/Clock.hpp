#pragma once

#include "shift/time/Duration.hpp"
#include "shift/time/SimulationTime.hpp"
#include "shift/time/shift_time_export.hpp"

namespace shift::time
{

class SHIFT_TIME_EXPORT Clock
{
public:
    struct TimeStep
    {
        SimulationTime time;
        Duration delta;
    };

    auto time_step() const -> TimeStep
    {
        return TimeStep{.time = time(), .delta = delta()};
    }

    auto time() const -> SimulationTime { return m_time; }

    auto delta() const -> Duration { return m_duration; }

    // todo: restrict who can call these
    auto set_time(SimulationTime time) -> void;
    auto set_delta(Duration duration) -> void;

private:
    SimulationTime m_time;
    Duration m_duration;
};

}  // namespace shift::time
