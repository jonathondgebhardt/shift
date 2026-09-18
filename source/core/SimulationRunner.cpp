#include <algorithm>
#include <format>
#include <iostream>
#include <memory>

#include "shift/core/Simulation.hpp"

#include "shift/core/SimulationRunner.hpp"
#include "shift/core/System.hpp"
#include "shift/core/UpdateResult.hpp"
#include "shift/logger/Log.hpp"
#include "shift/time/Clock.hpp"
#include "shift/time/SimulationTime.hpp"
#include "shift/time/Timer.hpp"
#include "shift/utilities/Exception.hpp"

namespace shift
{

auto SimulationRunner::run(Simulation& simulation,
                           time::SimulationTime time_limit) -> void
{
    auto timer = time::Timer{};
    timer.reset();

    log::trace("starting up systems");
    simulation.systems().startup(simulation.world());

    log::trace("sampling initial world state");
    if (m_telemetry != nullptr) {
        m_telemetry->sample({}, simulation.world());
    }

    auto& clock = simulation.clock();

    log::trace("scheduling first update");
    // todo: systems().systems() is gross. can scheduling the first update be
    // encapsulated?
    std::ranges::for_each(
        simulation.systems().systems(),
        [&](const std::unique_ptr<System>& system)
        {
            const auto result = system->first_update();
            if (const auto next_update = result.next_time(clock.time());
                next_update)
            {
                m_scheduler.schedule(*system, *next_update);
            }
        });

    if (m_scheduler.empty()) {
        throw Exception{"no systems scheduled a first update"};
    }

    log::trace("running simulation");

    // todo: check end condition before processing updates
    // todo: this API is kind of annoying: make sure scheduler is not empty, get
    // first next update event, then make sure it's not nullopt
    while (!m_scheduler.empty() && m_scheduler.top()) {
        // we know there's a valid event to process because the scheduler is not
        // empty and we check that the top event is not nullopt
        // NOLINTNEXTLINE(bugprone-unchecked-optional-access)
        const auto current_update = m_scheduler.top().value();

        if (current_update.time > time_limit) {
            log::info(
                std::format("time limit met: {}", clock.time().to_string()));
            break;
        }

        m_scheduler.pop();

        clock.set_time(current_update.time);
        const auto time_step = clock.time_step();

        // todo: i thought about encapsulating updating a system into Systems,
        // but that introduce a coupling between Systems and UpdateScheduler.
        auto* system = simulation.systems().find_system(current_update.uid);
        if (system == nullptr) {
            throw Exception{std::format("failed to find system with uid {}",
                                        current_update.uid)};
        }

        const auto result = system->update(simulation.world(), time_step);
        if (const auto next_update = result.next_time(clock.time());
            next_update)
        {
            m_scheduler.schedule(*system, *next_update);
        }

        if (m_telemetry != nullptr) {
            m_telemetry->sample(time_step.time, simulation.world());
        }
    }

    log::trace("shutting down simulation");

    // todo: would like to be able to do this
    // shift::log::trace("time elapsed: {}", timer.elapsed().to_string());
    log::info(
        std::format("real time elapsed: {}", timer.elapsed().to_string()));
}

}  // namespace shift
