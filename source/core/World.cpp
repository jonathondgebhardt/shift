#include <algorithm>
#include <string_view>
#include <utility>
#include <vector>

#include "shift/core/World.hpp"

#include "shift/core/Entity.hpp"
#include "shift/core/OptionalEntityReference.hpp"

namespace shift
{

auto World::find_entity(EntityUID uid) -> OptionalEntityReference
{
    const auto found = std::ranges::find_if(
        m_entities, [&](const Entity& entity) { return entity.uid() == uid; });
    if (found != m_entities.end()) {
        return OptionalEntityReference{*found};
    }

    return {};
}

auto World::find_entity(std::string_view name) -> OptionalEntityReference
{
    const auto found = std::ranges::find_if(m_entities,
                                            [&](const Entity& entity)
                                            { return entity.name() == name; });
    if (found != m_entities.end()) {
        return OptionalEntityReference{*found};
    }

    return {};
}

auto World::add_entity() -> Entity&
{
    static auto uid = EntityUID{};
    auto entity = Entity{++uid};
    m_entities.push_back(std::move(entity));
    return m_entities.back();
}

auto World::remove_entity(EntityUID uid) -> bool
{
    return std::erase_if(m_entities,
                         [&](const Entity& entity)
                         { return entity.uid() == uid; })
        > 0;
}

auto World::remove_entity(std::string_view name) -> bool
{
    return std::erase_if(m_entities,
                         [&](const Entity& entity)
                         { return entity.name() == name; })
        > 0;
}

}  // namespace shift
