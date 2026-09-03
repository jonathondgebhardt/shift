#pragma once

#include "shift/core/TimeConvert.hpp"
#include "shift/core/TimeTypes.hpp"
#include "shift/core/shift_core_export.hpp"

namespace shift::time
{

class SHIFT_CORE_EXPORT SimulationTime
{
public:
    using SimulationTimeType = Microseconds;

    template<TimeType T>
    explicit SimulationTime(T time)
        : m_time{convert::time_cast<SimulationTimeType>(time)}
    {
    }

    template<TimeType T>
    auto operator==(T time) const -> bool
    {
        return m_time == convert::time_cast<SimulationTimeType>(time);
    }

    template<TimeType T>
    auto as() const -> T
    {
        return convert::time_cast<T>(m_time);
    }

    template<TimeType T>
    friend auto operator+(SimulationTime lhs, T rhs) -> SimulationTime
    {
        lhs += rhs;
        return lhs;
    }

    friend auto operator+(SimulationTime lhs, SimulationTime rhs)
        -> SimulationTime
    {
        lhs += rhs;
        return lhs;
    }

    template<TimeType T>
    auto operator+=(T time) -> SimulationTime&
    {
        return operator+=(SimulationTime{time});
    }

    auto operator+=(SimulationTime sim_time) -> SimulationTime&
    {
        m_time += sim_time.m_time;
        return *this;
    }

    template<TimeType T>
    friend auto operator-(SimulationTime lhs, T rhs) -> SimulationTime
    {
        lhs -= rhs;
        return lhs;
    }

    friend auto operator-(SimulationTime lhs, SimulationTime rhs)
        -> SimulationTime
    {
        lhs -= rhs;
        return lhs;
    }

    template<TimeType T>
    auto operator-=(T time) -> SimulationTime&
    {
        return operator-=(SimulationTime{time});
    }

    auto operator-=(SimulationTime sim_time) -> SimulationTime&
    {
        m_time -= sim_time.m_time;
        return *this;
    }

private:
    SimulationTimeType m_time{};
};

}  // namespace shift::time
