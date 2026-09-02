#pragma once

#include <optional>

#include "shift/core/Entity.hpp"
#include "shift/core/shift_core_export.hpp"

namespace shift
{

class SHIFT_CORE_EXPORT OptionalEntityReference
{
public:
    // c++26 adds std::optional<T&>
    using OER = std::optional<std::reference_wrapper<Entity>>;

    explicit OptionalEntityReference(shift::Entity& entity)
        : m_entity{std::ref(entity)}
    {
    }

    OptionalEntityReference() = default;

    auto unwrap() -> Entity&;
    auto unwrap() const -> const Entity&;
    auto try_unwrap() -> Entity&;
    auto try_unwrap() const -> const Entity&;

    auto empty() const -> bool;

private:
    OER m_entity;
};

}  // namespace shift
