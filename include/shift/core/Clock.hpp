#pragma once

#include "shift/core/TimeConvert.hpp"
#include "shift/core/TimeTypes.hpp"
#include "shift/core/TimeUpdater.hpp"
#include "shift/core/shift_core_export.hpp"

namespace shift
{

class SHIFT_CORE_EXPORT Clock
{
public:
    struct TimeStep
    {
        time::Microseconds time;
        time::Microseconds delta;
    };

    auto time_step() const -> TimeStep
    {
        return TimeStep{.time = time(), .delta = delta()};
    }

    template<time::TimeType T = time::Microseconds>
    auto time() const -> T
    {
        return time::convert::time_cast<T>(m_time);
    }

    template<time::TimeType T = time::Microseconds>
    auto delta() const -> T
    {
        return time::convert::time_cast<T>(m_delta);
    }

private:
    friend class TimeUpdater;

    auto set_time(time::Microseconds time) -> void;
    auto advance(time::Microseconds delta) -> void;

    time::Microseconds m_time{};
    time::Microseconds m_delta{};
};

}  // namespace shift
