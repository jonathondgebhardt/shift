#include <string>
#include <utility>

#include "shift/core/Component.hpp"

#include "shift/core/UUID.hpp"

namespace shift
{

auto Component::uuid() const -> UUID
{
    return m_uuid;
}

auto Component::set_name(std::string name) -> void
{
    m_name = std::move(name);
}

}  // namespace shift
