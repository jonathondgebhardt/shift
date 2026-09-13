#include <stdexcept>

#include "shift/time/FixedTimeUpdater.hpp"

#include "shift/time/Clock.hpp"
#include "shift/time/Duration.hpp"

namespace shift::time
{

FixedTimeUpdater::FixedTimeUpdater(const Duration duration)
    : m_duration{duration}
{
    if (m_duration.data() <= 0) {
        throw std::runtime_error(
            "cannot update time with zero or less duration");
    }
}

auto FixedTimeUpdater::update_impl(Clock& clock) -> void
{
    update_delta(clock, m_duration);
}

}  // namespace shift::time
