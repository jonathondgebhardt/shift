#pragma once

#include <chrono>

namespace shift::time
{

using Microseconds = std::chrono::microseconds;
using Milliseconds = std::chrono::milliseconds;
using Seconds = std::chrono::seconds;
using Minutes = std::chrono::minutes;
using Hours = std::chrono::hours;
using Days = std::chrono::days;

template<typename T, typename... U>
concept is_any_of = (std::same_as<T, U> || ...);

// todo: relax constraint to T being std::chrono::duration?
template<typename T>
concept TimeType =
    is_any_of<T, Microseconds, Milliseconds, Seconds, Minutes, Hours, Days>;

// todo: constrain U to std::chrono::duration?
template<TimeType T, typename U>
constexpr auto time_cast(U time) -> T
{
    return std::chrono::duration_cast<T>(time);
}

template<typename T>
concept ClockType = is_any_of<T,
                              std::chrono::high_resolution_clock,
                              std::chrono::steady_clock,
                              std::chrono::system_clock>;

}  // namespace shift::time
