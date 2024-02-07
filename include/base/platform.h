/**
 * @file platform.h
 * @brief 平台相关定义
 *
 * @copyright Copyright 2024-present Trajectronix Open Source Group
 *
 */
#pragma once
#include <cstddef>
#include <utility>
#include <bit>

#if __STDC_HOSTED__ == 0
    #define CPPFASTBOX_FREESTANDING
#elif defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64) || defined(__WIN32__) || defined(__WINDOWS__)
    #define CPPFASTBOX_WINDOWS
#elif defined(__linux__) || defined(__linux) || defined(linux) || defined(__gnu_linux__)
    #define CPPFASTBOX_LINUX
#elifdef TARGET_OS_IPHONE
    #define CPPFASTBOX_IOS
#elifdef TARGET_OS_MAC
    #define CPPFASTBOX_MACOS
#elifdef __ANDROID__
    #define CPPFASTBOX_ANDROID
#elif defined(__wasm__) || defined(__wasm) || defined(__wasm64__) || defined(__wasm64)
    #define CPPFASTBOX_WASM
#else
    #error Unknown system
#endif

#ifdef __i386__
    #define CPPFASTBOX_X86
#elifdef __x86_64__
    #define CPPFASTBOX_X64
#elifdef __arm__
    #define CPPFASTBOX_ARM
#elifdef __aarch64__
    #define CPPFASTBOX_ARM64
#elifdef __loongarch__
    #define CPPFASTBOX_LA
#elifdef __loongarch64
    #define CPPFASTBOX_LA64
#elif defined(__wasm32__) || defined(__wasm32)
    #define CPPFASTBOX_WASM
#elif defined(__wasm64__) || defined(__wasm64)
    #define CPPFASTBOX_WASM64
#else
    #error Unknown arch
#endif

#ifdef __clang__
    #define CPPFASTBOX_CLANG
#elifdef __GNUC__
    #define CPPFASTBOX_GCC
#endif

// Windows下的调用协议
#ifdef CPPFASTBOX_WINDOWS
    #define CPPFASTBOX_CDECL __cdecl
    #define CPPFASTBOX_STDCALL __stdcall
#else
    #define CPPFASTBOX_CDECL
    #define CPPFASTBOX_STDCALL
#endif

// 无操作
#define CPPFASTBOX_NOP void(nullptr)

namespace cppfastbox
{
    // 当前平台的操作系统
    enum class operating_system : ::std::size_t
    {
        freestanding,
        windows,
        linux,
        ios,
        macos,
        android,
        wasm,
        os_num,  //< 支持的操作系统数量
#ifdef CPPFASTBOX_FREESTANDING
        native = freestanding
#elifdef CPPFASTBOX_WINDOWS
        native = windows
#elifdef CPPFASTBOX_LINUX
        native = linux
#elifdef CPPFASTBOX_IOS
        native = iso
#elifdef CPPFASTBOX_MACOS
        native = macos
#elifdef CPPFASTBOX_ANDROID
        native = android
#elifdef CPPFASTBOX_WASM
        native = wasm
#endif
    };
    // 操作系统名称
    constexpr const inline char* operating_system_name[]{"freestanding",
                                                         "windows",
                                                         "linux",
                                                         "ios",
                                                         "macos",
                                                         "android",
                                                         "wasm",
                                                         "Freestanding",
                                                         "Windows",
                                                         "Linux",
                                                         "iOS",
                                                         "MacOS",
                                                         "Android",
                                                         "WebAssembly"};
    /**
     * @brief 判断当前系统是否是给定系统
     *
     * @tparam os 系统枚举
     */
    template <::cppfastbox::operating_system os>
    constexpr inline auto is_os{::cppfastbox::operating_system::native == os};
    /**
     * @brief 获取当前系统名称
     *
     * @tparam leaf 页数
     */
    template <::std::size_t leaf>
    constexpr inline auto get_native_os_name{::cppfastbox::operating_system_name[leaf * ::std::to_underlying(::cppfastbox::operating_system::os_num) +
                                                                               ::std::to_underlying(::cppfastbox::operating_system::native)]};

    // 当前cpu架构
    enum class cpu_arch : ::std::size_t
    {
        x86,
        x64,
        arm,
        arm64,
        la,
        la64,
        wasm,
        wasm64,
        arch_num,  //< 支持的cpu架构数
#ifdef CPPFASTBOX_X86
        native = x86
#elifdef CPPFASTBOX_X64
        native = x64
#elifdef CPPFASTBOX_ARM
        native = arm
#elifdef CPPFASTBOX_ARM64
        native = arm64
#elifdef CPPFASTBOX_LA
        native = la
#elifdef CPPFASTBOX_LA64
        native = la64
#elifdef CPPFASTBOX_WASM
        native = wasm
#elifdef CPPFASTBOX_WASM64
        native = wasm64
#endif
    };
    // cpu架构名称
    constexpr const inline char* cpu_arch_name[]{"x86",       "x64",         "arm",         "arm64",         "la",     "la64",
                                                 "wasm",      "wasm64",      "X86",         "X86_64",        "ARM",    "AArch64",
                                                 "LoongArch", "LoongArch64", "WebAssembly", "WebAssembly64", "i386",   "x86-64",
                                                 "aarch32",   "aarch64",     "loongarch",   "loongarch64",   "wasm32", "wasm64"};
    /**
     * @brief 判断当前cpu是否是给定cpu
     *
     * @tparam arch cpu枚举
     */
    template <::cppfastbox::cpu_arch arch>
    constexpr inline auto is_arch{::cppfastbox::cpu_arch::native == arch};
    /**
     * @brief 获取当前cpu名称
     *
     * @tparam leaf 页数
     */
    template <::std::size_t leaf>
    constexpr inline auto get_native_arch_name{
        cpu_arch_name[leaf * ::std::to_underlying(::cppfastbox::cpu_arch::arch_num) + ::std::to_underlying(::cppfastbox::cpu_arch::native)]};

    // 当前编译器
    enum class compiler : ::std::size_t
    {
        clang,
        gcc,
        compiler_num,  //< 支持的编译器数
#ifdef CPPFASTBOX_CLANG
        native = clang
#else
        native = gcc
#endif
    };
    // 编译器名称
    constexpr const inline char* compiler_name[]{"clang", "gcc", "Clang", "GCC", "clang++", "g++", "llvm", "gcc"};
    /**
     * @brief 判断当前编译器是否是给定编译器
     *
     * @tparam compiler 编译器枚举
     */
    template <::cppfastbox::compiler compiler>
    constexpr inline auto is_compiler{::cppfastbox::compiler::native == compiler};
    /**
     * @brief 获取当前编译器名称
     *
     * @tparam leaf 页数
     */
    template <::std::size_t leaf>
    constexpr inline auto get_native_compiler_name{
        compiler_name[leaf * ::std::to_underlying(::cppfastbox::compiler::compiler_num) + ::std::to_underlying(::cppfastbox::compiler::native)]};
}  // namespace cppfastbox

namespace cppfastbox
{
    // 是否是32位cpu
    constexpr inline auto is_32bit{sizeof(::std::size_t) == 4};
    // 是否是64位cpu
    constexpr inline auto is_64bit{sizeof(::std::size_t) == 8};
    // 是否是小端
    constexpr inline auto is_little_endian{::std::endian::native == ::std::endian::little};
    // 是否是大端
    constexpr inline auto is_big_endian{::std::endian::native == ::std::endian::big};

#ifdef __SIZEOF_INT128__
    /**
     * @brief 原生的int128类型
     *
     * @note 若不支持__int128扩展则为void
     */
    using native_int128_t = __int128_t;
    /**
     * @brief 原生的uint128类型
     *
     * @note 若不支持__int128扩展则为void
     */
    using native_uint128_t = __uint128_t;
#else
    /**
     * @brief 原生的int128类型
     *
     * @note 若不支持__int128扩展则为void
     */
    using native_int128_t = void;
    /**
     * @brief 原生的uint128类型
     *
     * @note 若不支持__int128扩展则为void
     */
    using native_uint128_t = void;
#endif
    // 是否支持__int128扩展
    constexpr inline auto support_int128{!::std::is_void_v<native_int128_t>};
    // 判断给定类型是否是原生的int128类型
    template <typename type>
    concept is_native_int128 = ::cppfastbox::support_int128 && ::std::same_as<type, native_int128_t>;
    // 判断给定类型是否是原生的uint128类型
    template <typename type>
    concept is_native_uint128 = ::cppfastbox::support_int128 && ::std::same_as<type, native_uint128_t>;

#ifdef __SIZEOF_FLOAT128__
    /**
     * @brief 原生的float128类型
     *
     * @note 若不支持__float128扩展则为void
     */
    using native_float128_t = __float128;
#else
    /**
     * @brief 原生的float128类型
     *
     * @note 若不支持__float128扩展则为void
     */
    using native_float128_t = void;
#endif
    // 是否支持__float128扩展
    constexpr inline auto support_float128{!::std::is_void_v<native_float128_t>};
    // 判断给定类型是否是原生的float128类型
    template <typename type>
    concept is_native_float128 = ::cppfastbox::support_float128 && ::std::same_as<type, native_float128_t>;
}  // namespace cppfastbox

namespace cppfastbox
{
#if defined(DEBUG) || defined(_DEBUG)
    /**
     * @brief 判断是否以debug模式编译
     *
     * @note 这可能会启用一些利于调试的代码
     */
    constexpr inline auto is_debug{true};
#else
    /**
     * @brief 判断是否以debug模式编译
     *
     * @note 这可能会启用一些利于调试的代码
     */
    constexpr inline auto is_debug{false};
#endif
#ifdef NDEBUG
    /**
     * @brief 判断是否以release模式编译
     *
     * @note 这会禁用断言等功能
     */
    constexpr inline auto is_release{true};
#else
    /**
     * @brief 判断是否以release模式编译
     *
     * @note 这会禁用断言等功能
     */
    constexpr inline auto is_release{false};
#endif
}  // namespace cppfastbox
