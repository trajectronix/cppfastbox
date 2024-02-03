/**
 * @file iterator.h
 * @brief 迭代器支持
 *
 * @copyright Copyright 2024-present Trajectronix Open Source Group
 *
 */
#pragma once
#include <iterator>
#include <type_traits>

namespace cppfastbox
{
    /**
     * @brief 通用连续迭代器
     *
     * @tparam Type 对象类型
     */
    template <typename type>
    struct contiguous_iterator
    {
        using value_type = ::std::remove_cv_t<type>;
        using pointer = type*;
        using const_pointer = const type*;
        using reference = type&;
        using const_reference = const type&;
        using difference_type = ::std::ptrdiff_t;
        using iterator_category = ::std::contiguous_iterator_tag;

        pointer ptr{};

        constexpr inline contiguous_iterator& operator++ () noexcept { return ++ptr, *this; }

        constexpr inline contiguous_iterator operator++ (int) noexcept { return {ptr++}; }

        constexpr inline contiguous_iterator& operator+= (difference_type diff) noexcept { return ptr += diff, *this; }

        constexpr inline contiguous_iterator& operator-- () noexcept { return --ptr, *this; }

        constexpr inline contiguous_iterator operator-- (int) noexcept { return {ptr--}; }

        constexpr inline contiguous_iterator& operator-= (difference_type diff) noexcept { return ptr -= diff, *this; }

        [[nodiscard]] constexpr inline friend reference operator* (contiguous_iterator self) noexcept { return *self.ptr; }

        [[nodiscard]] constexpr inline pointer operator->(this const auto self) noexcept { return self.ptr; }

        [[nodiscard]] constexpr inline reference operator[] (this const auto self, difference_type diff) noexcept { return self.ptr[diff]; }

        [[nodiscard]] constexpr inline friend contiguous_iterator operator+ (contiguous_iterator self, difference_type diff) noexcept
        {
            return {self.ptr + diff};
        }

        [[nodiscard]] constexpr inline friend contiguous_iterator operator+ (difference_type diff, contiguous_iterator iterator) noexcept
        {
            return {iterator.ptr + diff};
        }

        [[nodiscard]] constexpr inline friend contiguous_iterator operator- (contiguous_iterator self, difference_type diff) noexcept
        {
            return {self.ptr - diff};
        }

        [[nodiscard]] constexpr inline friend difference_type operator- (contiguous_iterator self, contiguous_iterator other) noexcept
        {
            return self.ptr - other.ptr;
        }

        [[nodiscard]] constexpr inline friend bool operator== (contiguous_iterator self, contiguous_iterator other) noexcept
        {
            return self.ptr == other.ptr;
        }

        [[nodiscard]] constexpr inline friend auto operator<=> (contiguous_iterator self, contiguous_iterator other) noexcept
        {
            return self.ptr <=> other.ptr;
        }
    };

    namespace detail
    {
        template <typename type>
        constexpr inline auto is_contiguous_iterator_impl{false};
        template <typename type>
        constexpr inline auto is_contiguous_iterator_impl<contiguous_iterator<type>>{true};
    }  // namespace detail

    /**
     * @brief 判断是否是cppfastbox::contiguous_iterator类型
     *
     */
    template <typename type>
    concept is_contiguous_iterator = detail::is_contiguous_iterator_impl<type>;
}  // namespace cppfastbox
