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
    using simd_int8_t = ::std::conditional_t<::cppfastbox::is_arch<::cppfastbox::cpu_arch::x86>, char, int8_t>;
    using simd_int16_t = ::std::conditional_t<::cppfastbox::is_arch<::cppfastbox::cpu_arch::x86>, short, int16_t>;
    using simd_int32_t = ::std::conditional_t<::cppfastbox::is_arch<::cppfastbox::cpu_arch::x86>, int, int32_t>;
    using simd_int64_t = ::std::conditional_t<::cppfastbox::is_arch<::cppfastbox::cpu_arch::x86>, char, int64_t>;
    using simd_uint8_t = ::std::make_unsigned_t<::cppfastbox::simd_int8_t>;
    using simd_uint16_t = ::std::make_unsigned_t<::cppfastbox::simd_int16_t>;
    using simd_uint32_t = ::std::make_unsigned_t<::cppfastbox::simd_int32_t>;
    using simd_uint64_t = ::std::make_unsigned_t<::cppfastbox::simd_int64_t>;
}  // namespace cppfastbox

namespace cppfastbox
{
    // 有符号整数
    template <typename type>
    concept signed_integral = ::std::signed_integral<type> || ::cppfastbox::is_native_int128<type>;
    // 无符号整数
    template <typename type>
    concept unsigned_integral = ::std::unsigned_integral<type> || ::cppfastbox::is_native_uint128<type>;
    // 整数
    template <typename type>
    concept integral = ::cppfastbox::signed_integral<type> || ::cppfastbox::unsigned_integral<type>;

    // 定长有符号整数
    template <typename type>
    concept fixed_size_signed_integral =
        ::std::same_as<type, ::std::int8_t> || ::std::same_as<type, ::std::int16_t> || ::std::same_as<type, ::std::int32_t> ||
        ::std::same_as<type, ::std::int64_t> || ::cppfastbox::is_native_int128<type>;
    // 定长无符号整数
    template <typename type>
    concept fixed_size_unsigned_integral =
        ::std::same_as<type, ::std::uint8_t> || ::std::same_as<type, ::std::uint16_t> || ::std::same_as<type, ::std::uint32_t> ||
        ::std::same_as<type, ::std::uint64_t> || ::cppfastbox::is_native_uint128<type>;
    // 定长整数
    template <typename type>
    concept fixed_size_integral = ::cppfastbox::fixed_size_signed_integral<type> || ::cppfastbox::fixed_size_unsigned_integral<type>;

    // 字符
    template <typename type>
    concept character = ::std::same_as<type, char> || ::std::same_as<type, wchar_t> || ::std::same_as<type, char8_t> ||
                        ::std::same_as<type, char16_t> || ::std::same_as<type, char32_t>;
    // 定长字符
    template <typename type>
    concept fixed_size_character = ::std::same_as<type, char8_t> || ::std::same_as<type, char16_t> || ::std::same_as<type, char32_t>;

    // 由向量扩展使用的有符号整数类型
    template <typename type>
    concept simd_signed_integral = ::std::same_as<type, ::cppfastbox::simd_int8_t> || ::std::same_as<type, ::cppfastbox::simd_int16_t> ||
                                   ::std::same_as<type, ::cppfastbox::simd_int32_t> || ::std::same_as<type, ::cppfastbox::simd_int64_t>;
    // 由向量扩展使用的无符号整数类型
    template <typename type>
    concept simd_unsigned_integral = ::std::same_as<type, ::cppfastbox::simd_uint8_t> || ::std::same_as<type, ::cppfastbox::simd_uint16_t> ||
                                     ::std::same_as<type, ::cppfastbox::simd_uint32_t> || ::std::same_as<type, ::cppfastbox::simd_uint64_t>;
    // 由向量使用的整数类型
    template <typename type>
    concept simd_integral = ::cppfastbox::simd_unsigned_integral<type> || ::cppfastbox::simd_signed_integral<type>;

    // 浮点数类型
    template <typename type>
    concept floating_point = ::std::floating_point<type> || ::cppfastbox::is_native_float128<type>;
}  // namespace cppfastbox

namespace cppfastbox::detail
{
    template <bool is_signed, ::std::size_t size>
    consteval inline auto get_fixed_size_integral() noexcept
    {
        if constexpr(is_signed)
        {
            if constexpr(size == 1) { return ::std::int8_t{}; }
            else if constexpr(size == 2) { return ::std::int16_t{}; }
            else if constexpr(size == 4) { return ::std::int32_t{}; }
            else if constexpr(size == 8) { return ::std::int64_t{}; }
            else if constexpr(size == 16) { return ::cppfastbox::native_int128_t{}; }
        }
        else
        {
            if constexpr(size == 1) { return ::std::uint8_t{}; }
            else if constexpr(size == 2) { return ::std::uint16_t{}; }
            else if constexpr(size == 4) { return ::std::uint32_t{}; }
            else if constexpr(size == 8) { return ::std::uint64_t{}; }
            else if constexpr(size == 16) { return ::cppfastbox::native_uint128_t{}; }
        }
    }

    template <::std::size_t size>
    consteval inline auto get_fixed_size_character() noexcept
    {
        if constexpr(size == 1) { return char8_t{}; }
        else if constexpr(size == 2) { return char16_t{}; }
        else if constexpr(size == 4) { return char32_t{}; }
    }

    template <bool is_signed, ::std::size_t size>
    consteval inline auto get_simd_integral_impl() noexcept
    {
        if constexpr(is_signed)
        {
            if constexpr(size == 1) { return ::cppfastbox::simd_int8_t{}; }
            else if constexpr(size == 2) { return ::cppfastbox::simd_int16_t{}; }
            else if constexpr(size == 4) { return ::cppfastbox::simd_int32_t{}; }
            else if constexpr(size == 8) { return ::cppfastbox::simd_int64_t{}; }
        }
        else
        {
            if constexpr(size == 1) { return ::cppfastbox::simd_uint8_t{}; }
            else if constexpr(size == 2) { return ::cppfastbox::simd_uint16_t{}; }
            else if constexpr(size == 4) { return ::cppfastbox::simd_uint32_t{}; }
            else if constexpr(size == 8) { return ::cppfastbox::simd_uint64_t{}; }
        }
    }

    struct uint128_little_endian
    {
        ::std::uint64_t lo{};
        ::std::uint64_t hi{};
    };

    struct uint128_big_endian
    {
        ::std::uint64_t hi{};
        ::std::uint64_t lo{};
    };

    using uint128_t_impl = ::std::
        conditional_t<::cppfastbox::is_little_endian, ::cppfastbox::detail::uint128_little_endian, ::cppfastbox::detail::uint128_big_endian>;

    struct int128_little_endian
    {
        ::std::uint64_t lo{};
        ::std::int64_t hi{};
    };

    struct int128_big_endian
    {
        ::std::int64_t hi{};
        ::std::uint64_t lo{};
    };

    using int128_t_impl = ::std::
        conditional_t<::cppfastbox::is_little_endian, ::cppfastbox::detail::int128_little_endian, ::cppfastbox::detail::int128_big_endian>;
}  // namespace cppfastbox::detail

namespace cppfastbox
{
    /**
     * @brief 获取定长整数类型
     *
     * @tparam is_signed 是否有符号
     * @tparam size 整数字节数
     */
    template <bool is_signed, ::std::size_t size>
        requires (!::std::is_void_v<decltype(::cppfastbox::detail::get_fixed_size_integral<is_signed, size>())>)
    using fixed_size_integer_t = decltype(::cppfastbox::detail::get_fixed_size_integral<is_signed, size>());
    /**
     * @brief 获取定长字符类型
     *
     * @tparam size 字符字节数
     */
    template <::std::size_t size>
        requires (!::std::is_void_v<decltype(::cppfastbox::detail::get_fixed_size_character<size>())>)
    using fixed_size_character_t = decltype(::cppfastbox::detail::get_fixed_size_character<size>());
    /**
     * @brief 将当前整数类型转化为同宽度同符号定长整数类型
     *
     * @tparam type 整数类型
     */
    template <::cppfastbox::integral type>
    using to_fixed_size_integer_t = ::cppfastbox::fixed_size_integer_t<::cppfastbox::signed_integral<type>, sizeof(type)>;
    /**
     * @brief 将当前字符类型转化为同宽度定长字符类型
     *
     * @tparam type 字符类型
     */
    template <::cppfastbox::character type>
    using to_fixed_size_character_t = ::cppfastbox::fixed_size_character_t<sizeof(type)>;

    /**
     * @brief 通过内建类型合成的__uint128_t
     *
     * @note 在不支持__int128扩展的机器上为void
     */
    using uint128_t = ::std::conditional_t<::cppfastbox::support_int128, ::cppfastbox::detail::uint128_t_impl, void>;
    /**
     * @brief 通过内建类型合成的__int128_t
     *
     * @note 在不支持__int128扩展的机器上为void
     */
    using int128_t = ::std::conditional_t<::cppfastbox::support_int128, ::cppfastbox::detail::int128_t_impl, void>;
}  // namespace cppfastbox

namespace cppfastbox
{
    /**
     * @brief 根据`is_move`选择move或forward
     * 等价于decltype(cond_move_v<is_move>(std::declval<type>()))
     *
     * @tparam is_move 为true则move，为false则forward
     * @code {.cpp}
     * cond_move_v<true, int> -> move, int&&
     * cond_move_v<true, int&> -> move, int&&
     * cond_move_v<true, int&&> -> move, int&&
     * cond_move_v<false, int> -> forward, int&&
     * cond_move_v<false, int&> -> forward, int&
     * cond_move_v<false, int&&> -> forward, int&&
     * @endcode
     *
     */
    template <bool is_move, typename type>
    using cond_move_t = ::std::conditional_t<
        is_move,
        ::std::add_rvalue_reference_t<::std::remove_reference_t<type>>,
        ::std::conditional_t<::std::is_reference_v<type>, type, ::std::add_rvalue_reference_t<::std::remove_reference_t<type>>>>;

    /**
     * @brief 根据`is_move`选择move或forward
     *
     * @tparam is_move 为true则move，为false则forward
     * @code {.cpp}
     * cond_move_v<true, int> -> move, int&&
     * cond_move_v<true, int&> -> move, int&&
     * cond_move_v<false, int> -> forward, int&&
     * cond_move_v<false, int&> -> forward, int&
     * @endcode
     *
     */
    template <bool is_move, typename type>
    constexpr inline auto&& cond_move_v(type&& v) noexcept
    {
        if constexpr(is_move) { return ::std::move(v); }
        else { return ::std::forward<type>(v); }
    }

    /**
     * @brief 根据`is_rvalue`选择左值引用或右值引用
     *
     * @tparam is_rvalue 为true则为右值引用，为false则为左值引用
     * @code {.cpp}
     * cond_forward_v<true, int> -> int&&
     * cond_forward_v<false, int> -> int&
     * @endcode
     *
     */
    template <bool is_rvalue, typename type>
    using cond_forward_t = ::std::conditional_t<is_rvalue,
                                                ::std::add_rvalue_reference_t<::std::remove_reference_t<type>>,
                                                ::std::add_lvalue_reference_t<::std::remove_reference_t<type>>>;

    /**
     * @brief 根据`is_rvalue`选择左值引用或右值引用
     *
     * @tparam is_rvalue 为true则为右值引用，为false则为左值引用
     * @code {.cpp}
     * cond_forward_v<true, int> -> int&&
     * cond_forward_v<false, int> -> int&
     * @endcode
     *
     */
    template <bool is_rvalue, typename type>
    constexpr inline auto&& cond_forward_v(type&& v) noexcept
    {
        using reference = ::cppfastbox::cond_forward_t<is_rvalue, type>;
        return static_cast<reference>(v);
    }

    /**
     * @brief 移除const限定并转发
     *
     * @tparam type 输入类型
     * @tparam default_type 输入类型不带有const限定时要返回的类型
     * @tparam forward_type 输入类型带有const限定时要转发到的类型
     * @code {.cpp}
     * template<typename type> struct impl{};
     * template<typename type>
     * struct test_impl : forward_without_const_t<type, std::false_type, test_impl> {};
     * template<typename type>
     * struct test_impl<impl<type>> : std::true_type {};
     * // 检测类型type是否是一维有界数组
     * // impl<int> -> true
     * // const impl<int> -> true
     * // volatile impl<int> -> false
     * // const volatile impl<int> -> false
     * // void -> false
     * template<typename type>
     * concept test = test_impl<type>::value;
     * @endcode
     *
     */
    template <typename type, typename default_type, template <typename> typename forward_type>
    using forward_without_const_t = ::std::conditional_t<::std::is_const_v<type>, forward_type<::std::remove_const_t<type>>, default_type>;

    /**
     * @brief 移除volatile限定并转发
     *
     * @tparam type 输入类型
     * @tparam default_type 输入类型不带有volatile限定时要返回的类型
     * @tparam forward_type 输入类型带有volatile限定时要转发到的类型
     * @code {.cpp}
     * template<typename type> struct impl{};
     * template<typename type>
     * struct test_impl : forward_without_volatile_t<type, std::false_type, test_impl> {};
     * template<typename type>
     * struct test_impl<impl<type>> : std::true_type {};
     * // 检测类型type是否是一维有界数组
     * // impl<int> -> true
     * // const impl<int> -> false
     * // volatile impl<int> -> true
     * // const volatile impl<int> -> false
     * // void -> false
     * template<typename type>
     * concept test = test_impl<type>::value;
     * @endcode
     *
     */
    template <typename type, typename default_type, template <typename> typename forward_type>
    using forward_without_volatile_t =
        ::std::conditional_t<::std::is_volatile_v<type>, forward_type<::std::remove_volatile_t<type>>, default_type>;

    /**
     * @brief 移除cv限定并转发
     *
     * @tparam type 输入类型
     * @tparam default_type 输入类型不带有cv限定时要返回的类型
     * @tparam forward_type 输入类型带有cv限定时要转发到的类型
     * @code {.cpp}
     * template<typename type> struct impl{};
     * template<typename type>
     * struct test_impl : forward_without_cv_t<type, std::false_type, test_impl> {};
     * template<typename type>
     * struct test_impl<impl<type>> : std::true_type {};
     * // 检测类型type是否是一维有界数组
     * // impl<int> -> true
     * // const impl<int> -> true
     * // volatile impl<int> -> true
     * // const volatile impl<int> -> false
     * // void -> false
     * template<typename type>
     * concept test = test_impl<type>::value;
     * @endcode
     *
     */
    template <typename type, typename default_type, template <typename> typename forward_type>
    using forward_without_cv_t =
        ::std::conditional_t<::std::same_as<type, ::std::remove_cv_t<type>>, default_type, forward_type<::std::remove_cv_t<type>>>;
}  // namespace cppfastbox
