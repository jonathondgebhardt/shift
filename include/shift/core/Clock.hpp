#pragma once

#include "shift/core/Object.hpp"
#include "shift/core/TimeConvert.hpp"
#include "shift/core/TimeTypes.hpp"
#include "shift/core/shift_core_export.hpp"

namespace shift
{

class SHIFT_CORE_EXPORT Clock : public Object
{
public:
    auto type() const -> const char* override { return "Clock"; }

    // todo: return m_time and m_delta?
    struct TickFrame
    {
        time::Microseconds time;
        time::Microseconds delta;
    };

    auto tick() -> TickFrame;

    template<time::TimeType T = time::Microseconds>
    auto time() const -> T
    {
        return time::convert::time_cast<T>(m_time);
    }

    template<time::TimeType T = time::Microseconds>
    auto delta() const -> T
    {
        return time::convert::time_cast<T>(m_delta);
    }

private:
    time::Microseconds m_time{};
    time::Microseconds m_delta{};
};

}  // namespace shift
