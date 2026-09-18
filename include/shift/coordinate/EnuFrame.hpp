#pragma once

#include "shift/coordinate/GeodeticPosition.hpp"

namespace shift::coordinate
{

struct EnuFrame
{
    GeodeticPosition origin;

    constexpr auto operator==(const EnuFrame&) const -> bool = default;
};

}  // namespace shift::coordinate
