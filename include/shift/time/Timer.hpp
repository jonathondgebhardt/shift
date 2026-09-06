#pragma once

#include <chrono>

#include "shift/time/Duration.hpp"
#include "shift/time/TimeTypes.hpp"
#include "shift/time/shift_time_export.hpp"

namespace shift::time
{

template<time::ClockType T = std::chrono::steady_clock>
class SHIFT_TIME_EXPORT Timer
{
public:
    auto reset() -> void
    {
        m_start = T::now();
        m_last_tick = m_start;
    }

    auto elapsed() const -> Duration
    {
        return time::Duration{
            time_cast<Duration::DurationType>(T::now() - m_start)};
    }

    auto tick() -> Duration
    {
        const auto now = T::now();
        const auto elapsed =
            Duration{time_cast<Duration::DurationType>(now - m_last_tick)};
        m_last_tick = now;
        return elapsed;
    }

private:
    SHIFT_SUPPRESS_C4251
    T::time_point m_start;
    T::time_point m_last_tick;
};

}  // namespace shift::time
