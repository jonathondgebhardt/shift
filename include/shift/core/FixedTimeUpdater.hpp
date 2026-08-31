#pragma once

#include "shift/core/TimeConvert.hpp"
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
        update_delta(clock,
                     time::convert::time_cast<time::Microseconds>(m_delta));
    }

private:
    T m_delta;
};

}  // namespace shift
