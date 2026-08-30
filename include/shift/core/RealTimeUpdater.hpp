#pragma once

#include <chrono>

#include "shift/core/TimeTypes.hpp"
#include "shift/core/TimeUpdater.hpp"
#include "shift/core/Timer.hpp"
#include "shift/core/shift_core_export.hpp"

namespace shift
{

class SHIFT_CORE_EXPORT RealTimeUpdater : public TimeUpdater
{
public:
    RealTimeUpdater();

    auto update_impl(Clock& clock) -> void override;

private:
    Timer<time::Microseconds, std::chrono::high_resolution_clock> m_timer;
};

}  // namespace shift
