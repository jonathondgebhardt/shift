#pragma once

#include "shift/core/SimulationTime.hpp"
#include "shift/core/TimeConvert.hpp"
#include "shift/core/TimeTypes.hpp"
#include "shift/core/shift_core_export.hpp"

namespace shift
{

class TimeUpdater;

class SHIFT_CORE_EXPORT Clock
{
public:
    struct TimeStep
    {
        time::SimulationTime time;
        time::Microseconds delta;
    };

    auto time_step() const -> TimeStep
    {
        return TimeStep{.time = time(), .delta = delta()};
    }

    auto time() const -> time::SimulationTime { return m_time; }

    template<time::TimeType T = time::Microseconds>
    auto delta() const -> T
    {
        return time::convert::time_cast<T>(m_delta);
    }

private:
    friend class TimeUpdater;

    auto set_time(time::SimulationTime time) -> void;
    auto set_delta(time::Microseconds delta) -> void;

    time::SimulationTime m_time;
    time::Microseconds m_delta{};
};

}  // namespace shift
