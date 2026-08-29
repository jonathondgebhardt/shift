#include <random>

#include "shift/core/UUID.hpp"

#include <fmt/format.h>

namespace shift
{

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers,
// hicpp-signed-bitwise)

// shamelessly stolen from LLM. perhaps using boost::uuid would be better.
auto UUID::build() -> UUID
{
    // todo: expose seeding generator

    static std::random_device device;
    static std::mt19937_64 gen{device()};

    std::uniform_int_distribution<std::uint64_t> dis{0, 0xFFFFFFFFFFFFFFFF};

    std::uint64_t first = dis(gen);
    std::uint64_t second = dis(gen);

    // set the 4 most significant bits of the 7th byte to 0100 (version 4)
    first = (first & 0xFFFFFFFFFFFF0FFF) | 0x0000000000004000;
    second = (second & 0x3FFFFFFFFFFFFFFF) | 0x8000000000000000;

    return UUID{first, second};
}

auto UUID::to_string() const -> std::string
{
    return fmt::format(
        "{:08x}-{:04x}-{:04x}-{:04x}-{:012x}",
        static_cast<std::uint32_t>(m_first >> 32),
        static_cast<std::uint16_t>((m_first >> 16) & 0xFFFF),
        static_cast<std::uint16_t>(m_first & 0xFFFF),
        static_cast<std::uint16_t>(m_second >> 48),
        static_cast<std::uint64_t>(m_second & 0xFFFFFFFFFFFFull));
}

auto UUID::empty() const -> bool
{
    return m_first == std::uint64_t{} && m_second == std::uint64_t{};
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers,
// hicpp-signed-bitwise)

}  // namespace shift
