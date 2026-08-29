#include <format>
#include <iterator>
#include <memory>
#include <source_location>
#include <string>
#include <string_view>

#include "shift/logger/Log.hpp"

#include "shift/logger/LogBackend.hpp"

namespace shift::log
{

struct Message::Impl
{
    Impl(Level level, std::source_location location)
        : level(level)
        , location(location)
    {
    }

    Level level;
    std::source_location location;
    std::string text;
    bool submitted = false;
};

Message::Message(Level level, std::source_location location)
    : m_impl(std::make_unique<Impl>(level, location))
{
}

Message::~Message()
{
    submit();
}

auto Message::append_formatted(std::string_view format, std::format_args args)
    -> void
{
    if (!m_impl || m_impl->submitted) {
        return;
    }

    std::vformat_to(std::back_inserter(m_impl->text), format, args);
}

auto Message::submit() -> void
{
    if (!m_impl || m_impl->submitted) {
        return;
    }

    m_impl->submitted = true;

    detail::backend().write(m_impl->level, m_impl->text, m_impl->location);
}

auto Message::enabled() const noexcept -> bool
{
    if (!m_impl || m_impl->submitted) {
        return false;
    }

    return detail::backend().enabled(m_impl->level);
}

// ------------------------------------------------------------
// Factory functions
// ------------------------------------------------------------

auto trace(std::source_location location) -> Message
{
    return Message{Level::TRACE, location};
}

auto debug(std::source_location location) -> Message
{
    return Message{Level::DEBUG, location};
}

auto info(std::source_location location) -> Message
{
    return Message{Level::INFO, location};
}

auto warning(std::source_location location) -> Message
{
    return Message{Level::WARNING, location};
}

auto error(std::source_location location) -> Message
{
    return Message{Level::ERROR, location};
}

auto critical(std::source_location location) -> Message
{
    return Message{Level::CRITICAL, location};
}

}  // namespace shift::log
