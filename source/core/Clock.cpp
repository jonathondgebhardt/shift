#include "shift/core/Clock.hpp"

#include "shift/core/TimeTypes.hpp"

namespace shift
{

auto Clock::set_time(time::Microseconds time) -> void
{
    m_delta = time - m_time;
    m_time = time;
}

auto Clock::advance(time::Microseconds delta) -> void
{
    m_delta = delta;
    m_time += delta;
}

}  // namespace shift
