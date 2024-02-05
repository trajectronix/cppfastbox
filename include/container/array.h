/**
 * @file array.h
 * @brief 数组及多维数组实现
 *
 * @copyright Copyright 2024-present Trajectronix Open Source Group
 *
 */
#pragma once
#include <iterator>
#include "../libc/assert.h"
#include "../base/utility.h"

/**
 * @brief 一维数组实现
 *
 */
namespace cppfastbox
{
    template <typename type, ::std::size_t... next>
    struct array;

    template <typename type, ::std::size_t n>
        requires (n != 0)
    struct array<type, n>
    {
        using value_type = ::std::remove_cv_t<type>;
        using pointer = type*;
        using const_pointer = const type*;
        using reference = type&;
        using const_reference = const type&;
        using size_type = ::std::size_t;
        using difference_type = ::std::ptrdiff_t;
        using native_array_type = type[n];
        native_array_type array{};

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
            return cmove<::std::is_rvalue_reference_v<decltype(self)>>(self.array[index]);
        }

        using iterator = pointer;
        using const_iterator = const_pointer;
        using reverse_iterator = ::std::reverse_iterator<iterator>;
        using const_reverse_iterator = ::std::reverse_iterator<const_iterator>;

        [[nodiscard]] constexpr inline auto begin(this auto&& self) noexcept { return self.array; }

        [[nodiscard]] constexpr inline auto cbegin(this const auto& self) noexcept { return self.begin(); }

        [[nodiscard]] constexpr inline auto end(this auto&& self) noexcept { return self.array + n; }

        [[nodiscard]] constexpr inline auto cend(this const auto& self) noexcept { return self.end(); }

        [[nodiscard]] constexpr inline auto rbegin(this auto&& self) noexcept { return ::std::reverse_iterator{self.end()}; }

        [[nodiscard]] constexpr inline auto crbegin(this const auto& self) noexcept { return self.rbegin(); }

        [[nodiscard]] constexpr inline auto rend(this auto&& self) noexcept { return ::std::reverse_iterator{self.begin()}; }

        [[nodiscard]] constexpr inline auto crend(this const auto& self) noexcept { return self.rend(); }
    };

    // 一维数组推导指引
    template <typename type, typename... next>
        requires (::std::same_as<type, next> && ...)
    array(type, next...) -> ::cppfastbox::array<type, 1 + sizeof...(next)>;
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
        using value_type = ::std::remove_cv_t<type>;
        using pointer = type*;
        using const_pointer = const type*;
        using reference = type&;
        using const_reference = const type&;
        using size_type = ::std::size_t;
        using difference_type = ::std::ptrdiff_t;

        [[nodiscard]] consteval inline static bool empty() noexcept { return true; }

        [[nodiscard]] consteval inline static size_type size() noexcept { return 0; }

        [[nodiscard]] consteval inline static size_type maxSize() noexcept { return size(); }

        // 获取维度总数
        [[nodiscard]] consteval inline static size_type rank() noexcept { return 0; }

        [[nodiscard]] constexpr inline auto data(this auto&& self) noexcept
        {
            return ::std::conditional_t<::std::is_const_v<decltype(self)>, const_pointer, pointer>{};
        }

        using iterator = pointer;
        using const_iterator = const_pointer;
        using reverse_iterator = ::std::reverse_iterator<iterator>;
        using const_reverse_iterator = ::std::reverse_iterator<const_iterator>;

        [[nodiscard]] constexpr inline auto begin(this auto&& self) noexcept
        {
            return ::std::conditional_t<::std::is_const_v<decltype(self)>, const_iterator, iterator>{};
        }

        [[nodiscard]] constexpr inline auto cbegin(this const auto& self) noexcept { return self.begin(); }

        [[nodiscard]] constexpr inline auto end(this auto&& self) noexcept
        {
            return ::std::conditional_t<::std::is_const_v<decltype(self)>, const_iterator, iterator>{};
        }

        [[nodiscard]] constexpr inline auto rbegin(this auto&& self) noexcept
        {
            return ::std::conditional_t<::std::is_const_v<decltype(self)>, const_iterator, iterator>{};
        }

        [[nodiscard]] constexpr inline auto crbegin(this const auto& self) noexcept { return self.begin(); }

        [[nodiscard]] constexpr inline auto rend(this auto&& self) noexcept
        {
            return ::std::conditional_t<::std::is_const_v<decltype(self)>, const_iterator, iterator>{};
        }

        [[nodiscard]] constexpr inline auto crend(this const auto& self) noexcept { return self.end(); }
    };

    template <typename type, ::std::size_t n, ::std::size_t... next>
        requires (n == 0 || ((next == 0) || ...))
    struct array<type, n, next...> : ::cppfastbox::array<type>
    {
        using value_type = ::std::remove_cv_t<type>;
        using pointer = type*;
        using const_pointer = const type*;
        using reference = type&;
        using const_reference = const type&;
        using size_type = ::std::size_t;
        using difference_type = ::std::ptrdiff_t;
        using iterator = pointer;
        using const_iterator = const_pointer;
        using reverse_iterator = ::std::reverse_iterator<iterator>;
        using const_reverse_iterator = ::std::reverse_iterator<const_iterator>;

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
            return 0zu;
        }
    };
}  // namespace cppfastbox

namespace cppfastbox::detail
{
    template <typename type_in, ::std::size_t n, ::std::size_t... next>
    struct make_native_array_from_sequence_impl
    {
        using type = make_native_array_from_sequence_impl<type_in, next...>::type[n];
    };

    template <typename type_in, ::std::size_t n>
    struct make_native_array_from_sequence_impl<type_in, n>
    {
        using type = type_in[n];
    };

    template <typename type_in, ::std::size_t... next>
    using make_native_array_from_sequence = ::cppfastbox::detail::make_native_array_from_sequence_impl<type_in, next...>::type;

    template <::std::size_t n>
    inline consteval auto get_stride_per_extent(const ::std::size_t (&n_per_extent)[n]) noexcept
    {
        ::cppfastbox::array<::std::size_t, n> stride_per_extent{};
        for(auto i{0zu}; i < n; i++)
        {
            auto stride = 1zu;
            for(auto j{i + 1}; j < n; j++) { stride *= n_per_extent[j]; }
            stride_per_extent[i] = stride;
        }
        return stride_per_extent;
    }

    constexpr inline auto&& get_value_from_native_array(auto&& array, ::std::size_t index, auto... index_next) noexcept
    {
        constexpr auto extent{::std::extent_v<::std::remove_reference_t<decltype(array)>>};
        constexpr auto is_rvalue{::std::is_rvalue_reference_v<decltype(array)>};
        ::cppfastbox::assert(index < extent);
        if constexpr(sizeof...(index_next) == 0) { return cmove<is_rvalue>(array[index]); }
        else { return get_value_from_native_array(cmove<is_rvalue>(array[index]), index_next...); }
    }
}  // namespace cppfastbox::detail

/**
 * @brief 多维数组实现
 *
 */
namespace cppfastbox
{
    template <typename type, ::std::size_t n, ::std::size_t... next>
        requires (n != 0 && ((next != 0) && ...))
    struct array<type, n, next...>
    {
        using value_type = ::std::remove_cv_t<type>;
        using pointer = type*;
        using const_pointer = const type*;
        using reference = type&;
        using const_reference = const type&;
        using size_type = ::std::size_t;
        using difference_type = ::std::ptrdiff_t;
        using native_array_type = detail::make_native_array_from_sequence<type, n, next...>;
        using sub_array_type = ::std::remove_extent_t<native_array_type>;
        native_array_type array{};

        // 获取维度总数
        [[nodiscard]] consteval inline static size_type rank() noexcept { return sizeof...(next) + 1; }

        // 每维度上的元素个数
        constexpr inline static size_type n_per_extent[rank()]{n, next...};

        constexpr inline static auto stride_per_extent{detail::get_stride_per_extent(n_per_extent)};

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

        [[nodiscard]] constexpr inline auto data(this auto&& self) noexcept { return self.array; }

        [[nodiscard]] constexpr inline auto&& front(this auto&& self) noexcept { return self.array[0]; }

        [[nodiscard]] constexpr inline auto&& back(this auto&& self) noexcept { return self.array[n - 1]; }

        using iterator = sub_array_type;
        using const_iterator = const sub_array_type;
        using reverse_iterator = ::std::reverse_iterator<iterator>;
        using const_reverse_iterator = ::std::reverse_iterator<const_iterator>;

        [[nodiscard]] constexpr inline auto&& operator[] (this auto&& self, ::std::size_t index, ::std::integral auto... index_next) noexcept
        {
            return detail::get_value_from_native_array(cmove<::std::is_rvalue_reference_v<decltype(self)>>(self.array), index, index_next...);
        }

        [[nodiscard]] constexpr inline auto begin(this auto&& self) noexcept { return self.array; }

        [[nodiscard]] constexpr inline auto cbegin(this const auto& self) noexcept { return self.begin(); }

        [[nodiscard]] constexpr inline auto end(this auto&& self) noexcept { return self.array + n; }

        [[nodiscard]] constexpr inline auto cend(this const auto& self) noexcept { return self.end(); }

        [[nodiscard]] constexpr inline auto rbegin(this auto&& self) noexcept { return ::std::reverse_iterator{self.end()}; }

        [[nodiscard]] constexpr inline auto crbegin(this const auto& self) noexcept { return self.rbegin(); }

        [[nodiscard]] constexpr inline auto rend(this auto&& self) noexcept { return ::std::reverse_iterator{self.begin()}; }

        [[nodiscard]] constexpr inline auto crend(this const auto& self) noexcept { return self.rend(); }
    };
}  // namespace cppfastbox

namespace cppfastbox::detail
{
    /**
     * @brief 从原生数组中获取array类型
     *
     * @tparam native_array 原生数组类型
     * @tparam value_type 原生数组的元素类型
     * @tparam n 每维度元素数
     */
    template <typename native_array, typename value_type, ::std::size_t... n>
    struct make_array_from_native_impl
    {
        using next = ::std::remove_extent_t<native_array>;
        using type = make_array_from_native_impl<::std::conditional_t<::std::rank_v<native_array> != 1, next, void>,
                                                 next,  //< 最后一维时此处为原生数组的元素类型
                                                 n...,
                                                 ::std::extent_v<native_array>>::type;
    };

    template <typename value_type, ::std::size_t... n>
    struct make_array_from_native_impl<void, value_type, n...>
    {
        using type = ::cppfastbox::array<::std::remove_cv_t<value_type>, n...>;
    };

    template <typename native_array>
    using make_array_from_native = ::cppfastbox::detail::make_array_from_native_impl<native_array, void>::type;

    /**
     * @brief 在编译期拷贝原生数组
     *
     * @param to 目标数组
     * @param from 原数组
     */
    template <typename type>
    consteval inline void copy_native_array(type&& to, type&& from) noexcept
    {
        using array_type = ::std::remove_reference_t<type>;
        constexpr auto extent{::std::extent_v<array_type>};
        for(auto i{0zu}; i < extent; i++)
        {
            if constexpr(::std::rank_v<array_type> == 1) { to[i] = from[i]; }
            else { ::cppfastbox::detail::copy_native_array(to[i], from[i]); }
        }
    }
}  // namespace cppfastbox::detail

namespace cppfastbox
{
    /**
     * @brief 拷贝原生数组
     *
     * @param to 目标数组
     * @param from 原数组
     */
    template <typename type>
    constexpr inline void copy_native_array(type&& to, type&& from) noexcept
    {
        static_assert(::std::is_bounded_array_v<::std::remove_reference_t<type>>, "Function arguments should be native arrays.");
        if consteval { ::cppfastbox::detail::copy_native_array(to, from); }
        else { __builtin_memcpy(::std::addressof(to), ::std::addressof(from), sizeof(to)); }
    }

    /**
     * @brief 从原生数组中构造array类型
     *
     */
    template <typename type>
    [[nodiscard]] constexpr inline auto make_array(type&& native_array) noexcept
    {
        static_assert(::std::is_bounded_array_v<::std::remove_reference_t<type>>, "The function argument should be a native array.");
        using array_type = ::cppfastbox::detail::make_array_from_native<::std::remove_reference_t<type>>;
        array_type array{};
        ::cppfastbox::copy_native_array(array.array, native_array);
        return array;
    }
}  // namespace cppfastbox

namespace cppfastbox::detail
{
    template <typename type>
    constexpr inline auto is_array_impl{false};
    template <typename type, ::std::size_t... n>
    constexpr inline auto is_array_impl<::cppfastbox::array<type, n...>>{true};
    template <typename type, ::std::size_t... n>
    constexpr inline auto is_array_impl<const ::cppfastbox::array<type, n...>>{true};
    template <typename type, ::std::size_t... n>
    constexpr inline auto is_array_impl<volatile ::cppfastbox::array<type, n...>>{true};
    template <typename type, ::std::size_t... n>
    constexpr inline auto is_array_impl<const volatile ::cppfastbox::array<type, n...>>{true};
}  // namespace cppfastbox::detail

namespace cppfastbox
{
    /**
     * @brief 判断是否是::cppfastbox::array类型
     *
     */
    template <typename type>
    concept is_array = detail::is_array_impl<type>;

    template <::std::size_t index, typename type>
        requires (::cppfastbox::is_array<::std::remove_reference_t<type>>)
    constexpr inline auto&& get(type&& array) noexcept
    {
        static_assert(index < ::std::remove_reference_t<type>::extent(0), "The subscript is out of bounds.");
        return ::std::forward<type>(array)[index];
    }
}  // namespace cppfastbox

namespace std
{
    template <size_t index, typename type_in, ::std::size_t n, ::std::size_t... next>
    struct tuple_element<index, ::cppfastbox::array<type_in, n, next...>>
    {
        static_assert(n != 0 && ((next != 0) && ...), "The array must be non-empty.");
        static_assert(index < n, "The subscript is out of bounds.");
        using type = ::std::remove_extent_t<typename ::cppfastbox::array<type_in, n, next...>::native_array_type>;
    };

    template <typename type, ::std::size_t n, ::std::size_t... next>
        requires (n != 0 && ((next != 0) && ...))
    struct tuple_size<::cppfastbox::array<type, n, next...>> : ::std::integral_constant<::std::size_t, n>
    {
    };

    template <typename type, ::std::size_t... n>
        requires ((n == 0) || ...)
    struct tuple_size<::cppfastbox::array<type, n...>> : ::std::integral_constant<::std::size_t, 0>
    {
    };
}  // namespace std
