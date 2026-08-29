#include <format>
#include <iterator>
#include <memory>
#include <source_location>
#include <string>
#include <string_view>

#include "shift/logger/Log.hpp"

#include <spdlog/common.h>
#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace shift::log
{

namespace
{

// ============================================================
// Backend
// ============================================================

class Backend
{
public:
    Backend()
    {
        auto sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

        m_logger = std::make_shared<spdlog::logger>("shift", sink);

        m_logger->set_level(spdlog::level::trace);

        m_logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v");
    }

    [[nodiscard]]
    auto logger() noexcept -> spdlog::logger&
    {
        return *m_logger;
    }

private:
    std::shared_ptr<spdlog::logger> m_logger;
};

auto backend() -> Backend&
{
    static Backend instance;
    return instance;
}

// ============================================================
// Level conversion
// ============================================================

auto to_spdlog_level(Level level) noexcept -> spdlog::level::level_enum
{
    switch (level) {
        case Level::trace:
            return spdlog::level::trace;

        case Level::debug:
            return spdlog::level::debug;

        case Level::info:
            return spdlog::level::info;

        case Level::warning:
            return spdlog::level::warn;

        case Level::error:
            return spdlog::level::err;

        case Level::critical:
            return spdlog::level::critical;
    }

    // Should never happen unless Level gets an invalid value.
    return spdlog::level::off;
}

}  // namespace

// ============================================================
// Message::Impl
// ============================================================

struct Message::Impl
{
    Impl(Level level, std::source_location location)
        : m_level(level)
        , m_location(location)
    {
    }

    Level m_level;
    std::source_location m_location;

    std::string m_text;

    bool m_submitted = false;
};

// ============================================================
// Message
// ============================================================

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
    if (!m_impl || m_impl->m_submitted) {
        return;
    }

    std::vformat_to(std::back_inserter(m_impl->m_text), format, args);
}

auto Message::submit() -> void
{
    if (!m_impl || m_impl->m_submitted) {
        return;
    }

    m_impl->m_submitted = true;

    auto& logger = backend().logger();

    if (!logger.should_log(to_spdlog_level(m_impl->m_level))) {
        return;
    }

    const auto& location = m_impl->m_location;

    logger.log(spdlog::source_loc{location.file_name(),
                                  static_cast<int>(location.line()),
                                  location.function_name()},
               to_spdlog_level(m_impl->m_level),
               "{}",
               m_impl->m_text);
}

auto Message::enabled() const noexcept -> bool
{
    if (!m_impl || m_impl->m_submitted) {
        return false;
    }

    return backend().logger().should_log(to_spdlog_level(m_impl->m_level));
}

// ============================================================
// Factory functions
// ============================================================

auto trace(std::source_location location) -> Message
{
    return Message{Level::trace, location};
}

auto debug(std::source_location location) -> Message
{
    return Message{Level::debug, location};
}

auto info(std::source_location location) -> Message
{
    return Message{Level::info, location};
}

auto warning(std::source_location location) -> Message
{
    return Message{Level::warning, location};
}

auto error(std::source_location location) -> Message
{
    return Message{Level::error, location};
}

auto critical(std::source_location location) -> Message
{
    return Message{Level::critical, location};
}

}  // namespace shift::log
