#pragma once

#include "shift/core/Component.hpp"
#include "shift/core/TimeTypes.hpp"

namespace shift
{

class TimeUpdater : public Component
{
public:
    virtual auto next_time() -> time::Microseconds = 0;
};

}  // namespace shift
