#include <array>
#include <vector>

#include "shift/coordinate/CoordinateTransform.hpp"

#include <GeographicLib/Geocentric.hpp>
#include <GeographicLib/LocalCartesian.hpp>

#include "shift/coordinate/EcefPosition.hpp"
#include "shift/coordinate/EcefVector.hpp"
#include "shift/coordinate/EnuFrame.hpp"
#include "shift/coordinate/EnuPosition.hpp"
#include "shift/coordinate/EnuVector.hpp"
#include "shift/coordinate/GeodeticPosition.hpp"

namespace
{
// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers,
// readability-magic-numbers)

auto get_cartesian_rotation_matrix(shift::coordinate::EnuFrame frame)
    -> std::array<double, 9>
{
    const auto cartesian =
        GeographicLib::LocalCartesian{frame.origin.latitude(),
                                      frame.origin.longitude(),
                                      frame.origin.altitude()};
    auto matrix = std::vector<double>{};
    auto dont_care = 0.0;
    cartesian.Forward(frame.origin.latitude(),
                      frame.origin.longitude(),
                      frame.origin.altitude(),
                      dont_care,
                      dont_care,
                      dont_care,
                      matrix);

    // todo: throw if matrix is not 3x3

    auto array = std::array<double, 9>{};
    std::ranges::copy(matrix.begin(), matrix.end(), array.begin());
    return array;
}

auto transpose(std::array<double, 9> matrix) -> std::array<double, 9>
{
    return {matrix[0],
            matrix[3],
            matrix[6],
            matrix[1],
            matrix[4],
            matrix[7],
            matrix[2],
            matrix[5],
            matrix[8]};
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers,
// readability-magic-numbers)

}  // namespace

namespace shift::coordinate
{

auto to_geodetic(EcefPosition position) -> GeodeticPosition
{
    const auto& earth = GeographicLib::Geocentric::WGS84();
    double latitude{};
    double longitude{};
    double altitude{};
    earth.Reverse(
        position.x, position.y, position.z, latitude, longitude, altitude);
    return {latitude, longitude, altitude};
}

auto to_geodetic(EnuPosition position, EnuFrame frame) -> GeodeticPosition
{
    const auto cartesian =
        GeographicLib::LocalCartesian{frame.origin.latitude(),
                                      frame.origin.longitude(),
                                      frame.origin.altitude()};
    double latitude{};
    double longitude{};
    double altitude{};
    cartesian.Reverse(position.east,
                      position.north,
                      position.up,
                      latitude,
                      longitude,
                      altitude);
    return {latitude, longitude, altitude};
}

auto to_ecef(GeodeticPosition position) -> EcefPosition
{
    const auto& earth = GeographicLib::Geocentric::WGS84();
    auto ecef = EcefPosition{};
    earth.Forward(position.latitude(),
                  position.longitude(),
                  position.altitude(),
                  ecef.x,
                  ecef.y,
                  ecef.z);
    return ecef;
}

auto to_ecef([[maybe_unused]] EnuPosition position,
             [[maybe_unused]] EnuFrame frame) -> EcefPosition
{
    return to_ecef(to_geodetic(position, frame));
}

auto to_ecef(EnuVector vector, const EnuFrame& frame) -> EcefVector
{
    const auto matrix = get_cartesian_rotation_matrix(frame);

    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers,
    // readability-magic-numbers)
    return {
        (matrix[0] * vector.east) + (matrix[1] * vector.north)
            + (matrix[2] * vector.up),
        (matrix[3] * vector.east) + (matrix[4] * vector.north)
            + (matrix[5] * vector.up),
        (matrix[6] * vector.east) + (matrix[7] * vector.north)
            + (matrix[8] * vector.up),
    };
    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers,
    // readability-magic-numbers)
}

auto to_enu(GeodeticPosition position, EnuFrame frame) -> EnuPosition
{
    const auto cartesian =
        GeographicLib::LocalCartesian{frame.origin.latitude(),
                                      frame.origin.longitude(),
                                      frame.origin.altitude()};
    auto enu = EnuPosition{};
    cartesian.Forward(position.latitude(),
                      position.longitude(),
                      position.altitude(),
                      enu.east,
                      enu.north,
                      enu.up);
    return enu;
}

auto to_enu(EcefPosition position, EnuFrame frame) -> EnuPosition
{
    return to_enu(to_geodetic(position), frame);
}

auto to_enu(EcefVector vector, EnuFrame frame) -> EnuVector
{
    const auto matrix = transpose(get_cartesian_rotation_matrix(frame));

    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers,
    // readability-magic-numbers)
    return {
        (matrix[0] * vector.x) + (matrix[1] * vector.y)
            + (matrix[2] * vector.z),
        (matrix[3] * vector.x) + (matrix[4] * vector.y)
            + (matrix[5] * vector.z),
        (matrix[6] * vector.x) + (matrix[7] * vector.y)
            + (matrix[8] * vector.z),
    };
    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers,
    // readability-magic-numbers)
}

}  // namespace shift::coordinate
