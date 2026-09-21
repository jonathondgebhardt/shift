#pragma once

#include <optional>
#include <queue>
#include <span>
#include <vector>

#include <shift/time/shift_time_export.hpp>

#include "shift/core/System.hpp"
#include "shift/core/shift_core_export.hpp"
#include "shift/time/TimePoint.hpp"

namespace shift
{

// todo: this doesn't allow control of which events are executed if they occur
// at the same time
struct UpdateEvent
{
    constexpr auto operator==(const UpdateEvent& other) const -> bool
    {
        return time == other.time;
    }

    constexpr auto operator>(const UpdateEvent& other) const -> bool
    {
        return time > other.time;
    }

    constexpr auto operator>=(const UpdateEvent& other) const -> bool
    {
        return operator>(other) || operator==(other);
    }

    constexpr auto operator<(const UpdateEvent& other) const -> bool
    {
        return time < other.time;
    }

    constexpr auto operator<=(const UpdateEvent& other) const -> bool
    {
        return operator<(other) || operator==(other);
    }

    SystemUID uid{};
    time::TimePoint time;
};

class SHIFT_CORE_EXPORT UpdateScheduler
{
public:
    auto schedule(const System& system, time::TimePoint time) -> void;

    auto empty() const -> bool { return m_events.empty(); }

    auto top() const -> std::optional<UpdateEvent>;

    auto pop() -> void;

    auto processed() -> std::span<const UpdateEvent> { return m_processed; }

private:
    std::priority_queue<UpdateEvent, std::vector<UpdateEvent>, std::greater<>>
        SHIFT_SUPPRESS_C4251 m_events;
    SHIFT_SUPPRESS_C4251
    std::vector<UpdateEvent> m_processed;
};

}  // namespace shift
