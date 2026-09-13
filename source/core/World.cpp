#include <algorithm>
#include <memory>
#include <string_view>
#include <utility>
#include <vector>

#include "shift/core/World.hpp"

#include "shift/core/Entity.hpp"

namespace shift
{

auto World::find_entity(const EntityUID uid) -> Entity*
{
    const auto found =
        std::ranges::find_if(m_entities,
                             [&](const std::unique_ptr<Entity>& entity)
                             { return entity->uid() == uid; });
    if (found != m_entities.end()) {
        return found->get();
    }

    return {};
}

auto World::find_entity(const std::string_view name) -> Entity*
{
    const auto found =
        std::ranges::find_if(m_entities,
                             [&](const std::unique_ptr<Entity>& entity)
                             { return entity->name() == name; });
    if (found != m_entities.end()) {
        return found->get();
    }

    return {};
}

auto World::add_entity() -> Entity*
{
    static auto uid = EntityUID{};
    auto entity = std::make_unique<Entity>(++uid);
    m_entities.push_back(std::move(entity));
    return m_entities.back().get();
}

auto World::remove_entity(const EntityUID uid) -> bool
{
    return std::erase_if(m_entities,
                         [&](const std::unique_ptr<Entity>& entity)
                         { return entity->uid() == uid; })
        > 0;
}

auto World::remove_entity(const std::string_view name) -> bool
{
    return std::erase_if(m_entities,
                         [&](const std::unique_ptr<Entity>& entity)
                         { return entity->name() == name; })
        > 0;
}

}  // namespace shift
