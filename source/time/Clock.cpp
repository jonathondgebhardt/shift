#include "shift/time/Clock.hpp"

#include "shift/time/Duration.hpp"
#include "shift/time/SimulationTime.hpp"

namespace shift::time
{

auto Clock::set_time(SimulationTime time) -> void
{
    m_duration = time - m_time;
    m_time = time;
}

auto Clock::set_delta(Duration duration) -> void
{
    m_duration = duration;
    m_time += duration;
}

}  // namespace shift::time
