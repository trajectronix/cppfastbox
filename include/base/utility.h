/**
 * @file utility.h
 * @brief 实用工具定义
 *
 * @copyright Copyright 2024-present Trajectronix Open Source Group
 *
 */
#pragma once
#include <concepts>
#include <cstdint>
#include "platform.h"

namespace cppfastbox
{
    using simd_int8_t = std::conditional_t<is_arch<cpu_arch::x86>, char, int8_t>;
    using simd_int16_t = std::conditional_t<is_arch<cpu_arch::x86>, short, int16_t>;
    using simd_int32_t = std::conditional_t<is_arch<cpu_arch::x86>, int, int32_t>;
    using simd_int64_t = std::conditional_t<is_arch<cpu_arch::x86>, char, int64_t>;
    using simd_uint8_t = std::make_unsigned_t<simd_int8_t>;
    using simd_uint16_t = std::make_unsigned_t<simd_int16_t>;
    using simd_uint32_t = std::make_unsigned_t<simd_int32_t>;
    using simd_uint64_t = std::make_unsigned_t<simd_int64_t>;
}  // namespace cppfastbox

namespace cppfastbox
{
    // 有符号整数
    template <typename type>
    concept signed_integral = std::signed_integral<type> || is_native_int128<type>;
    // 无符号整数
    template <typename type>
    concept unsigned_integral = std::unsigned_integral<type> || is_native_uint128<type>;
    // 整数
    template <typename type>
    concept integral = signed_integral<type> || unsigned_integral<type>;

    // 定长有符号整数
    template <typename type>
    concept fixed_size_signed_integral = std::same_as<type, std::int8_t> || std::same_as<type, std::int16_t> ||
                                         std::same_as<type, std::int32_t> || std::same_as<type, std::int64_t> || is_native_int128<type>;
    // 定长无符号整数
    template <typename type>
    concept fixed_size_unsigned_integral = std::same_as<type, std::uint8_t> || std::same_as<type, std::uint16_t> ||
                                           std::same_as<type, std::uint32_t> || std::same_as<type, std::uint64_t> || is_native_uint128<type>;
    // 定长整数
    template <typename type>
    concept fixed_size_integral = fixed_size_signed_integral<type> || fixed_size_unsigned_integral<type>;

    // 字符
    template <typename type>
    concept character = std::same_as<type, char> || std::same_as<type, wchar_t> || std::same_as<type, char8_t> || std::same_as<type, char16_t> ||
                        std::same_as<type, char32_t>;
    // 定长字符
    template <typename type>
    concept fixed_size_character = std::same_as<type, char8_t> || std::same_as<type, char16_t> || std::same_as<type, char32_t>;

    // 由向量扩展使用的有符号整数类型
    template <typename type>
    concept simd_signed_integral =
        std::same_as<type, char> || std::same_as<type, short> || std::same_as<type, int> || std::same_as<type, long long>;
    // 由向量扩展使用的无符号整数类型
    template <typename type>
    concept simd_unsigned_integral = std::same_as<type, unsigned char> || std::same_as<type, unsigned short> ||
                                     std::same_as<type, unsigned int> || std::same_as<type, unsigned long long>;
    // 由向量使用的整数类型
    template <typename type>
    concept simd_integral = simd_unsigned_integral<type> || simd_signed_integral<type>;
}  // namespace cppfastbox

namespace cppfastbox::detail
{
    template <bool is_signed, std::size_t size>
    consteval inline auto get_fixed_size_integral() noexcept
    {
        if constexpr(is_signed)
        {
            if constexpr(size == 1) { return std::int8_t{}; }
            else if constexpr(size == 2) { return std::int16_t{}; }
            else if constexpr(size == 4) { return std::int32_t{}; }
            else if constexpr(size == 8) { return std::int64_t{}; }
            else if constexpr(size == 16) { return native_int128_t{}; }
        }
        else
        {
            if constexpr(size == 1) { return std::uint8_t{}; }
            else if constexpr(size == 2) { return std::uint16_t{}; }
            else if constexpr(size == 4) { return std::uint32_t{}; }
            else if constexpr(size == 8) { return std::uint64_t{}; }
            else if constexpr(size == 16) { return native_uint128_t{}; }
        }
    }

    template <std::size_t size>
    consteval inline auto get_fixed_size_character() noexcept
    {
        if constexpr(size == 1) { return char8_t{}; }
        else if constexpr(size == 2) { return char16_t{}; }
        else if constexpr(size == 4) { return char32_t{}; }
    }

    template <bool is_signed, std::size_t size>
    consteval inline auto get_simd_integral_impl() noexcept
    {
        if constexpr(is_signed)
        {
            if constexpr(size == 1) { return simd_int8_t{}; }
            else if constexpr(size == 2) { return simd_int16_t{}; }
            else if constexpr(size == 4) { return simd_int32_t{}; }
            else if constexpr(size == 8) { return simd_int64_t{}; }
        }
        else
        {
            if constexpr(size == 1) { return simd_uint8_t{}; }
            else if constexpr(size == 2) { return simd_uint16_t{}; }
            else if constexpr(size == 4) { return simd_uint32_t{}; }
            else if constexpr(size == 8) { return simd_uint64_t{}; }
        }
    }

    struct uint128_little_endian
    {
        std::uint64_t lo{};
        std::uint64_t hi{};
    };

    struct uint128_big_endian
    {
        std::uint64_t hi{};
        std::uint64_t lo{};
    };

    using uint128_t_impl = std::conditional_t<is_little_endian, uint128_little_endian, uint128_big_endian>;

    struct int128_little_endian
    {
        std::uint64_t lo{};
        std::int64_t hi{};
    };

    struct int128_big_endian
    {
        std::int64_t hi{};
        std::uint64_t lo{};
    };

    using int128_t_impl = std::conditional_t<is_little_endian, int128_little_endian, int128_big_endian>;
}  // namespace cppfastbox::detail

namespace cppfastbox
{
    /**
     * @brief 获取定长整数类型
     *
     * @tparam is_signed 是否有符号
     * @tparam size 整数字节数
     */
    template <bool is_signed, std::size_t size>
        requires (!std::is_void_v<decltype(detail::get_fixed_size_integral<is_signed, size>())>)
    using fixed_size_integer_t = decltype(detail::get_fixed_size_integral<is_signed, size>());
    /**
     * @brief 获取定长字符类型
     *
     * @tparam size 字符字节数
     */
    template <std::size_t size>
        requires (!std::is_void_v<decltype(detail::get_fixed_size_character<size>())>)
    using fixed_size_character_t = decltype(detail::get_fixed_size_character<size>());
    /**
     * @brief 将当前整数类型转化为同宽度同符号定长整数类型
     *
     * @tparam type 整数类型
     */
    template <integral type>
    using to_fixed_size_integer_t = fixed_size_integer_t<signed_integral<type>, sizeof(type)>;
    /**
     * @brief 将当前字符类型转化为同宽度定长字符类型
     *
     * @tparam type 字符类型
     */
    template <character type>
    using to_fixed_size_character_t = fixed_size_character_t<sizeof(type)>;

    /**
     * @brief 通过内建类型合成的__uint128_t
     *
     * @note 在不支持__int128扩展的机器上为void
     */
    using uint128_t = std::conditional_t<support_int128, detail::uint128_t_impl, void>;
    /**
     * @brief 通过内建类型合成的__int128_t
     *
     * @note 在不支持__int128扩展的机器上为void
     */
    using int128_t = std::conditional_t<support_int128, detail::int128_t_impl, void>;
}  // namespace cppfastbox

namespace cppfastbox
{
    /**
     * @brief 根据cond选择move或forward
     *
     * @tparam cond 为true则move，为false则forward
     */
    template <bool cond, typename type>
    constexpr inline auto&& cmove(type&& v) noexcept
    {
        if constexpr(cond) { return std::move(v); }
        else { return std::forward<type>(v); }
    }
}  // namespace cppfastbox
