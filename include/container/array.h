/**
 * @file array.h
 * @brief 数组及多维数组实现
 *
 * @copyright Copyright 2024-present Trajectronix Open Source Group
 *
 */
#pragma once
#include "iterator.h"
#include "../libc/assert.h"

/**
 * @brief 一维数组实现
 *
 */
namespace cppfastbox
{
    template <typename type, std::size_t... next>
    struct array;

    template <typename type, ::std::size_t n>
        requires (n != 0)
    struct array<type, n>
    {
        using value_type = std::remove_cv_t<type>;
        using pointer = type*;
        using const_pointer = const type*;
        using reference = type&;
        using const_reference = const type&;
        using size_type = ::std::size_t;
        using difference_type = ::std::ptrdiff_t;
        type array[n]{};

        // 每维度上的元素个数
        constexpr inline static size_type n_per_extent[1]{n};

        [[nodiscard]] consteval inline static bool empty() noexcept { return false; }

        [[nodiscard]] consteval inline static size_type size() noexcept { return n; }

        [[nodiscard]] consteval inline static size_type maxSize() noexcept { return size(); }

        // 获取维度总数
        [[nodiscard]] consteval inline static size_type rank() noexcept { return 1zu; }

        /**
         * @brief 获取指定维度上元素的个数
         *
         * @param extentToInquire 要查询的维度，从0开始计数
         */
        [[nodiscard]] inline static constexpr size_type extent(size_type extentToInquire) noexcept
        {
            assert(extentToInquire < rank());
            return n;
        }

        /**
         * @brief 获取指定维度的步长
         *
         * @param extentToInquire 要查询的维度，从0开始计数
         */
        [[nodiscard]] inline static constexpr size_type stride(size_type extentToInquire) noexcept
        {
            assert(extentToInquire < rank());
            return n;
        }

        [[nodiscard]] constexpr inline auto data(this auto&& self) noexcept { return self.array; }

        [[nodiscard]] constexpr inline auto&& front(this auto&& self) noexcept { return self.array[0]; }

        [[nodiscard]] constexpr inline auto&& back(this auto&& self) noexcept { return self.array[n - 1]; }

        [[nodiscard]] constexpr inline auto&& operator[] (this auto&& self, size_type index) noexcept
        {
            assert(index < n);
            return self.array[index];
        }

        using iterator = contiguous_iterator<type>;
        using const_iterator = contiguous_iterator<const type>;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        [[nodiscard]] constexpr inline auto begin(this auto&& self) noexcept { return contiguous_iterator{self.array}; }

        [[nodiscard]] constexpr inline auto cbegin(this const auto& self) noexcept { return self.begin(); }

        [[nodiscard]] constexpr inline auto end(this auto&& self) noexcept { return contiguous_iterator{self.array + n}; }

        [[nodiscard]] constexpr inline auto cend(this const auto& self) noexcept { return self.end(); }

        [[nodiscard]] constexpr inline auto rbegin(this auto&& self) noexcept { return std::reverse_iterator{self.end()}; }

        [[nodiscard]] constexpr inline auto crbegin(this const auto& self) noexcept { return self.rbegin(); }

        [[nodiscard]] constexpr inline auto rend(this auto&& self) noexcept { return std::reverse_iterator{self.begin()}; }

        [[nodiscard]] constexpr inline auto crend(this const auto& self) noexcept { return self.rend(); }
    };

    // 一维数组推导指引
    template <typename type, typename... next>
        requires (::std::same_as<type, next> && ...)
    array(type, next...) -> array<type, 1 + sizeof...(next)>;
}  // namespace cppfastbox

/**
 * @brief 空数组实现
 *
 */
namespace cppfastbox
{
    template <typename type>
    struct array<type>
    {
        using value_type = std::remove_cv_t<type>;
        using pointer = type*;
        using const_pointer = const type*;
        using reference = type&;
        using const_reference = const type&;
        using size_type = ::std::size_t;
        using difference_type = ::std::ptrdiff_t;
        type array[0]{};

        // 每维度上的元素个数
        constexpr inline static size_type n_per_extent[0]{};

        [[nodiscard]] consteval inline static bool empty() noexcept { return true; }

        [[nodiscard]] consteval inline static size_type size() noexcept { return 0; }

        [[nodiscard]] consteval inline static size_type maxSize() noexcept { return size(); }

        // 获取维度总数
        [[nodiscard]] consteval inline static size_type rank() noexcept { return 0; }
        // 0维，维度上元素的个数恒为0
        [[nodiscard]] inline static constexpr size_type extent(size_type) noexcept { return 0; }

        [[nodiscard]] constexpr inline auto data(this auto&& self) noexcept
        {
            return std::conditional_t<std::is_const_v<decltype(self)>, const_pointer, pointer>{};
        }

        using iterator = contiguous_iterator<type>;
        using const_iterator = contiguous_iterator<const type>;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        [[nodiscard]] constexpr inline auto begin(this auto&& self) noexcept
        {
            return std::conditional_t<std::is_const_v<decltype(self)>, const_iterator, iterator>{};
        }

        [[nodiscard]] constexpr inline auto cbegin(this const auto& self) noexcept { return self.begin(); }

        [[nodiscard]] constexpr inline auto end(this auto&& self) noexcept
        {
            return std::conditional_t<std::is_const_v<decltype(self)>, const_iterator, iterator>{};
        }

        [[nodiscard]] constexpr inline auto rbegin(this auto&& self) noexcept
        {
            return std::conditional_t<std::is_const_v<decltype(self)>, const_iterator, iterator>{};
        }

        [[nodiscard]] constexpr inline auto crbegin(this const auto& self) noexcept { return self.begin(); }

        [[nodiscard]] constexpr inline auto rend(this auto&& self) noexcept
        {
            return std::conditional_t<std::is_const_v<decltype(self)>, const_iterator, iterator>{};
        }

        [[nodiscard]] constexpr inline auto crend(this const auto& self) noexcept { return self.end(); }
    };

    template <typename type, ::std::size_t n, std::size_t... next>
        requires (n == 0 || ((next == 0) || ...))
    struct array<type, n, next...> : array<type>
    {
        using value_type = std::remove_cv_t<type>;
        using pointer = type*;
        using const_pointer = const type*;
        using reference = type&;
        using const_reference = const type&;
        using size_type = ::std::size_t;
        using difference_type = ::std::ptrdiff_t;
        using iterator = contiguous_iterator<type>;
        using const_iterator = contiguous_iterator<const type>;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        // 获取维度总数
        [[nodiscard]] consteval inline static size_type rank() noexcept { return sizeof...(next) + 1; }

        // 每维度上的元素个数
        constexpr inline static size_type n_per_extent[rank()]{n, next...};

        /**
         * @brief 获取指定维度上元素的个数
         *
         * @param extentToInquire 要查询的维度，从0开始计数
         */
        [[nodiscard]] inline static constexpr size_type extent(size_type extentToInquire) noexcept
        {
            assert(extentToInquire < rank());
            return n_per_extent[extentToInquire];
        }

        /**
         * @brief 获取指定维度的步长
         *
         * @param extentToInquire 要查询的维度，从0开始计数
         */
        [[nodiscard]] inline static constexpr size_type stride(size_type extentToInquire) noexcept
        {
            assert(extentToInquire < rank());
            return n_per_extent[extentToInquire];
        }
    };
}  // namespace cppfastbox
