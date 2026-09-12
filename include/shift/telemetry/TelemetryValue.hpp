#pragma once

#include <memory>
#include <typeindex>
#include <utility>

#include "shift/telemetry/TelemetryTraits.hpp"

namespace shift::telemetry
{

class TelemetryValue
{
public:
    template<typename T>
    explicit TelemetryValue(T value)
        : m_value{std::make_unique<Value<T>>(std::move(value))}
    {
    }

    TelemetryValue(const TelemetryValue& other)
        : m_value{other.m_value->clone()}
    {
    }

    TelemetryValue(TelemetryValue&&) noexcept = default;

    auto operator=(const TelemetryValue& other) -> TelemetryValue&
    {
        if (this != &other) {
            m_value = other.m_value->clone();
        }

        return *this;
    }

    auto operator=(TelemetryValue&&) noexcept -> TelemetryValue& = default;

    ~TelemetryValue() = default;

    auto type() const noexcept -> std::type_index { return m_value->type(); }

    template<typename T>
    auto is() const noexcept -> bool
    {
        return type() == typeid(T);
    }

    template<typename T>
    auto get() const -> const T&
    {
        if (!is<T>()) {
            // todo: throw with a useful message
            throw std::bad_cast{};
        }

        return *static_cast<const T*>(m_value->pointer());
    }

    auto to_string() const -> std::string { return m_value->to_string(); }

private:
    struct Concept
    {
        Concept() = default;
        Concept(const Concept&) = default;
        Concept(Concept&&) noexcept = default;
        virtual ~Concept() = default;
        auto operator=(const Concept&) -> Concept& = default;
        auto operator=(Concept&&) noexcept -> Concept& = default;

        virtual auto type() const noexcept -> std::type_index = 0;

        virtual auto pointer() const noexcept -> const void* = 0;

        virtual auto clone() const -> std::unique_ptr<Concept> = 0;

        virtual auto to_string() const -> std::string = 0;
    };

    template<typename T>
    struct Value final : Concept
    {
        explicit Value(T val)
            : value{std::move(val)}
        {
        }

        auto type() const noexcept -> std::type_index override
        {
            return typeid(T);
        }

        auto pointer() const noexcept -> const void* override { return &value; }

        auto clone() const -> std::unique_ptr<Concept> override
        {
            return std::make_unique<Value<T>>(value);
        }

        auto to_string() const -> std::string override
        {
            return TelemetryTraits<T>::to_string(value);
        }

        T value;
    };

    std::unique_ptr<Concept> m_value;
};

}  // namespace shift::telemetry
