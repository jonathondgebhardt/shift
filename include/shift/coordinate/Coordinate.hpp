#pragma once

#include <format>

namespace shift::coordinate
{

struct EcefVector
{
    double x{};
    double y{};
    double z{};

    auto to_string() const -> std::string
    {
        return std::format("({}, {}, {})", x, y, z);
    }
};

struct GeodeticPosition
{
    double latitude{};
    double longitude{};
    double altitude{};

    auto to_string() const -> std::string
    {
        return std::format("({}, {}, {})", latitude, longitude, altitude);
    }
};

struct EnuPosition
{
    double east{};
    double north{};
    double up{};

    auto to_string() const -> std::string
    {
        return std::format("({}, {}, {})", east, north, up);
    }
};

struct EnuVector
{
    double east{};
    double north{};
    double up{};

    auto to_string() const -> std::string
    {
        return std::format("({}, {}, {})", east, north, up);
    }
};

struct EnuFrame
{
    GeodeticPosition origin;
};

}  // namespace shift::coordinate
