#include <memory>
#include <stdexcept>
#include <utility>

#include "shift/core/Clock.hpp"

#include "shift/core/TimeUpdater.hpp"

namespace shift
{

auto Clock::set_updater(std::unique_ptr<TimeUpdater> updater)
{
    m_updater = std::move(updater);
}

auto Clock::tick() -> TickFrame
{
    // todo: make TimeUpdater a proper member of this class since it's required?
    if (m_updater == nullptr) {
        // todo: create shift::Exception?
        throw std::runtime_error("cannot tick without updater");
    }

    // todo: how would something like this work when the updater needs to
    // determine the next time based on the simulations that are being run?
    // the current interface assumes the time updater is completely
    // self-contained.
    const auto next_time = m_updater->next_time();
    m_delta = next_time - m_time;
    m_time = next_time;

    return TickFrame{.time = m_time, .delta = m_delta};
}

}  // namespace shift
