#pragma once

#include <cstdint>
#include <format>
#include <memory>
#include <source_location>
#include <string_view>

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
    Message(const Message&) = delete;
    Message(Message&&) noexcept = default;

    ~Message();

    auto operator=(const Message&) -> Message& = delete;
    auto operator=(Message&&) noexcept -> Message& = default;

    template<typename... Args>
    auto append(std::format_string<Args...> format, Args&&... args) -> Message&;

    auto submit() -> void;

    [[nodiscard]]
    auto enabled() const noexcept -> bool;

private:
    SHIFT_SUPPRESS_C4251

    struct Impl;
    std::unique_ptr<Impl> m_impl;

    explicit Message(Level level, std::source_location location);

    auto append_formatted(std::string_view format, std::format_args args)
        -> void;

    friend auto trace(std::source_location location) -> Message;
    friend auto debug(std::source_location location) -> Message;
    friend auto info(std::source_location location) -> Message;
    friend auto warning(std::source_location location) -> Message;
    friend auto error(std::source_location location) -> Message;
    friend auto critical(std::source_location location) -> Message;
};

// error C2375: redefinition; different linkage
SHIFT_LOGGER_EXPORT auto trace(
    std::source_location location = std::source_location::current()) -> Message;

SHIFT_LOGGER_EXPORT auto debug(
    std::source_location location = std::source_location::current()) -> Message;

SHIFT_LOGGER_EXPORT auto info(
    std::source_location location = std::source_location::current()) -> Message;

SHIFT_LOGGER_EXPORT auto warning(
    std::source_location location = std::source_location::current()) -> Message;

SHIFT_LOGGER_EXPORT auto error(
    std::source_location location = std::source_location::current()) -> Message;

SHIFT_LOGGER_EXPORT auto critical(
    std::source_location location = std::source_location::current()) -> Message;

template<typename... Args>
auto Message::append(
    std::format_string<Args...> format,
    Args&&... args)  // NOLINT(cppcoreguidelines-missing-std-forward)
    -> Message&
{
    if (enabled()) {
        append_formatted(format.get(), std::make_format_args(args...));
    }

    return *this;
}

}  // namespace shift::log
