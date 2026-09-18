#pragma once

#include <source_location>
#include <stdexcept>
#include <string>

#include "shift/utilities/shift_utilities_export.hpp"

namespace shift
{

class Exception : public std::runtime_error
{
public:
    SHIFT_UTILITIES_EXPORT explicit Exception(
        const std::string& message,
        const std::source_location& loc = std::source_location::current());
};

}  // namespace shift
