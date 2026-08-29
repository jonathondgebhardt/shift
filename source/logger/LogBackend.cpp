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
        auto sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

        m_logger = std::make_shared<spdlog::logger>("shift", std::move(sink));

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

// auto Backend::output() const -> std::shared_ptr<Output>
// {
//     return m_output;
// }
//
auto backend() -> Backend&
{
    static Backend instance;
    return instance;
}

}  // namespace shift::log::detail
