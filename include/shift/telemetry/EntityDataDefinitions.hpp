#pragma once

#include "shift/core/Entity.hpp"
#include "shift/math/Vec3.hpp"
#include "shift/telemetry/DataDefinition.hpp"

namespace shift::telemetry
{

inline constexpr DataDefinition<Entity, math::Vec3> entity_position{
    "position", [](const Entity& entity) -> std::optional<math::Vec3> {
        return entity.position();
    }};

inline constexpr DataDefinition<Entity, double> entity_position_x{
    "position.x", [](const Entity& entity) -> std::optional<double> {
        return entity.position().x;
    }};

inline constexpr DataDefinition<Entity, double> entity_position_y{
    "position.y", [](const Entity& entity) -> std::optional<double> {
        return entity.position().y;
    }};

inline constexpr DataDefinition<Entity, double> entity_position_z{
    "position.z", [](const Entity& entity) -> std::optional<double> {
        return entity.position().z;
    }};

}  // namespace shift::telemetry
