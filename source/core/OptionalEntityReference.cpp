#include <exception>
#include <optional>

#include "shift/core/OptionalEntityReference.hpp"

#include "shift/core/Entity.hpp"

namespace shift
{

auto OptionalEntityReference::unwrap() -> Entity&
{
    return m_entity.value().get();
}

auto OptionalEntityReference::unwrap() const -> const Entity&
{
    return m_entity.value().get();
}

auto OptionalEntityReference::try_unwrap() -> Entity&
{
    if (empty()) {
        throw std::runtime_error("does not contain entity");
    }

    return m_entity.value().get();
}

auto OptionalEntityReference::try_unwrap() const -> const Entity&
{
    if (empty()) {
        throw std::runtime_error("does not contain entity");
    }

    return m_entity.value().get();
}

auto OptionalEntityReference::empty() const -> bool
{
    return !m_entity.has_value();
}

}  // namespace shift
