#pragma once

#include <memory>
#include <span>
#include <vector>

#include "shift/coordinate/EnuFrame.hpp"
#include "shift/core/Entity.hpp"
#include "shift/core/shift_core_export.hpp"

namespace shift
{

class SHIFT_CORE_EXPORT World
{
public:
    World() = default;
    World(const World&) = delete;
    World(World&&) noexcept = default;
    ~World() = default;
    auto operator=(const World&) -> World& = delete;
    auto operator=(World&&) noexcept -> World& = default;

    auto find_entity(EntityUID uid) const -> Entity*;
    auto find_entity(std::string_view name) const -> Entity*;

    auto entities() const -> std::span<const std::unique_ptr<Entity>>
    {
        return m_entities;
    }

    auto add_entity() -> Entity*;

    auto remove_entity(EntityUID uid) -> bool;
    auto remove_entity(std::string_view name) -> bool;

    auto reference_frame() const -> coordinate::EnuFrame
    {
        return m_reference_frame;
    }

    auto set_reference_frame(coordinate::EnuFrame reference_frame) -> void
    {
        m_reference_frame = reference_frame;
    }

private:
    SHIFT_SUPPRESS_C4251
    std::vector<std::unique_ptr<Entity>> m_entities;

    // todo: move to Environment
    coordinate::EnuFrame m_reference_frame;
};

}  // namespace shift
