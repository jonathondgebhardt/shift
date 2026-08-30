#include "shift/core/RealTimeUpdater.hpp"

#include "shift/core/TimeTypes.hpp"

namespace shift
{

RealTimeUpdater::RealTimeUpdater()
{
    m_timer.reset();
}

auto RealTimeUpdater::next_time() -> time::Microseconds
{
    return m_timer.tick();
}

}  // namespace shift
