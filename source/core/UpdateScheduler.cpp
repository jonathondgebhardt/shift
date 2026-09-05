#include <optional>
#include <queue>
#include <stdexcept>
#include <vector>

#include "shift/core/UpdateScheduler.hpp"

#include "shift/core/System.hpp"
#include "shift/time/SimulationTime.hpp"

namespace shift
{

auto UpdateScheduler::schedule(const System& system,
                               time::SimulationTime time) -> void
{
    if (system.uid() == shift::SystemUID{}) {
        throw std::runtime_error("cannot schedule system with invalid UID");
    }

    m_events.emplace(UpdateEvent{.uid = system.uid(), .time = time});
}

auto UpdateScheduler::top() const -> std::optional<UpdateEvent>
{
    if (empty()) {
        return {};
    }

    return m_events.top();
}

auto UpdateScheduler::pop() -> void
{
    if (const auto update_event = top(); update_event) {
        m_processed.emplace_back(*update_event);
        m_events.pop();
    }
}

}  // namespace shift
