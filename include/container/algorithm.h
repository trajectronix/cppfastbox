/**
 * @file algorithm.h
 * @brief
 *
 * @copyright Copyright 2024-present Trajectronix Open Source Group
 *
 */
#pragma once
#include <bit>
#include <iterator>
#include <ranges>
#include <compare>
#include "../base/utility.h"

namespace cppfastbox::detail
{
    template <typename type_in>
    struct get_bare_iterator_impl
    {
        using type = type_in;
    };

    template <typename type_in>
    struct get_bare_iterator_impl<::std::basic_const_iterator<type_in>>
    {
        using type = ::cppfastbox::detail::get_bare_iterator_impl<typename type_in::iterator_type>::type;
    };

    template <typename type_in>
    struct get_bare_iterator_impl<::std::reverse_iterator<type_in>>
    {
        using type = ::cppfastbox::detail::get_bare_iterator_impl<typename type_in::iterator_type>::type;
    };

    // 提取出底层迭代器
    template <typename type>
    using get_bare_iterator = ::cppfastbox::detail::get_bare_iterator_impl<type>::type;
}  // namespace cppfastbox::detail

namespace cppfastbox
{
    /**
     * @brief 指明一个类型是否可以使用memcmp进行三路比较
     *
     * @note 添加该类型的的特化来指明一个类型可以使用memcmp进行三路比较
     */
    template <typename type>
    constexpr inline auto is_trivially_three_way_comparable{false};
    /**
     * @brief 判断类型是否可以使用memcmp进行三路比较
     *
     * @tparam type
     */
    template <typename type>
    concept trivially_three_way_comparable =
        ::cppfastbox::is_trivially_three_way_comparable<type> ||
        (std::endian::native == std::endian::big ? ::cppfastbox::unsigned_integral<type> || ::std::is_pointer_v<type>
                                                 : ::std::same_as<type, unsigned char>);

    /**
     * @brief 指明一个类型是否可以使用memcmp进行相等比较
     *
     * @note 添加该类型的的特化来指明一个类型可以使用memcmp进行相等比较
     */
    template <typename type>
    constexpr inline auto is_trivially_equality_comparable{false};
    /**
     * @brief 判读一个类型是否可以使用memcmp进行相等比较
     *
     * @note 添加trivially_equality_comparable的特化以指明一个类型可以使用memcmp进行相等比较
     */
    template <typename type>
    concept trivially_equality_comparable =
        ::cppfastbox::integral<::std::remove_cvref_t<type>> || ::std::floating_point<::std::remove_cvref_t<type>> ||
        ::std::is_pointer_v<::std::remove_cvref_t<type>> || ::cppfastbox::is_trivially_equality_comparable<::std::remove_cvref_t<type>>;

    /**
     * @brief 指明一个类型是平凡可重定位的，即其行为不依赖自身的地址
     *
     * @tparam 添加该类型的的特化来指明一个类型不满足上述条件
     */
    template <typename type>
    constexpr inline auto is_trivially_relocatable{true};
    /**
     * @brief 判读一个类型是否是平凡可重定位的，即其行为不依赖自身的地址
     *
     * @note 添加is_trivially_relocatable的特化以指明一个类型不满足上述条件
     */
    template <typename type>
    concept trivially_relocatable = ::cppfastbox::is_trivially_relocatable<type>;
}  // namespace cppfastbox

namespace cppfastbox
{
    template <typename type>
    constexpr inline void swap(type& a, type& b) noexcept
    {
        if !consteval
        {
            if constexpr(::cppfastbox::trivially_relocatable<type>)
            {
                constexpr auto size{::std::bit_ceil(sizeof(type))};
                constexpr auto buf_size{size > 64 ? 64 : size};
                constexpr auto copy_times{sizeof(type) / buf_size};
                constexpr auto rest_size{sizeof(type) % buf_size};
                auto pa{reinterpret_cast<char*>(::std::addressof(a))};
                auto pb{reinterpret_cast<char*>(::std::addressof(b))};
                char buf[buf_size]{};
                for(auto i{0zu}; i < copy_times; i++)
                {
                    __builtin_memcpy(buf, pa, buf_size);
                    __builtin_memcpy(pa, pb, buf_size);
                    __builtin_memcpy(pb, buf, buf_size);
                    pa += buf_size, pb += buf_size;
                }
                __builtin_memcpy(buf, pa, rest_size);
                __builtin_memcpy(pa, pb, rest_size);
                __builtin_memcpy(pb, buf, rest_size);
                return;
            }
        }
        return std::ranges::swap(a, b);
    }
}  // namespace cppfastbox
