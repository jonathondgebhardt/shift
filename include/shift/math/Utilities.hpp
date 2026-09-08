#pragma once

#include <cmath>
#include <limits>
#include <type_traits>

#include "shift/math/shift_math_export.hpp"

namespace shift::math
{

template<typename T>
    requires std::is_floating_point_v<T>
SHIFT_MATH_EXPORT constexpr auto floating_point_eq(
    const T lhs, const T rhs, T epsilon = std::numeric_limits<T>::epsilon())
    -> auto
{
    return std::abs(lhs - rhs) < epsilon;
}

}  // namespace shift::math
