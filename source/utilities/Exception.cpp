#include <format>
#include <source_location>
#include <stdexcept>
#include <string>

#include "shift/utilities/Exception.hpp"

namespace
{

auto format_message(const std::string& message,
                    const std::source_location& loc) -> std::string
{
    return std::format("{} at {}:{} ({})",
                       message,
                       loc.file_name(),
                       loc.line(),
                       loc.function_name());
}

}  // namespace

namespace shift
{

Exception::Exception(const std::string& message,
                     const std::source_location& loc)
    : std::runtime_error{format_message(message, loc)}
{
}

}  // namespace shift
