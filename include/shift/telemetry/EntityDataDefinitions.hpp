#pragma once

#include <string_view>

#include "shift/coordinate/CoordinateTransform.hpp"
#include "shift/coordinate/EnuFrame.hpp"
#include "shift/core/Entity.hpp"
#include "shift/telemetry/DataDefinition.hpp"

namespace shift::telemetry
{

inline constexpr DataDefinition<Entity, coordinate::EcefPosition>
    entity_position_ecef{"position_ecef",
                         [](const Entity& entity) -> coordinate::EcefPosition
                         { return entity.position(); }};

// todo: need access to world ENU frame
inline constexpr DataDefinition<Entity, coordinate::EnuPosition>
    entity_position_enu{"position_enu",
                        [](const Entity& entity) -> coordinate::EnuPosition {
                            return coordinate::to_enu(entity.position(),
                                                      coordinate::EnuFrame{});
                        }};

inline constexpr DataDefinition<Entity, double> entity_position_enu_x{
    "position_enu.east", [](const Entity& entity) -> double {
        return coordinate::to_enu(entity.position(), coordinate::EnuFrame{})
            .east;
    }};

inline constexpr DataDefinition<Entity, double> entity_position_enu_y{
    "position_enu.north", [](const Entity& entity) -> double {
        return coordinate::to_enu(entity.position(), coordinate::EnuFrame{})
            .north;
    }};

inline constexpr DataDefinition<Entity, double> entity_position_enu_z{
    "position_enu.up", [](const Entity& entity) -> double {
        return coordinate::to_enu(entity.position(), coordinate::EnuFrame{}).up;
    }};

}  // namespace shift::telemetry
