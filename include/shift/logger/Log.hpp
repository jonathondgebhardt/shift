#pragma once

#include <cstdint>
#include <format>
#include <memory>
#include <source_location>

#include "shift/logger/shift_logger_export.hpp"

namespace shift::log
{

enum class Level : std::uint8_t
{
    TRACE,
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};

class SHIFT_LOGGER_EXPORT Message
{
public:
    explicit Message(std::string text,
                     Level level,
                     std::source_location location);

    Message(const Message&) = delete;
    Message(Message&&) noexcept = default;
    ~Message();
    auto operator=(const Message&) -> Message& = delete;
    auto operator=(Message&&) noexcept -> Message& = default;

    auto submit() -> void;

    [[nodiscard]]
    auto enabled() const noexcept -> bool;

private:
    SHIFT_SUPPRESS_C4251

    struct Impl;
    std::unique_ptr<Impl> m_impl;
};

// todo: way to much duplication
template<typename... Args>
SHIFT_LOGGER_EXPORT auto trace(
    std::format_string<Args...> msg,
    Args&&... args,
    std::source_location location = std::source_location::current()) -> Message
{
    return Message{
        std::format(msg, std::forward<Args>(args)...), Level::TRACE, location};
}

template<typename... Args>
SHIFT_LOGGER_EXPORT auto debug(
    std::format_string<Args...> msg,
    Args&&... args,
    std::source_location location = std::source_location::current()) -> Message
{
    return Message{
        std::format(msg, std::forward<Args>(args)...), Level::DEBUG, location};
}

template<typename... Args>
SHIFT_LOGGER_EXPORT auto info(
    std::format_string<Args...> msg,
    Args&&... args,
    std::source_location location = std::source_location::current()) -> Message
{
    return Message{
        std::format(msg, std::forward<Args>(args)...), Level::INFO, location};
}

template<typename... Args>
SHIFT_LOGGER_EXPORT auto warning(
    std::format_string<Args...> msg,
    Args&&... args,
    std::source_location location = std::source_location::current()) -> Message
{
    return Message{std::format(msg, std::forward<Args>(args)...),
                   Level::WARNING,
                   location};
}

template<typename... Args>
SHIFT_LOGGER_EXPORT auto error(
    std::format_string<Args...> msg,
    Args&&... args,
    std::source_location location = std::source_location::current()) -> Message
{
    return Message{
        std::format(msg, std::forward<Args>(args)...), Level::ERROR, location};
}

template<typename... Args>
SHIFT_LOGGER_EXPORT auto critical(
    std::format_string<Args...> msg,
    Args&&... args,
    std::source_location location = std::source_location::current()) -> Message
{
    return Message{std::format(msg, std::forward<Args>(args)...),
                   Level::CRITICAL,
                   location};
}

}  // namespace shift::log
