#pragma once

#include <cmath>
#include <limits>
#include <type_traits>

namespace shift::math
{

template<typename T>
    requires std::is_floating_point_v<T>
constexpr auto floating_point_eq(const T lhs, const T rhs) -> auto
{
    return std::abs(lhs - rhs) < std::numeric_limits<T>::epsilon();
}

}  // namespace shift::math
