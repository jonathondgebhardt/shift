#include "shift/core/RealTimeUpdater.hpp"

#include "shift/core/TimeTypes.hpp"

namespace shift
{

RealTimeUpdater::RealTimeUpdater()
{
    // todo: delay until startup?
    m_timer.reset();
}

auto RealTimeUpdater::next_time() -> time::Microseconds
{
    return m_timer.elapsed();
}

}  // namespace shift
