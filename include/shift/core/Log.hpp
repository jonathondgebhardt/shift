#pragma once

#include <cstdint>
#include <format>
#include <memory>
#include <source_location>
#include <string_view>

namespace shift::log
{

enum class Level : std::uint8_t
{
    trace,
    debug,
    info,
    warning,
    error,
    critical
};

class Message
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

    [[nodiscard]] auto enabled() const noexcept -> bool;

private:
    struct Impl;

    explicit Message(Level level, std::source_location location);

    auto append_formatted(std::string_view format, std::format_args args)
        -> void;

    std::unique_ptr<Impl> m_impl;

    friend auto trace(std::source_location location) -> Message;
    friend auto debug(std::source_location location) -> Message;
    friend auto info(std::source_location location) -> Message;
    friend auto warning(std::source_location location) -> Message;
    friend auto error(std::source_location location) -> Message;
    friend auto critical(std::source_location location) -> Message;
};

auto trace(std::source_location location = std::source_location::current())
    -> Message;

auto debug(std::source_location location = std::source_location::current())
    -> Message;

auto info(std::source_location location = std::source_location::current())
    -> Message;

auto warning(std::source_location location = std::source_location::current())
    -> Message;

auto error(std::source_location location = std::source_location::current())
    -> Message;

auto critical(std::source_location location = std::source_location::current())
    -> Message;

// ------------------------------------------------------------
// Template implementation
// ------------------------------------------------------------

template<typename... Args>
auto Message::append(std::format_string<Args...> format, Args&&... args)
    -> Message&
{
    if (m_impl && enabled()) {
        append_formatted(format.get(), std::make_format_args(args...));
    }

    return *this;
}

}  // namespace shift::log
