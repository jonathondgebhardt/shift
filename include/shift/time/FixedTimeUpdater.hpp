#pragma once

#include "shift/time/Duration.hpp"
#include "shift/time/TimeUpdater.hpp"
#include "shift/time/shift_time_export.hpp"

namespace shift::time
{

class SHIFT_TIME_EXPORT FixedTimeUpdater : public TimeUpdater
{
public:
    explicit FixedTimeUpdater(Duration duration)
        : m_duration{duration}
    {
        // todo: ensure m_delta > 0?
    }

    auto update_impl(Clock& clock) -> void override
    {
        update_delta(clock, m_duration);
    }

private:
    Duration m_duration;
};

}  // namespace shift::time
