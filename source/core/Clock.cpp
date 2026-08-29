#include "shift/core/Clock.hpp"

namespace shift
{

auto Clock::tick() -> TickFrame
{
    // todo: get time update component and update time
    return TickFrame{.time = m_time, .delta = m_delta};
}

}  // namespace shift
