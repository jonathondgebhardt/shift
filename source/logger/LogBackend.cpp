#include <memory>
#include <source_location>
#include <string>
#include <string_view>
#include <utility>

#include "shift/logger/LogBackend.hpp"

#include <spdlog/common.h>
#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "shift/logger/Log.hpp"

namespace shift::log::detail
{

namespace
{

constexpr auto to_spdlog_level(Level level) noexcept
    -> spdlog::level::level_enum
{
    switch (level) {
        case Level::TRACE:
            return spdlog::level::trace;

        case Level::DEBUG:
            return spdlog::level::debug;

        case Level::INFO:
            return spdlog::level::info;

        case Level::WARNING:
            return spdlog::level::warn;

        case Level::ERROR:
            return spdlog::level::err;

        case Level::CRITICAL:
            return spdlog::level::critical;
    }

    return spdlog::level::off;
}

// ------------------------------------------------------------
// Output interface
// ------------------------------------------------------------

class SpdlogOutput final : public Backend::Output
{
public:
    SpdlogOutput()
    {
        // todo: should be able to configure sink externally
        // todo: log file
        auto sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

        m_logger = std::make_shared<spdlog::logger>("shift", std::move(sink));
        // todo: should be able to configure level externally
        m_logger->set_level(spdlog::level::trace);
        m_logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v");
    }

    auto enabled(Level level) const noexcept -> bool override
    {
        return m_logger->should_log(to_spdlog_level(level));
    }

    auto write(Level level,
               std::string_view message,
               std::source_location location) -> void override
    {
        const auto spdlog_level = to_spdlog_level(level);

        if (!m_logger->should_log(spdlog_level)) {
            return;
        }

        m_logger->log(spdlog::source_loc{location.file_name(),
                                         static_cast<int>(location.line()),
                                         location.function_name()},
                      spdlog_level,
                      "{}",
                      message);
    }

private:
    std::shared_ptr<spdlog::logger> m_logger;
};

}  // namespace

// ------------------------------------------------------------
// Backend
// ------------------------------------------------------------

Backend::Backend()
    : m_output(std::make_shared<SpdlogOutput>())
{
}

Backend::~Backend() = default;

auto Backend::enabled(Level level) const noexcept -> bool
{
    return m_output->enabled(level);
}

auto Backend::write(Level level,
                    std::string_view message,
                    std::source_location location) -> void
{
    m_output->write(level, message, location);
}

auto Backend::set_output(std::shared_ptr<Output> output)
    -> std::shared_ptr<Output>
{
    auto previous = std::move(m_output);
    m_output = std::move(output);
    return previous;
}

auto backend() -> Backend&
{
    static Backend instance;
    return instance;
}

}  // namespace shift::log::detail
