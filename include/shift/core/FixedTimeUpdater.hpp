#pragma once

#include "shift/core/TimeUpdater.hpp"
#include "shift/core/shift_core_export.hpp"

namespace shift
{

template<time::TimeType T>
class SHIFT_CORE_EXPORT FixedTimeUpdater : public TimeUpdater
{
public:
    explicit FixedTimeUpdater(T delta)
        : m_delta{delta}
    {
        // todo: ensure m_delta > 0?
    }

    auto update_impl(Clock& clock) -> void override
    {
        update_delta(clock, m_delta);
    }

private:
    T m_delta;
};

}  // namespace shift
