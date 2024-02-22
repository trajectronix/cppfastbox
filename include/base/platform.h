/**
 * @file platform.h
 * @brief 平台相关定义
 *
 * @copyright Copyright (c) 2024-present Trajectronix Open Source Group
 *
 */
#pragma once
#ifndef __cplusplus
    #error We must use cppfastbox with c++ compiler
#endif
#if __cplusplus < 202300
    #error The c++ compiler does not support c++23 standard
#endif
#include <cstddef>
#include <utility>
#include <bit>
#include "min_max.h"

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
    #error Unknown Operating System
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
#else
    #error Unknown c++ compiler
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
// 恒内联函数
#define CPPFASTBOX_ALWAYS_INLINE [[using gnu: always_inline, artificial]]

namespace cppfastbox
{
    // 受支持的操作系统
    enum class os : ::std::size_t
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
    //  支持的操作系统数量
    constexpr inline auto os_num{::std::to_underlying(::cppfastbox::os::os_num)};
    // 操作系统名称
    constexpr const inline char* os_name[]{"freestanding",
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
    //  保证表os_name的元素数正确
    static_assert(sizeof(::cppfastbox::os_name) / sizeof(char*) % ::cppfastbox::os_num == 0);
    // 表os_name的页数
    constexpr inline auto os_leaf_num{sizeof(::cppfastbox::os_name) / sizeof(char*) / ::cppfastbox::os_num};
    /**
     * @brief 判断当前系统是否是给定操作系统
     *
     * @tparam os 操作系统枚举
     */
    template <::cppfastbox::os os>
    constexpr inline auto is_os{::cppfastbox::os::native == os};
    /**
     * @brief 获取当前系统名称
     *
     * @tparam leaf 页数
     * @tparam os 操作系统枚举
     */
    template <::std::size_t leaf, ::cppfastbox::os os = ::cppfastbox::os::native>
    constexpr inline auto get_os_name{::cppfastbox::os_name[leaf * ::cppfastbox::os_num + ::std::to_underlying(os)]};

    // 受支持的cpu架构
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
    //  支持的cpu架构数
    constexpr inline auto cpu_arch_num{::std::to_underlying(::cppfastbox::cpu_arch::arch_num)};
    // cpu架构名称
    constexpr const inline char* cpu_arch_name[]{"x86",       "x64",         "arm",         "arm64",         "la",     "la64",
                                                 "wasm",      "wasm64",      "X86",         "X86_64",        "ARM",    "AArch64",
                                                 "LoongArch", "LoongArch64", "WebAssembly", "WebAssembly64", "i386",   "x86-64",
                                                 "aarch32",   "aarch64",     "loongarch",   "loongarch64",   "wasm32", "wasm64"};

    //  保证表cpu_arch_name的元素数正确
    static_assert(sizeof(::cppfastbox::cpu_arch_name) / sizeof(char*) % ::cppfastbox::cpu_arch_num == 0);
    // 表cpu_arch_name的页数
    constexpr inline auto cpu_arch_leaf_num{sizeof(::cppfastbox::cpu_arch_name) / sizeof(char*) / ::cppfastbox::cpu_arch_num};
    /**
     * @brief 判断当前cpu是否是给定cpu
     *
     * @tparam arch cpu架构枚举
     */
    template <::cppfastbox::cpu_arch arch>
    constexpr inline auto is_cpu_arch{::cppfastbox::cpu_arch::native == arch};
    /**
     * @brief 获取cpu名称
     *
     * @tparam leaf 页数
     * @tparam arch cpu架构枚举
     */
    template <::std::size_t leaf, ::cppfastbox::cpu_arch arch = ::cppfastbox::cpu_arch::native>
    constexpr inline auto get_cpu_arch_name{::cppfastbox::cpu_arch_name[leaf * ::cppfastbox::cpu_arch_num + ::std::to_underlying(arch)]};

    // 受支持的编译器
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
    //  支持的编译器数
    constexpr inline auto compiler_num{::std::to_underlying(::cppfastbox::compiler::compiler_num)};
    // 编译器名称
    constexpr const inline char* compiler_name[]{"clang", "gcc", "Clang", "GCC", "clang++", "g++", "llvm", "gcc"};
    //  保证表compiler_name的元素数正确
    static_assert(sizeof(::cppfastbox::compiler_name) / sizeof(char*) % ::cppfastbox::compiler_num == 0);
    // 表compiler_name的页数
    constexpr inline auto compiler_leaf_num{sizeof(::cppfastbox::compiler_name) / sizeof(char*) / ::cppfastbox::compiler_num};
    /**
     * @brief 判断当前编译器是否是给定编译器
     *
     * @tparam compiler 编译器枚举
     */
    template <::cppfastbox::compiler compiler>
    constexpr inline auto is_compiler{::cppfastbox::compiler::native == compiler};
    /**
     * @brief 获取编译器名称
     *
     * @tparam leaf 页数
     * @tparam compiler 编译器枚举
     */
    template <::std::size_t leaf, ::cppfastbox::compiler compiler = ::cppfastbox::compiler::native>
    constexpr inline auto get_compiler_name{::cppfastbox::compiler_name[leaf * ::cppfastbox::compiler_num + ::std::to_underlying(compiler)]};

    // 受支持的cpu指令集
    enum class cpu_flag : ::std::size_t
    {
        sse,
        sse2,
        sse3,
        ssse3,
        sse4_1,
        sse4_2,
        avx,
        avx2,
        avx512f,
        avx512bw,
        avx512vl,
        avx512dq,
        avx512vbmi,
        wasm128,
        neon,
        sve,
        sve2,
        lsx,
        lasx,
        cpu_flag_num  //< 支持的cpu指令集数量
    };
    //  支持的cpu指令集数量
    constexpr inline auto cpu_flag_num{::std::to_underlying(::cppfastbox::cpu_flag::cpu_flag_num)};
    // cpu指令集名称
    constexpr const inline char* cpu_flag_name[]{
        "sse",      "sse2",       "sse3",         "ssse3",   "sse4_1", "sse4_2", "avx",  "avx2",    "avx512f",  "avx512bw",
        "avx512vl", "avx512dq",   "avx512vbmi",   "wasm128", "neon",   "sve",    "sve2", "lsx",     "lasx",     "SSE",
        "SSE2",     "SSE3",       "SSSE3",        "SSE4.1",  "SSE4.2", "AVX",    "AVX2", "AVX512F", "AVX512BW", "AVX512VL",
        "AVX512DQ", "AVX512VBMI", "Wasm Simd128", "Neon",    "SVE",    "SVE2",   "LSX",  "LASX"};
    // 表cpu_flag_name的页数
    constexpr inline auto cpu_flag_leaf_num{sizeof(::cppfastbox::cpu_flag_name) / sizeof(char*) / ::cppfastbox::cpu_flag_num};
    /**
     * @brief 获取cpu指令集名称
     *
     * @tparam leaf 页数
     * @tparam flag cpu指令集枚举
     */
    template <::std::size_t leaf, ::cppfastbox::cpu_flag flag>
    constexpr inline auto get_cpu_flag_name{::cppfastbox::cpu_flag_name[leaf * ::cppfastbox::cpu_flag_num + ::std::to_underlying(flag)]};
}  // namespace cppfastbox

namespace cppfastbox
{
    // 是否是32位cpu
    constexpr inline auto is_32bit{sizeof(::std::size_t) == 4};
    // 是否是64位cpu
    constexpr inline auto is_64bit{sizeof(::std::size_t) == 8};
    // 仅支持32位或64位cpu
    static_assert(::cppfastbox::is_32bit || ::cppfastbox::is_64bit, "Cppfastbox only support 32-bit or 64-bit cpu.");
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
    constexpr inline auto int128_support{!::std::is_void_v<::cppfastbox::native_int128_t>};
    // 判断给定类型是否是原生的int128类型
    template <typename type>
    concept is_native_int128 = ::cppfastbox::int128_support && ::std::same_as<type, ::cppfastbox::native_int128_t>;
    // 判断给定类型是否是原生的uint128类型
    template <typename type>
    concept is_native_uint128 = ::cppfastbox::int128_support && ::std::same_as<type, ::cppfastbox::native_uint128_t>;

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
    constexpr inline auto float128_support{!::std::is_void_v<::cppfastbox::native_float128_t>};
    // 判断给定类型是否是原生的float128类型
    template <typename type>
    concept is_native_float128 = ::cppfastbox::float128_support && ::std::same_as<type, ::cppfastbox::native_float128_t>;
}  // namespace cppfastbox

namespace cppfastbox
{
    /**
     * @brief 判断是否以debug模式编译
     *
     * @note 这可能会启用一些利于调试的代码
     */
    constexpr inline bool is_debug{
#if defined(DEBUG) || defined(_DEBUG)
        true
#endif
    };
    /**
     * @brief 判断是否以release模式编译
     *
     * @note 这会禁用断言等功能
     */
    constexpr inline bool is_release{
#ifdef NDEBUG
        true
#endif
    };
}  // namespace cppfastbox

// 编译时已知的cpu flag
namespace cppfastbox::cpu_flags
{
    // 是否支持sse指令集
    constexpr inline bool sse_support{
#ifdef __SSE__
        true
#endif
    };

    // 是否支持sse2指令集
    constexpr inline bool sse2_support{
#ifdef __SSE2__
        true
#endif
    };

    // 是否支持sse3指令集
    constexpr inline bool sse3_support{
#ifdef __SSE3__
        true
#endif
    };

    // 是否支持ssse3指令集
    constexpr inline bool ssse3_support{
#ifdef __SSSE3__
        true
#endif
    };

    // 是否支持sse4.1指令集
    constexpr inline bool sse4_1_support{
#ifdef __SSE4_1__
        true
#endif
    };

    // 是否支持sse4.2指令集
    constexpr inline bool sse4_2_support{
#ifdef __SSE4_2__
        true
#endif
    };

    // 是否支持avx指令集
    constexpr inline bool avx_support{
#ifdef __AVX__
        true
#endif
    };

    // 是否支持avx2指令集
    constexpr inline bool avx2_support{
#ifdef __AVX2__
        true
#endif
    };

    // 是否支持avx512f指令集
    constexpr inline bool avx512f_support{
#if defined(__AVX512F__)
        true
#endif
    };

    // 是否支持avx512bw指令集
    constexpr inline bool avx512bw_support{
#if defined(__AVX512BW__)
        true
#endif
    };

    // 是否支持avx512vl指令集
    constexpr inline bool avx512vl_support{
#if defined(__AVX512VL__)
        true
#endif
    };

    // 是否支持avx512dq指令集
    constexpr inline bool avx512dq_support{
#if defined(__AVX512DQ__)
        true
#endif
    };

    // 是否支持avx512vbmi指令集
    constexpr inline bool avx512vbmi_support{
#if defined(__AVX512VBMI__)
        true
#endif
    };

    // 是否支持wasm simd128指令集
    constexpr inline bool wasm128_support{
#if defined(__wasm_simd128__)
        true
#endif
    };

    // 是否支持arm neon指令集
    constexpr inline bool neon_support{
#ifdef __ARM_NEON
        true
#endif
    };

    // 是否支持arm sve指令集
    constexpr inline bool sve_support{
#ifdef __ARM_FEATURE_SVE
        true
#endif
    };

    // 是否支持arm sve2指令集
    constexpr inline bool sve2_support{
#ifdef __ARM_FEATURE_SVE2
        true
#endif
    };

    // 是否支持loongarch sx指令集
    constexpr inline bool lsx_support{
#ifdef __loongarch_sx
        true
#endif
    };

    // 是否支持loongarch asx指令集
    constexpr inline bool lasx_support{
#ifdef __loongarch_asx
        true
#endif
    };
}  // namespace cppfastbox::cpu_flags

namespace cppfastbox::cpu_flags::arm
{
    // 是否支持arm neon指令集
    constexpr inline bool neon_support{
#ifdef __ARM_NEON
        true
#endif
    };

    // 是否支持arm sve指令集
    constexpr inline bool sve_support{
#ifdef __ARM_FEATURE_SVE
        true
#endif
    };

    // 是否支持arm sve2指令集
    constexpr inline bool sve2_support{
#ifdef __ARM_FEATURE_SVE2
        true
#endif
    };

    // arm架构
    enum class arch : ::std::size_t
    {
        inapplicability,  //< 非arm架构，不适用
        armv1,
        armv2,
        armv3,
        armv4,
        armv5,
        armv6,
        armv7,
        armv8,
        armv9,
        arch_num,  //< 支持的arm架构数+1
#ifdef __ARM_ARCH
        native = __ARM_ARCH
#else
        native = inapplicability
#endif
    };
    // arm架构数
    constexpr inline auto arch_num{::std::to_underlying(::cppfastbox::cpu_flags::arm::arch::arch_num) - 1};
    // arm架构名称
    constexpr const inline char* arch_name[]{
        "armv1",
        "armv2",
        "armv3",
        "armv4",
        "armv5",
        "armv6",
        "armv7",
        "armv8",
        "armv9",
        "ARMv1",
        "ARMv2",
        "ARMv3",
        "ARMv4",
        "ARMv5",
        "ARMv6",
        "ARMv7",
        "ARMv8",
        "ARMv9",
    };
    //  保证表arch_name的元素数正确
    static_assert(sizeof(::cppfastbox::cpu_flags::arm::arch_name) / sizeof(char*) % ::cppfastbox::cpu_flags::arm::arch_num == 0);
    // 表arch_name的页数
    constexpr inline auto arch_leaf_num{sizeof(::cppfastbox::cpu_flags::arm::arch_name) / sizeof(char*) /
                                        ::cppfastbox::cpu_flags::arm::arch_num};
    /**
     * @brief 获取arm架构名称
     *
     * @tparam leaf 页数
     * @tparam flag arm架构枚举
     */
    template <::std::size_t leaf, ::cppfastbox::cpu_flags::arm::arch arch = ::cppfastbox::cpu_flags::arm::arch::native>
        requires (arch != ::cppfastbox::cpu_flags::arm::arch::inapplicability)
    constexpr inline auto get_arch_name{
        ::cppfastbox::cpu_flags::arm::arch_name[leaf * ::cppfastbox::cpu_flags::arm::arch_num + ::std::to_underlying(arch)]};

    // arm配置
    enum class profile : ::std::size_t
    {
        inapplicability,  //< 非arm架构，不适用
        none,             //< 无特殊配置
        a,                //< a系列
        r,                //< r系列
        m,                //< m系列
        profile_num,      //< 支持的arm配置数+1
#ifdef __ARM_ARCH_PROFILE
    #if __ARM_ARCH_PROFILE == 'A'
        native = a
    #elif __ARM_ARCH_PROFILE == 'R'
        native = r
    #else
        native = m
    #endif
#else
    #if defined(CPPFASTBOX_ARM) || defined(CPPFASTBOX_ARM64)
        native = none
    #else
        native = inapplicability
    #endif
#endif
    };
    // arm配置数
    constexpr inline auto profile_num{::std::to_underlying(::cppfastbox::cpu_flags::arm::profile::profile_num) - 1};
    // arm配置名称
    constexpr const inline char* profile_name[]{"none", "a", "r", "m", "none", "A", "R", "M"};
    //  保证表profile_name的元素数正确
    static_assert(sizeof(::cppfastbox::cpu_flags::arm::profile_name) / sizeof(char*) % ::cppfastbox::cpu_flags::arm::profile_num == 0);
    // 表profile_name的页数
    constexpr inline auto profile_leaf_num{sizeof(::cppfastbox::cpu_flags::arm::profile_name) / sizeof(char*) /
                                           ::cppfastbox::cpu_flags::arm::profile_num};
    /**
     * @brief 获取arm配置名称
     *
     * @tparam leaf 页数
     * @tparam flag arm配置枚举
     */
    template <::std::size_t leaf, ::cppfastbox::cpu_flags::arm::profile profile = ::cppfastbox::cpu_flags::arm::profile::native>
        requires (profile != ::cppfastbox::cpu_flags::arm::profile::inapplicability)
    constexpr inline auto get_profile_name{
        ::cppfastbox::cpu_flags::arm::profile_name[leaf * ::cppfastbox::cpu_flags::arm::profile_num + ::std::to_underlying(profile)]};

    // 是否支持标量的非对齐读写
    constexpr inline bool unaligned_ls_support{::std::to_underlying(::cppfastbox::cpu_flags::arm::arch::native) >=
                                               ::std::to_underlying(::cppfastbox::cpu_flags::arm::arch::armv6)};
    // 是否支持向量的非对齐读写
    constexpr inline bool unaligned_simd_ls_support{
#ifdef __ARM_NEON
        true
#endif
    };
};  // namespace cppfastbox::cpu_flags::arm

namespace cppfastbox
{
    namespace detail
    {
        consteval inline ::std::size_t native_vector_max_size() noexcept
        {
            if constexpr(::cppfastbox::cpu_flags::avx512f_support) { return 64; }
            else if constexpr(::cppfastbox::cpu_flags::avx_support) { return 32; }
            else if constexpr(::cppfastbox::cpu_flags::sse_support) { return 16; }
            else if constexpr(::cppfastbox::cpu_flags::arm::sve_support) { return 256; }
            else if constexpr(::cppfastbox::cpu_flags::arm::neon_support) { return 16; }
            else if constexpr(::cppfastbox::cpu_flags::lasx_support) { return 32; }
            else if constexpr(::cppfastbox::cpu_flags::lsx_support) { return 16; }
            else if constexpr(::cppfastbox::cpu_flags::wasm128_support) { return 16; }
            else { return 0; }
        }

        consteval inline ::std::size_t native_vector_ls_max_size() noexcept
        {
            if constexpr(::cppfastbox::cpu_flags::avx512f_support) { return 64; }
            else if constexpr(::cppfastbox::cpu_flags::avx_support) { return 32; }
            else if constexpr(::cppfastbox::cpu_flags::sse_support) { return 16; }
            else if constexpr(::cppfastbox::cpu_flags::sve_support) { return 32; }   //< 编译器只生成ldp和stp
            else if constexpr(::cppfastbox::cpu_flags::neon_support) { return 32; }  //< ldp和stp可以同时处理两个128位向量
            else if constexpr(::cppfastbox::cpu_flags::lasx_support) { return 32; }
            else if constexpr(::cppfastbox::cpu_flags::lsx_support) { return 16; }
            else if constexpr(::cppfastbox::cpu_flags::wasm128_support) { return 16; }
            else { return 0; }
        }
    }  // namespace detail

    // 硬件支持的最大向量大小，若硬件不支持向量化则为0
    constexpr inline auto native_vector_max_size{::cppfastbox::detail::native_vector_max_size()};
    // 单指令可以读写的最大向量大小，若硬件不支持向量化则为0
    constexpr inline auto native_vector_ls_max_size{::cppfastbox::detail::native_vector_ls_max_size()};
    // 是否支持向量化
    constexpr inline auto simd_support{::cppfastbox::native_vector_max_size != 0};
    // 32位程序不应使用64位cpu专有的向量指令集
    static_assert(::cppfastbox::is_64bit || (::cppfastbox::is_32bit && ::cppfastbox::native_vector_max_size <= 16),
                  "32-bit programs should not use the vector instruction set specific to 64-bit cpus.");
    // 硬件支持的最大通道大小
    constexpr inline auto native_lane_max_size{::cppfastbox::max(::cppfastbox::native_vector_max_size, sizeof(::std::size_t))};
    // 硬件支持的最大读写通道大小
    constexpr inline auto native_ls_lane_max_size{::cppfastbox::max(::cppfastbox::native_vector_ls_max_size, sizeof(::std::size_t))};
    // cppfastbox支持的最大通道大小
    constexpr inline auto lane_max_size_support{64zu};
    // cppfastbox支持的最大读写通道大小
    constexpr inline auto ls_lane_max_size_support{64zu};
}  // namespace cppfastbox
