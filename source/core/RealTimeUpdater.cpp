#include "shift/core/RealTimeUpdater.hpp"

#include "shift/core/Clock.hpp"

namespace shift
{

auto RealTimeUpdater::startup() -> void
{
    m_timer.reset();
}

auto RealTimeUpdater::update_impl(Clock& clock) -> void
{
    update_delta(clock, m_timer.tick());
}

}  // namespace shift
