#include <algorithm>
#include <memory>
#include <ranges>
#include <stdexcept>

#include "shift/core/Clock.hpp"

#include "shift/core/Component.hpp"
#include "shift/core/TimeUpdater.hpp"

namespace
{

// todo: add get_component<T>()?
auto get_updater(const shift::Clock& clock) -> shift::TimeUpdater*
{
    auto pipeline = clock.components()
        | std::views::transform(
                        [](const std::unique_ptr<shift::Component>& component)
                        { return component.get(); })
        | std::views::filter([](const shift::Component* component)
                             { return component != nullptr; });
    auto found = std::ranges::find_if(
        pipeline,
        [](shift::Component* component)
        { return dynamic_cast<shift::TimeUpdater*>(component) != nullptr; });
    return found != pipeline.end() ? dynamic_cast<shift::TimeUpdater*>(*found)
                                   : nullptr;
}

}  // namespace

namespace shift
{

auto Clock::tick() -> TickFrame
{
    // todo: make TimeUpdater a proper member of this class since it's required?
    auto* updater = get_updater(*this);
    if (updater == nullptr) {
        // todo: create shift::Exception?
        throw std::runtime_error("cannot tick without updater");
    }

    const auto next_time = updater->next_time();
    m_delta = next_time - m_time;
    m_time = next_time;

    return TickFrame{.time = m_time, .delta = m_delta};
}

}  // namespace shift
