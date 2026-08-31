#pragma once

#include <optional>
#include <span>
#include <vector>

#include "shift/core/Entity.hpp"
#include "shift/core/UUID.hpp"
#include "shift/core/shift_core_export.hpp"

namespace shift
{

class SHIFT_CORE_EXPORT World
{
public:
    // c++26 adds std::optional<T&>
    // todo: interacting with OptionalEntityReference is cumbersome, add
    // convenience OptionalReference?
    using OptionalEntityReference =
        std::optional<std::reference_wrapper<Entity>>;
    auto find_entity(UUID uuid) -> OptionalEntityReference;
    auto find_entity(std::string_view name) -> OptionalEntityReference;

    auto entities() const -> std::span<const Entity> { return m_entities; }

    auto add_entity(Entity entity) -> void;

    auto remove_entity(UUID uuid) -> bool;
    auto remove_entity(std::string_view name) -> bool;

private:
    std::vector<Entity> m_entities;
};

}  // namespace shift
