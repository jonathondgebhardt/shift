#pragma once

#include "shift/time/Duration.hpp"
#include "shift/time/TimePoint.hpp"
#include "shift/time/shift_time_export.hpp"

namespace shift::time
{

class SHIFT_TIME_EXPORT Clock
{
public:
    struct TimeStep
    {
        TimePoint time;
        Duration delta;
    };

    auto time_step() const -> TimeStep
    {
        return TimeStep{.time = time(), .delta = delta()};
    }

    auto time() const -> TimePoint { return m_time; }

    auto delta() const -> Duration { return m_duration; }

    // todo: restrict who can call these
    auto set_time(TimePoint time) -> void;
    auto set_delta(Duration duration) -> void;

private:
    TimePoint m_time;
    Duration m_duration;
};

}  // namespace shift::time
