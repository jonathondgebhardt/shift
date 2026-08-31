#pragma once

#include "shift/core/Clock.hpp"
#include "shift/core/World.hpp"
#include "shift/core/shift_core_export.hpp"

namespace shift
{

class SHIFT_CORE_EXPORT Simulation
{
public:
    auto clock() -> Clock& { return m_clock; }

    auto world() -> World& { return m_world; }

private:
    Clock m_clock;
    World m_world;
    // systems: transforms or evaluates simulation state as part of the
    // simulation's progression; perform some operation on simulation state
    // - What work needs to happen as the simulation advances?
    // - e.g.: physics, collision, simulation models
    //
    // services: provides capabilities used by the simulation but does not
    // itself constitute a simulation process
    // - What capability does the simulation need access to?
    // - e.g.: rng, events, logger, config, networking, recorder
};

}  // namespace shift
