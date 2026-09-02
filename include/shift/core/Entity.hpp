#pragma once

#include <memory>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include "shift/core/Component.hpp"
#include "shift/core/UUID.hpp"
#include "shift/core/shift_core_export.hpp"

// todo: move this somewhere better
struct Vec3
{
    double x{};
    double y{};
    double z{};
};

namespace shift
{

class SHIFT_CORE_EXPORT Entity
{
public:
    auto uuid() const -> UUID;

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

    auto get_component(UUID uuid) const -> Component*;

    auto get_component(std::string_view name) const -> Component*;

    auto position() const -> Vec3 { return m_position; }

    auto position() -> Vec3& { return m_position; }

    auto set_position(Vec3 position) -> void { m_position = position; }

private:
    SHIFT_SUPPRESS_C4251
    std::string m_name;
    std::vector<std::unique_ptr<Component>> m_components;
    UUID m_uuid{UUID::build()};
    Vec3 m_position;
};

}  // namespace shift
