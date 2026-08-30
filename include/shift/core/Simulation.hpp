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
    // systems
    // services
};

}  // namespace shift
