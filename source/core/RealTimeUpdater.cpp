#include "shift/core/RealTimeUpdater.hpp"

#include "shift/core/Clock.hpp"

namespace shift
{

RealTimeUpdater::RealTimeUpdater()
{
    // todo: this is probably too early and should wait until startup
    m_timer.reset();
}

auto RealTimeUpdater::update_impl(Clock& clock) -> void
{
    update_delta(clock, m_timer.tick());
}

}  // namespace shift
