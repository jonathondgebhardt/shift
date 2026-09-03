#include "shift/core/Clock.hpp"

#include "shift/core/SimulationTime.hpp"
#include "shift/core/TimeTypes.hpp"

namespace shift
{

auto Clock::set_time(time::SimulationTime time) -> void
{
    m_delta = (time - m_time).as<time::Microseconds>();
    m_time = time;
}

auto Clock::set_delta(time::Microseconds delta) -> void
{
    m_delta = delta;
    m_time += delta;
}

}  // namespace shift
