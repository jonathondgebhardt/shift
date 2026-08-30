#pragma once

#include <chrono>

#include "shift/core/TimeConvert.hpp"
#include "shift/core/TimeTypes.hpp"
#include "shift/core/shift_core_export.hpp"

namespace shift
{

template<time::TimeType T = time::Microseconds,
         time::ClockType U = std::chrono::steady_clock>
class SHIFT_CORE_EXPORT Timer
{
public:
    auto reset() -> void
    {
        m_start = U::now();
        m_last_tick = m_start;
    }

    auto elapsed() const -> T
    {
        const auto now = U::now();
        const auto elapsed = now - m_start;
        return time::convert::time_cast<T>(time::Seconds{elapsed});
    }

    auto tick() -> T
    {
        const auto now = U::now();
        const auto elapsed = now - m_last_tick;
        m_last_tick = now;
        return time::convert::time_cast<T>(time::Seconds{elapsed});
    }

private:
    U::time_point m_start;
    U::time_point m_last_tick;
};

}  // namespace shift
