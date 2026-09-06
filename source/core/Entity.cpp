#include <algorithm>
#include <memory>
#include <ranges>
#include <string>
#include <string_view>
#include <utility>

#include "shift/core/Entity.hpp"

#include "shift/core/Component.hpp"
#include "shift/core/UUID.hpp"

namespace shift
{

auto Entity::uid() const -> EntityUID
{
    return m_uid;
}

auto Entity::set_name(std::string name) -> void
{
    m_name = std::move(name);
}

auto Entity::add_component(std::unique_ptr<Component> component) -> bool
{
    if (!component) {
        return false;
    }

    // todo: enforce uniqueness?
    m_components.push_back(std::move(component));
    return true;
}

auto Entity::has_component(UUID uuid) const -> bool
{
    return find_component(uuid) != nullptr;
}

auto Entity::has_component(std::string_view name) const -> bool
{
    return find_component(name) != nullptr;
}

auto Entity::find_component(UUID uuid) const -> Component*
{
    auto pipeline = m_components
        | std::views::transform([](const std::unique_ptr<Component>& component)
                                { return component.get(); })
        | std::views::filter([](const Component* component)
                             { return component != nullptr; });

    const auto found =
        std::ranges::find_if(pipeline,
                             [&uuid](const Component* component)
                             { return component->uuid() == uuid; });
    return found != pipeline.end() ? *found : nullptr;
}

auto Entity::find_component(std::string_view name) const -> Component*
{
    auto pipeline = m_components
        | std::views::transform([](const std::unique_ptr<Component>& component)
                                { return component.get(); })
        | std::views::filter([](const Component* component)
                             { return component != nullptr; });

    const auto found =
        std::ranges::find_if(pipeline,
                             [&name](const Component* component)
                             { return component->name() == name; });
    return found != pipeline.end() ? *found : nullptr;
}

}  // namespace shift
