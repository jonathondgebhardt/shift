#include <algorithm>
#include <memory>
#include <ranges>
#include <string>
#include <string_view>
#include <utility>

#include "shift/core/Object.hpp"

#include "shift/core/Component.hpp"
#include "shift/core/UUID.hpp"

namespace shift
{

auto Object::uuid() const -> UUID
{
    return m_uuid;
}

auto Object::set_name(std::string name) -> void
{
    m_name = std::move(name);
}

auto Object::add_component(std::unique_ptr<Component> component) -> bool
{
    if (!component) {
        return false;
    }

    // todo: enforce uniqueness?
    m_components.push_back(std::move(component));
    return true;
}

auto Object::has_component(UUID uuid) const -> bool
{
    return get_component(uuid) != nullptr;
}

auto Object::has_component(std::string_view name) const -> bool
{
    return get_component(name) != nullptr;
}

auto Object::get_component(UUID uuid) const -> Component*
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

auto Object::get_component(std::string_view name) const -> Component*
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
