#pragma once

#include <optional>
#include <span>
#include <vector>

#include "shift/core/Entity.hpp"
#include "shift/core/OptionalEntityReference.hpp"
#include "shift/core/shift_core_export.hpp"

namespace shift
{

class SHIFT_CORE_EXPORT World
{
public:
    auto find_entity(EntityUID uid) -> OptionalEntityReference;
    auto find_entity(std::string_view name) -> OptionalEntityReference;

    auto entities() const -> std::span<const Entity> { return m_entities; }

    auto add_entity() -> Entity&;

    auto remove_entity(EntityUID uid) -> bool;
    auto remove_entity(std::string_view name) -> bool;

private:
    std::vector<Entity> m_entities;
};

}  // namespace shift
