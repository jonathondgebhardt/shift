#include <string>
#include <utility>

#include "shift/core/Object.hpp"

#include "shift/core/UUID.hpp"

namespace shift
{

auto Object::uuid() const -> UUID
{
    return m_uuid;
}

auto Object::set_name(std::string name) -> void
{
    m_name = std::move(name);
}

}  // namespace shift
