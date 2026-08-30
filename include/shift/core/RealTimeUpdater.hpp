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

    auto type() const -> const char* override { return "RealTimeUpdater"; }

    auto next_time() -> time::Microseconds override;

private:
    Timer<time::Microseconds, std::chrono::high_resolution_clock> m_timer;
};

}  // namespace shift
