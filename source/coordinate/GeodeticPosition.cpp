#include <format>
#include <stdexcept>
#include <string>

#include "shift/coordinate/GeodeticPosition.hpp"

namespace
{

constexpr auto valid_latitude(double latitude) -> bool
{
    constexpr auto latitude_boundary = 90.0;
    return latitude >= -latitude_boundary && latitude <= latitude_boundary;
}

constexpr auto valid_longitude(double longitude) -> bool
{
    constexpr auto longitude_boundary = 180.0;
    return longitude >= -longitude_boundary && longitude <= longitude_boundary;
}

}  // namespace

namespace shift::coordinate
{

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
GeodeticPosition::GeodeticPosition(double latitude, double longitude)
    : GeodeticPosition{latitude, longitude, 0.0}
{
}

// NOLINTBEGIN(bugprone-easily-swappable-parameters)
GeodeticPosition::GeodeticPosition(double latitude,
                                   double longitude,
                                   double altitude)
    : m_latitude{latitude}
    , m_longitude{longitude}
    , m_altitude{altitude}
{
    // NOLINTEND(bugprone-easily-swappable-parameters)
    if (!valid_latitude(latitude)) {
        throw std::runtime_error(
            std::format("latitude must be within [-90, 90]: {}", latitude));
    }

    if (!valid_longitude(longitude)) {
        throw std::runtime_error(
            std::format("longitude must be within [-180, 180]: {}", longitude));
    }
}

auto GeodeticPosition::set_latitude(double latitude) -> void
{
    if (!valid_latitude(latitude)) {
        throw std::runtime_error(
            std::format("latitude must be within [-90, 90]: {}", latitude));
    }

    m_latitude = latitude;
}

auto GeodeticPosition::set_longitude(double longitude) -> void
{
    if (!valid_longitude(longitude)) {
        throw std::runtime_error(
            std::format("longitude must be within [-180, 180]: {}", longitude));
    }

    m_longitude = longitude;
}

auto GeodeticPosition::to_string() const -> std::string
{
    return std::format("({}, {}, {})", m_latitude, m_longitude, m_altitude);
}

}  // namespace shift::coordinate
