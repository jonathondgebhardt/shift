#include <memory>
#include <utility>

#include "shift/core/Simulation.hpp"

#include "shift/core/System.hpp"
#include "shift/logger/Log.hpp"

namespace shift
{

auto Simulation::add_system(std::unique_ptr<System> system) -> void
{
    if (!system) {
        shift::log::warning().append("refusing to add null system");
        return;
    }

    static auto uid = SystemUID{0};
    system->set_uid(++uid);
    m_systems.push_back(std::move(system));
}

}  // namespace shift
