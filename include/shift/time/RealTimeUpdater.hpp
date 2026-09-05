#pragma once

#include <chrono>

#include "shift/time/TimeUpdater.hpp"
#include "shift/time/Timer.hpp"
#include "shift/time/shift_time_export.hpp"

namespace shift::time
{

class SHIFT_TIME_EXPORT RealTimeUpdater : public TimeUpdater
{
public:
    auto startup() -> void override;

    auto update_impl(Clock& clock) -> void override;

private:
    Timer<std::chrono::high_resolution_clock> m_timer;
};

}  // namespace shift::time
