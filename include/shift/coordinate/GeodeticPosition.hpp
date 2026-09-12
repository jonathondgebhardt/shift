#pragma once

#include <string>

#include "shift/coordinate/shift_coordinate_export.hpp"
#include "shift/math/Utilities.hpp"

namespace shift::coordinate
{

class SHIFT_COORDINATE_EXPORT GeodeticPosition
{
public:
    constexpr GeodeticPosition() = default;

    GeodeticPosition(double latitude, double longitude);

    GeodeticPosition(double latitude, double longitude, double altitude);

    constexpr auto operator==(GeodeticPosition other) const -> bool
    {
        return math::floating_point_eq(m_latitude, other.m_latitude)
            && math::floating_point_eq(m_longitude, other.m_longitude)
            && math::floating_point_eq(m_altitude, other.m_altitude);
    }

    auto set_latitude(double latitude) -> void;

    constexpr auto latitude() const -> double { return m_latitude; }

    auto set_longitude(double longitude) -> void;

    constexpr auto longitude() const -> double { return m_longitude; }

    constexpr auto set_altitude(double altitude) -> void
    {
        m_altitude = altitude;
    }

    constexpr auto altitude() const -> double { return m_altitude; }

    auto to_string() const -> std::string;

private:
    double m_latitude{};
    double m_longitude{};
    double m_altitude{};
};

}  // namespace shift::coordinate
