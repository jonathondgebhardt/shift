#include <algorithm>
#include <memory>
#include <utility>
#include <vector>

#include "shift/core/Systems.hpp"

#include "shift/core/System.hpp"
#include "shift/logger/Log.hpp"

namespace shift
{

auto Systems::add_system(std::unique_ptr<System> system) -> void
{
    if (!system) {
        shift::log::warning("refusing to add null system");
        return;
    }

    static auto uid = SystemUID{0};
    system->set_uid(++uid);
    m_systems.push_back(std::move(system));
}

auto Systems::remove_system(SystemUID uid) -> bool
{
    return std::erase_if(m_systems,
                         [&](const std::unique_ptr<System>& system)
                         { return system->uid() == uid; })
        > 0;
}

auto Systems::find_system(SystemUID uid) -> System*
{
    const auto found =
        std::ranges::find_if(m_systems,
                             [&](const std::unique_ptr<System>& system)
                             { return system->uid() == uid; });
    return found != m_systems.end() ? found->get() : nullptr;
}

auto Systems::startup() -> void
{
    std::ranges::for_each(m_systems,
                          [](const std::unique_ptr<System>& system)
                          { system->startup(); });
}

}  // namespace shift
