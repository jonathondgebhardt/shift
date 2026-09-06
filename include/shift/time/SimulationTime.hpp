#pragma once

#include "shift/time/Duration.hpp"
#include "shift/time/TimeTypes.hpp"
#include "shift/time/shift_time_export.hpp"

namespace shift::time
{

class SHIFT_TIME_EXPORT SimulationTime
{
public:
    using SimulationTimeType = Microseconds;

    SimulationTime() = default;
    SimulationTime(const SimulationTime&) = default;
    SimulationTime(SimulationTime&&) noexcept = default;
    ~SimulationTime() = default;
    auto operator=(const SimulationTime&) -> SimulationTime& = default;
    auto operator=(SimulationTime&&) noexcept -> SimulationTime& = default;
    auto operator<=>(const SimulationTime&) const = default;
    auto operator==(const SimulationTime&) const -> bool = default;

    template<TimeType T>
    constexpr explicit SimulationTime(T time)
        : m_time{time_cast<SimulationTimeType>(time)}
    {
    }

    template<TimeType T>
    auto as() const -> T
    {
        return time_cast<T>(m_time);
    }

    auto data() const -> std::int64_t { return m_time.count(); }

    constexpr auto get() const -> SimulationTimeType { return m_time; }

    friend constexpr auto operator+(SimulationTime time, Duration duration)
        -> SimulationTime
    {
        time += duration;
        return time;
    }

    constexpr auto operator+=(Duration duration) -> SimulationTime&
    {
        m_time += duration.get();
        return *this;
    }

    friend constexpr auto operator-(SimulationTime time, Duration duration)
        -> SimulationTime
    {
        time -= duration;
        return time;
    }

    constexpr auto operator-=(Duration sim_time) -> SimulationTime&
    {
        m_time -= sim_time.get();
        return *this;
    }

    friend constexpr auto operator-(SimulationTime lhs, SimulationTime rhs)
        -> Duration
    {
        return Duration{lhs.get() - rhs.get()};
    }

    auto to_string() const -> std::string
    {
        return std::to_string(m_time.count());
    }

private:
    SHIFT_SUPPRESS_C4251
    SimulationTimeType m_time{};
};

}  // namespace shift::time
