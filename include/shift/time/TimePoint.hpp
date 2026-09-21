#pragma once

#include "shift/time/Duration.hpp"
#include "shift/time/TimeTypes.hpp"
#include "shift/time/shift_time_export.hpp"

namespace shift::time
{

class SHIFT_TIME_EXPORT TimePoint
{
public:
    using TimePointType = Microseconds;

    TimePoint() = default;
    TimePoint(const TimePoint&) = default;
    TimePoint(TimePoint&&) noexcept = default;
    ~TimePoint() = default;
    auto operator=(const TimePoint&) -> TimePoint& = default;
    auto operator=(TimePoint&&) noexcept -> TimePoint& = default;
    auto operator<=>(const TimePoint&) const = default;
    auto operator==(const TimePoint&) const -> bool = default;

    template<TimeType T>
    constexpr explicit TimePoint(T time)
        : m_time{time_cast<TimePointType>(time)}
    {
    }

    template<TimeType T>
    auto as() const -> T
    {
        return time_cast<T>(m_time);
    }

    auto data() const -> std::int64_t { return m_time.count(); }

    constexpr auto get() const -> TimePointType { return m_time; }

    friend constexpr auto operator+(TimePoint time,
                                    Duration duration) -> TimePoint
    {
        time += duration;
        return time;
    }

    constexpr auto operator+=(Duration duration) -> TimePoint&
    {
        m_time += duration.get();
        return *this;
    }

    friend constexpr auto operator-(TimePoint time,
                                    Duration duration) -> TimePoint
    {
        time -= duration;
        return time;
    }

    constexpr auto operator-=(Duration sim_time) -> TimePoint&
    {
        m_time -= sim_time.get();
        return *this;
    }

    friend constexpr auto operator-(TimePoint lhs, TimePoint rhs) -> Duration
    {
        return Duration{lhs.get() - rhs.get()};
    }

    auto to_string() const -> std::string;

private:
    SHIFT_SUPPRESS_C4251
    TimePointType m_time{};
};

}  // namespace shift::time
