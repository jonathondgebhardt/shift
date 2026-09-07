#include <memory>
#include <source_location>
#include <string>
#include <utility>

#include "shift/logger/Log.hpp"

#include "shift/logger/LogBackend.hpp"

namespace shift::log
{

struct Message::Impl
{
    Impl(std::string tex, Level lev, std::source_location loc)
        : level{lev}
        , location{loc}
        , text{std::move(tex)}
    {
    }

    Level level;
    std::source_location location;
    std::string text;
    bool submitted = false;
};

Message::Message(std::string text, Level level, std::source_location location)
    : m_impl{std::make_unique<Impl>(std::move(text), level, location)}
{
}

Message::~Message()
{
    submit();
}

auto Message::submit() -> void
{
    if (m_impl->submitted) {
        return;
    }

    m_impl->submitted = true;

    detail::backend().write(m_impl->level, m_impl->text, m_impl->location);
}

auto Message::enabled() const noexcept -> bool
{
    if (m_impl->submitted) {
        return false;
    }

    return detail::backend().enabled(m_impl->level);
}

}  // namespace shift::log
