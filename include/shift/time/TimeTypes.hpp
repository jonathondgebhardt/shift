#pragma once

#include <chrono>

namespace shift::time
{

namespace detail
{

template<typename T, typename... U>
concept is_any_of = (std::same_as<T, U> || ...);

constexpr auto seconds_to_minutes = 60;
constexpr auto seconds_to_hours = seconds_to_minutes * 60;
constexpr auto seconds_to_days = seconds_to_hours * 24;

}  // namespace detail

using Microseconds = std::chrono::microseconds;
using Milliseconds = std::chrono::milliseconds;
using Seconds = std::chrono::duration<double>;
using Minutes =
    std::chrono::duration<double, std::ratio<detail::seconds_to_minutes>>;
using Hours =
    std::chrono::duration<double, std::ratio<detail::seconds_to_hours>>;
using Days = std::chrono::duration<double, std::ratio<detail::seconds_to_days>>;

// todo: relax constraint to T being std::chrono::duration?
template<typename T>
concept TimeType = detail::
    is_any_of<T, Microseconds, Milliseconds, Seconds, Minutes, Hours, Days>;

// todo: constrain U to std::chrono::duration?
template<TimeType T, typename U>
constexpr auto time_cast(U time) -> T
{
    return std::chrono::duration_cast<T>(time);
}

template<typename T>
concept ClockType = detail::is_any_of<T,
                                      std::chrono::high_resolution_clock,
                                      std::chrono::steady_clock,
                                      std::chrono::system_clock>;

}  // namespace shift::time
