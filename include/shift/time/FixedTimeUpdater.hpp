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
        if (m_duration.data() <= 0) {
            throw std::runtime_error(
                "cannot update time with zero or less duration");
        }
    }

    auto update_impl(Clock& clock) -> void override
    {
        update_delta(clock, m_duration);
    }

private:
    SHIFT_SUPPRESS_C4251
    Duration m_duration;
};

}  // namespace shift::time
