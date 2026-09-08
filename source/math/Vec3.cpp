#include <cmath>

#include "shift/math/Vec3.hpp"

namespace shift::math
{

auto Vec3::magnitude() const -> double
{
    return std::hypot(x, y, z);
}

auto Vec3::distance(const Vec3 lhs, const Vec3 rhs) -> double
{
    return (lhs - rhs).magnitude();
}

}  // namespace shift::math
