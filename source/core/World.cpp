#include <algorithm>
#include <functional>
#include <optional>
#include <string_view>
#include <vector>

#include "shift/core/World.hpp"

#include "shift/core/Entity.hpp"
#include "shift/core/UUID.hpp"

namespace shift
{

auto World::find_entity(UUID uuid) -> OptionalEntityReference
{
    const auto found = std::ranges::find_if(m_entities,
                                            [&](const Entity& entity)
                                            { return entity.uuid() == uuid; });
    return found != m_entities.end() ? std::optional{std::ref(*found)}
                                     : std::nullopt;
}

auto World::find_entity(std::string_view name) -> OptionalEntityReference
{
    const auto found = std::ranges::find_if(m_entities,
                                            [&](const Entity& entity)
                                            { return entity.name() == name; });
    return found != m_entities.end() ? std::optional{std::ref(*found)}
                                     : std::nullopt;
}

auto World::add_entity() -> Entity&
{
    // todo: use something other than uuid?
    m_entities.emplace_back();
    return m_entities.back();
}

auto World::remove_entity(UUID uuid) -> bool
{
    return std::erase_if(m_entities,
                         [&](const Entity& entity)
                         { return entity.uuid() == uuid; })
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
