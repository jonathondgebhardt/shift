#pragma once

#include "shift/time/TimeTypes.hpp"
#include "shift/time/shift_time_export.hpp"

namespace shift::time
{

class SHIFT_TIME_EXPORT Duration
{
public:
    using DurationType = Microseconds;

    constexpr Duration() = default;
    constexpr Duration(const Duration&) = default;
    constexpr Duration(Duration&&) noexcept = default;
    constexpr ~Duration() = default;

    constexpr auto operator=(const Duration&) -> Duration& = default;
    constexpr auto operator=(Duration&&) noexcept -> Duration& = default;

    template<TimeType T>
    explicit constexpr Duration(T duration)
        : m_duration{time_cast<DurationType>(duration)}
    {
    }

    template<TimeType T>
    constexpr auto as() const -> T
    {
        return time_cast<T>(m_duration);
    }

    constexpr auto get() const -> DurationType { return m_duration; }

    constexpr auto data() const -> std::int64_t { return m_duration.count(); }

    constexpr auto operator<=>(const Duration&) const = default;

    friend constexpr auto operator+(Duration lhs, Duration rhs) -> Duration
    {
        lhs += rhs;
        return lhs;
    }

    constexpr auto operator+=(Duration duration) -> Duration&
    {
        m_duration += duration.m_duration;
        return *this;
    }

    friend constexpr auto operator-(Duration lhs, Duration rhs) -> Duration
    {
        lhs -= rhs;
        return lhs;
    }

    constexpr auto operator-=(Duration duration) -> Duration&
    {
        m_duration -= duration.m_duration;
        return *this;
    }

    auto to_string() const -> std::string { return std::to_string(data()); }

private:
    SHIFT_SUPPRESS_C4251
    DurationType m_duration{};
};

}  // namespace shift::time
