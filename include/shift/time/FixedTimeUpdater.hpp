#pragma once

#include "shift/time/Duration.hpp"
#include "shift/time/TimeUpdater.hpp"
#include "shift/time/shift_time_export.hpp"

namespace shift::time
{

class SHIFT_TIME_EXPORT FixedTimeUpdater : public TimeUpdater
{
public:
    explicit FixedTimeUpdater(Duration duration);

    auto update_impl(Clock& clock) -> void override;

private:
    SHIFT_SUPPRESS_C4251
    Duration m_duration;
};

}  // namespace shift::time
