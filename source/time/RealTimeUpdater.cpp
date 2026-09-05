#include "shift/time/RealTimeUpdater.hpp"

#include "shift/time/Clock.hpp"

namespace shift::time
{

auto RealTimeUpdater::startup() -> void
{
    m_timer.reset();
}

auto RealTimeUpdater::update_impl(Clock& clock) -> void
{
    update_delta(clock, m_timer.tick());
}

}  // namespace shift::time
