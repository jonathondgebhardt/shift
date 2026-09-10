#pragma once

#include "shift/coordinate/Coordinate.hpp"
#include "shift/coordinate/shift_coordinate_export.hpp"

namespace shift::coordinate
{

SHIFT_COORDINATE_EXPORT auto to_geodetic(EcefPosition position)
    -> GeodeticPosition;

SHIFT_COORDINATE_EXPORT auto to_geodetic(EnuPosition position, EnuFrame frame)
    -> GeodeticPosition;

SHIFT_COORDINATE_EXPORT auto to_ecef(GeodeticPosition position) -> EcefPosition;

SHIFT_COORDINATE_EXPORT auto to_ecef(EnuPosition position, EnuFrame frame)
    -> EcefPosition;

SHIFT_COORDINATE_EXPORT auto to_ecef(EnuVector vector, const EnuFrame& frame)
    -> EcefVector;

SHIFT_COORDINATE_EXPORT auto to_enu(GeodeticPosition position, EnuFrame frame)
    -> EnuPosition;

SHIFT_COORDINATE_EXPORT auto to_enu(EcefPosition position, EnuFrame frame)
    -> EnuPosition;

SHIFT_COORDINATE_EXPORT auto to_enu(EcefVector vector, EnuFrame frame)
    -> EnuVector;

}  // namespace shift::coordinate
