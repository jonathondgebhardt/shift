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
    Message(Message&&) noexcept;
    ~Message();
    auto operator=(const Message&) -> Message& = delete;
    auto operator=(Message&&) noexcept -> Message&;

    auto submit() -> void;

    [[nodiscard]]
    auto enabled() const noexcept -> bool;

private:
    struct Impl;

    SHIFT_SUPPRESS_C4251
    std::unique_ptr<Impl> m_impl;
};

// todo: i would like this to accept a format string and a parameter pack to
// populate the format string
auto trace(std::string message,
           std::source_location location = std::source_location::current())
    -> Message;

auto debug(std::string message,
           std::source_location location = std::source_location::current())
    -> Message;

auto info(std::string message,
          std::source_location location = std::source_location::current())
    -> Message;

auto warning(std::string message,
             std::source_location location = std::source_location::current())
    -> Message;

auto error(std::string message,
           std::source_location location = std::source_location::current())
    -> Message;

auto critical(std::string message,
              std::source_location location = std::source_location::current())
    -> Message;

}  // namespace shift::log
