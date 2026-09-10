#include <cmath>
#include <cstdint>
#include <limits>
#include <memory>
#include <numbers>
#include <stdexcept>
#include <utility>

#include "shift/coordinate/Coordinate.hpp"
#include "shift/coordinate/CoordinateTransform.hpp"
#include "shift/core/Entity.hpp"
#include "shift/core/Simulation.hpp"
#include "shift/core/SimulationRunner.hpp"
#include "shift/core/System.hpp"
#include "shift/core/Systems.hpp"
#include "shift/core/UpdateResult.hpp"
#include "shift/core/World.hpp"
#include "shift/telemetry/ConsoleTelemetryRecorder.hpp"
#include "shift/telemetry/EntityDataDefinitions.hpp"
#include "shift/telemetry/Telemetry.hpp"
#include "shift/time/Clock.hpp"

namespace
{

class OrbitSystem : public shift::System
{
public:
    explicit OrbitSystem(shift::EntityUID uid)
        : m_uid{uid}
    {
    }

    auto startup() -> void override
    {
        if (m_uid == shift::EntityUID{}) {
            throw std::runtime_error("uid cannot be empty");
        }

        const auto double_equal = [](const double lhs, const double rhs)
        {
            return std::abs(lhs - rhs) < std::numeric_limits<double>::epsilon();
        };

        if (double_equal(m_radius, 0.0)) {
            throw std::runtime_error("radius cannot be zero");
        }

        if (double_equal(m_speed, 0.0)) {
            throw std::runtime_error("speed cannot be zero");
        }
    }

    auto first_update() -> shift::UpdateResult override
    {
        return shift::UpdateResult::schedule_now();
    }

    auto update(shift::World& world, shift::time::Clock::TimeStep time_step)
        -> shift::UpdateResult override
    {
        static auto update_count = 0u;
        update_count++;

        auto& entity = world.find_entity(m_uid).try_unwrap();
        constexpr auto frame = shift::coordinate::EnuFrame{};
        auto position = shift::coordinate::to_enu(entity.position(), frame);
        position.east = m_radius * std::cos(m_angle);
        position.north = m_radius * std::sin(m_angle);
        entity.set_position(shift::coordinate::to_ecef(position, frame));

        m_angle += m_speed * static_cast<double>(time_step.delta.data());

        constexpr auto two_pi = 2 * std::numbers::pi;
        if (m_angle > two_pi) {
            m_angle -= two_pi;
        }

        constexpr auto max_updates = 5;
        if (update_count < max_updates) {
            using namespace std::chrono_literals;
            return shift::UpdateResult::schedule_after(
                shift::time::Duration{1ms});
        }

        return shift::UpdateResult::stop();
    }

private:
    shift::EntityUID m_uid;

    double m_angle{};
    double m_speed{0.025};
    std::uint16_t m_radius{10u};
};

}  // namespace

auto main() -> int
{
    auto simulation = shift::Simulation{};
    auto& entity = simulation.world().add_entity();

    auto runner = shift::SimulationRunner{};

    auto telemetry = shift::telemetry::Telemetry{
        std::make_unique<shift::telemetry::ConsoleTelemetryRecorder>()};
    telemetry.observe(shift::telemetry::entity_position_enu);

    runner.set_telemetry(&telemetry);

    auto system = std::make_unique<OrbitSystem>(entity.uid());
    simulation.systems().add_system(std::move(system));

    runner.run(simulation);

    return 0;
}
