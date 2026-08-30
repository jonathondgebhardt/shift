#pragma once

#include "shift/core/Clock.hpp"
#include "shift/core/shift_core_export.hpp"

namespace shift
{

class SHIFT_CORE_EXPORT Simulation
{
public:
    auto clock() -> Clock& { return m_clock; }

private:
    Clock m_clock;
    // world
    // systems
    // services
};

}  // namespace shift
