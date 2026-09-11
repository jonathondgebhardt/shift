#pragma once

#include <format>

namespace shift::coordinate
{

// todo: consider hiding members to enable validation
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
