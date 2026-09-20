#pragma once

#include <memory>
#include <ranges>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include "shift/coordinate/EcefPosition.hpp"
#include "shift/coordinate/EcefVector.hpp"
#include "shift/coordinate/EulerOrientation.hpp"
#include "shift/core/Component.hpp"
#include "shift/core/shift_core_export.hpp"

namespace shift
{

using EntityUID = std::uint64_t;

class SHIFT_CORE_EXPORT Entity
{
public:
    explicit Entity(EntityUID uid)
        : m_uid{uid}
    {
    }

    Entity() = default;
    Entity(const Entity&) = delete;
    Entity(Entity&&) = default;
    ~Entity() = default;
    auto operator=(const Entity&) -> Entity& = delete;
    auto operator=(Entity&&) noexcept -> Entity& = default;

    auto uid() const -> EntityUID;

    auto set_name(std::string name) -> void;

    auto name() const -> std::string_view { return m_name; }

    auto components() const -> std::span<const std::unique_ptr<Component>>
    {
        return m_components;
    }

    auto add_component(std::unique_ptr<Component> component) -> bool;

    template<typename T, typename... Args>
        requires std::is_base_of_v<Component, T>
    auto add_component(Args&&... args) -> bool
    {
        return add_component(std::make_unique<T>(std::forward<Args>(args)...));
    }

    auto has_component(UUID uuid) const -> bool;

    auto has_component(std::string_view name) const -> bool;

    auto find_component(UUID uuid) const -> Component*;

    auto find_component(std::string_view name) const -> Component*;

    template<typename T>
        requires std::is_base_of_v<Component, T>
    auto find_component() const -> T*
    {
        auto pipeline = m_components
            | std::views::transform(
                            [](const std::unique_ptr<Component>& component)
                            { return component.get(); })
            | std::views::filter([](const Component* component)
                                 { return component != nullptr; });

        const auto found = std::ranges::find_if(
            pipeline,
            [](Component* component)
            { return dynamic_cast<const T*>(component) != nullptr; });
        return found != pipeline.end() ? dynamic_cast<T*>(*found) : nullptr;
    }

    auto position() const -> coordinate::EcefPosition { return m_position; }

    auto position() -> coordinate::EcefPosition& { return m_position; }

    auto set_position(coordinate::EcefPosition position) -> void
    {
        m_position = position;
    }

    auto orientation() const -> coordinate::EulerOrientation
    {
        return m_orientation;
    }

    auto orientation() -> coordinate::EulerOrientation&
    {
        return m_orientation;
    }

    auto set_orientation(coordinate::EulerOrientation orientation) -> void
    {
        m_orientation = orientation;
    }

    auto velocity() const -> coordinate::EcefVector { return m_velocity; }

    auto velocity() -> coordinate::EcefVector& { return m_velocity; }

    auto set_velocity(coordinate::EcefVector velocity) -> void
    {
        m_velocity = velocity;
    }

    auto acceleration() const -> coordinate::EcefVector
    {
        return m_acceleration;
    }

    auto acceleration() -> coordinate::EcefVector& { return m_acceleration; }

    auto set_acceleration(coordinate::EcefVector acceleration) -> void
    {
        m_acceleration = acceleration;
    }

private:
    SHIFT_SUPPRESS_C4251
    std::string m_name;
    SHIFT_SUPPRESS_C4251
    std::vector<std::unique_ptr<Component>> m_components;
    coordinate::EcefPosition m_position;
    coordinate::EulerOrientation m_orientation;
    coordinate::EcefVector m_velocity;
    coordinate::EcefVector m_acceleration;
    EntityUID m_uid{};
};

}  // namespace shift
