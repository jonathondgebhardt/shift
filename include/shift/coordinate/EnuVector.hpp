#pragma once

#include <string>

#include "shift/coordinate/shift_coordinate_export.hpp"

namespace shift::coordinate
{

struct SHIFT_COORDINATE_EXPORT EnuVector
{
    double east{};
    double north{};
    double up{};

    auto to_string() const -> std::string;
};

}  // namespace shift::coordinate
