#pragma once

#include "shift/core/Clock.hpp"
#include "shift/core/TimeTypes.hpp"

namespace shift
{

class TimeUpdater
{
public:
    TimeUpdater() = default;
    TimeUpdater(const TimeUpdater&) = default;
    TimeUpdater(TimeUpdater&&) noexcept = default;
    virtual ~TimeUpdater() = default;
    auto operator=(const TimeUpdater&) -> TimeUpdater& = default;
    auto operator=(TimeUpdater&&) noexcept -> TimeUpdater& = default;

    virtual auto update(Clock& clock) -> Clock::TimeStep
    {
        update_impl(clock);
        return clock.time_step();
    }

protected:
    static auto update_time(Clock& clock, time::Microseconds time) -> void
    {
        clock.set_time(time);
    }

    static auto update_delta(Clock& clock, time::Microseconds delta) -> void
    {
        clock.set_delta(delta);
    }

private:
    virtual auto update_impl(Clock& clock) -> void = 0;
};

}  // namespace shift
