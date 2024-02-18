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
#include <memory>
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
    namespace detail
    {
        /**
         * @brief 平凡地交换两块内存的数据
         *
         * @tparam size 要交换的大小
         * @tparam align 内存对齐
         * @tparam unroll 循环展开深度
         * @param a 指向要交换数据的指针
         * @param b 指向要交换数据的指针
         */
        template <::std::size_t size, ::std::size_t align, ::std::size_t unroll = 4>
        inline void trivially_swap(void* a, void* b) noexcept
        {
            static_assert(::std::has_single_bit(align), "Align must be an integer power of 2.");
            using lanes_t = ::cppfastbox::native_ls_lanes;
            constexpr auto lanes{::cppfastbox::split_into_native_ls_lanes(size)};
            auto pa = reinterpret_cast<char*>(::std::assume_aligned<align>(a));
            auto pb = reinterpret_cast<char*>(::std::assume_aligned<align>(b));

            if constexpr(lanes.l64 == 1)  //< 有助于提高调试时生成汇编的质量
            {
                lanes_t::l64_t buf1{}, buf2{};
                __builtin_memcpy(&buf1, pa, 64);
                __builtin_memcpy(&buf2, pb, 64);
                __builtin_memcpy(pa, &buf2, 64);
                __builtin_memcpy(pb, &buf1, 64);
                pa += 64, pb += 64;
            }
            else if constexpr(lanes.l64 > 1)
            {
#ifdef __clang__
    #pragma clang loop unroll_count(unroll)
#else
    #pragma GCC unroll(unroll)
#endif
                for(auto i{0zu}; i < lanes.l64; i++)
                {
                    lanes_t::l64_t buf1{}, buf2{};
                    __builtin_memcpy(&buf1, pa, 64);
                    __builtin_memcpy(&buf2, pb, 64);
                    __builtin_memcpy(pa, &buf2, 64);
                    __builtin_memcpy(pb, &buf1, 64);
                    pa += 64, pb += 64;
                }
            }

            if constexpr(lanes.l32 == 1)  //< 有助于提高调试时生成汇编的质量
            {
                lanes_t::l32_t buf1{}, buf2{};
                __builtin_memcpy(&buf1, pa, 32);
                __builtin_memcpy(&buf2, pb, 32);
                __builtin_memcpy(pa, &buf2, 32);
                __builtin_memcpy(pb, &buf1, 32);
                pa += 32, pb += 32;
            }
            else if constexpr(lanes.l32 > 1)
            {
#ifdef __clang__
    #pragma clang loop unroll_count(unroll)
#else
    #pragma GCC unroll(unroll)
#endif
                for(auto i{0zu}; i < lanes.l32; i++)
                {
                    lanes_t::l32_t buf1{}, buf2{};
                    __builtin_memcpy(&buf1, pa, 32);
                    __builtin_memcpy(&buf2, pb, 32);
                    __builtin_memcpy(pa, &buf2, 32);
                    __builtin_memcpy(pb, &buf1, 32);
                    pa += 32, pb += 32;
                }
            }

            if constexpr(lanes.l16 == 1)  //< 有助于提高调试时生成汇编的质量
            {
                lanes_t::l16_t buf1{}, buf2{};
                __builtin_memcpy(&buf1, pa, 16);
                __builtin_memcpy(&buf2, pb, 16);
                __builtin_memcpy(pa, &buf2, 16);
                __builtin_memcpy(pb, &buf1, 16);
                pa += 16, pb += 16;
            }
            else if constexpr(lanes.l16 > 1)
            {
#ifdef __clang__
    #pragma clang loop unroll_count(4)
#else
    #pragma GCC unroll(4)
#endif
                for(auto i{0zu}; i < lanes.l16; i++)
                {
                    lanes_t::l16_t buf1{}, buf2{};
                    __builtin_memcpy(&buf1, pa, 16);
                    __builtin_memcpy(&buf2, pb, 16);
                    __builtin_memcpy(pa, &buf2, 16);
                    __builtin_memcpy(pb, &buf1, 16);
                    pa += 16, pb += 16;
                }
            }

            if constexpr(lanes.l8 == 1)  //< 有助于提高调试时生成汇编的质量
            {
                lanes_t::l8_t buf1{}, buf2{};
                __builtin_memcpy(&buf1, pa, 8);
                __builtin_memcpy(&buf2, pb, 8);
                __builtin_memcpy(pa, &buf2, 8);
                __builtin_memcpy(pb, &buf1, 8);
                pa += 8, pb += 8;
            }
            else if constexpr(lanes.l8 > 1)
            {
#ifdef __clang__
    #pragma clang loop unroll_count(4)
#else
    #pragma GCC unroll(4)
#endif
                for(auto i{0zu}; i < lanes.l8; i++)
                {
                    lanes_t::l8_t buf1{}, buf2{};
                    __builtin_memcpy(&buf1, pa, 8);
                    __builtin_memcpy(&buf2, pb, 8);
                    __builtin_memcpy(pa, &buf2, 8);
                    __builtin_memcpy(pb, &buf1, 8);
                    pa += 8, pb += 8;
                }
            }

            if constexpr(lanes.l4 == 1)  //< 有助于提高调试时生成汇编的质量
            {
                lanes_t::l4_t buf1{}, buf2{};
                __builtin_memcpy(&buf1, pa, 4);
                __builtin_memcpy(&buf2, pb, 4);
                __builtin_memcpy(pa, &buf2, 4);
                __builtin_memcpy(pb, &buf1, 4);
                pa += 4, pb += 4;
            }
            else if constexpr(lanes.l4 > 1)
            {
#ifdef __clang__
    #pragma clang loop unroll_count(4)
#else
    #pragma GCC unroll(4)
#endif
                for(auto i{0zu}; i < lanes.l4; i++)
                {
                    lanes_t::l4_t buf1{}, buf2{};
                    __builtin_memcpy(&buf1, pa, 4);
                    __builtin_memcpy(&buf2, pb, 4);
                    __builtin_memcpy(pa, &buf2, 4);
                    __builtin_memcpy(pb, &buf1, 4);
                    pa += 4, pb += 4;
                }
            }

            // 硬件支持的最大读写通道大小不小于4字节，故1字节和2字节的读写至多发生一次
            if constexpr(lanes.l2 == 1)  //< 有助于提高调试时生成汇编的质量
            {
                lanes_t::l2_t buf1{}, buf2{};
                __builtin_memcpy(&buf1, pa, 2);
                __builtin_memcpy(&buf2, pb, 2);
                __builtin_memcpy(pa, &buf2, 2);
                __builtin_memcpy(pb, &buf1, 2);
                pa += 2, pb += 2;
            }

            if constexpr(lanes.l1 == 1)  //< 有助于提高调试时生成汇编的质量
            {
                lanes_t::l1_t buf1{}, buf2{};
                __builtin_memcpy(&buf1, pa, 1);
                __builtin_memcpy(&buf2, pb, 1);
                __builtin_memcpy(pa, &buf2, 1);
                __builtin_memcpy(pb, &buf1, 1);
            }
        }
    }  // namespace detail

    /**
     * @brief 平凡地交换两个对象
     *
     * @tparam align 内存对齐，为0使用`type`的对齐
     * @tparam unroll 循环展开深度
     * @tparam type 对象类型
     * @param a 对象引用
     * @param b 对象引用
     */
    template <::std::size_t align = 0, ::std::size_t unroll = 4, typename type>
    inline void trivially_swap(type& a, type& b) noexcept
    {
        static_assert(align == 0 || ::std::has_single_bit(align), "Align must be 0(use align of type) or an integer power of 2.");
        ::cppfastbox::detail::trivially_swap<sizeof(type), align == 0 ? alignof(type) : align>(::std::addressof(a), ::std::addressof(b));
    }
}  // namespace cppfastbox
