#include <stdexcept>

#include "shift/core/OptionalEntityReference.hpp"

#include "shift/core/Entity.hpp"

namespace shift
{

auto OptionalEntityReference::unwrap() -> Entity&
{
    // NOLINTNEXTLINE(bugprone-unchecked-optional-access)
    return m_entity.value().get();
}

auto OptionalEntityReference::unwrap() const -> const Entity&
{
    // NOLINTNEXTLINE(bugprone-unchecked-optional-access)
    return m_entity.value().get();
}

auto OptionalEntityReference::try_unwrap() -> Entity&
{
    if (empty()) {
        throw std::runtime_error("does not contain entity");
    }

    // NOLINTNEXTLINE(bugprone-unchecked-optional-access)
    return m_entity.value().get();
}

auto OptionalEntityReference::try_unwrap() const -> const Entity&
{
    if (empty()) {
        throw std::runtime_error("does not contain entity");
    }

    // NOLINTNEXTLINE(bugprone-unchecked-optional-access)
    return m_entity.value().get();
}

auto OptionalEntityReference::empty() const -> bool
{
    return !m_entity.has_value();
}

}  // namespace shift
