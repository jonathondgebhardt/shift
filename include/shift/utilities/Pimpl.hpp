#pragma once

#include <memory>

template<typename T>
class Pimpl
{
public:
    template<typename... Args>
    explicit Pimpl(Args&&... args)
        : m_ptr{std::make_unique<T>(std::forward<Args>(args)...)}
    {
    }

    auto operator->() -> T* { return m_ptr.get(); }

    auto operator->() const -> const T* { return m_ptr.get(); }

    auto operator*() -> T& { return *m_ptr; }

    auto operator*() const -> const T& { return *m_ptr; }

private:
    std::unique_ptr<T> m_ptr;
};
