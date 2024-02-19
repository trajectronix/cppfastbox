/**
 * @file platform.h
 * @brief mix max函数实现
 *
 * @copyright Copyright (c) 2024-present Trajectronix Open Source Group
 *
 */
#pragma once
#include <concepts>

namespace cppfastbox
{
    namespace detail
    {
        template <typename type>
        concept less_comparable = requires(const type& a, const type& b) {
            { a < b } -> ::std::same_as<bool>;
        };
        template <typename type, typename func>
        concept compare_function = requires(const type& a, const type& b, func f) {
            { f(a, b) } -> ::std::same_as<bool>;
        };
    }  // namespace detail

    template <::cppfastbox::detail::less_comparable type>
    constexpr inline auto& min(const type& a, const type& b) noexcept
    {
        return a < b ? a : b;
    }

    template <typename type, ::cppfastbox::detail::compare_function<type> func>
    constexpr inline auto& min(const type& a, const type& b, func f) noexcept
    {
        return f(a, b) ? a : b;
    }

    template <::cppfastbox::detail::less_comparable type>
    constexpr inline auto& max(const type& a, const type& b) noexcept
    {
        return a < b ? b : a;
    }

    template <typename type, ::cppfastbox::detail::compare_function<type> func>
    constexpr inline auto& max(const type& a, const type& b, func f) noexcept
    {
        return f(a, b) ? a : b;
    }
}  // namespace cppfastbox
