#pragma once
#include <bit>
#include <cstring>
#include <cwchar>
#include <memory>

/**
 * @brief strlen标量支持
 *
 */
namespace cppfastbox::libc::detail
{
    constexpr auto ad_mask = []() consteval noexcept
    {
        constexpr ::std::uint_least64_t mask64l{0x7efefefe'fefefeffu};
        constexpr ::std::uint_least32_t mask32l{0x7efefeffu};
        constexpr ::std::uint_least64_t mask64b{0xfffefefe'fefefe7eu};
        constexpr ::std::uint_least32_t mask32b{0xfffefe7eu};
        if constexpr(::std::endian::native == ::std::endian::little)
        {
            if constexpr(sizeof(::std::size_t) == 4) { return mask32l; }
            else { return mask64l; }
        }
        else
        {
            if constexpr(sizeof(::std::size_t) == 4) { return mask32b; }
            else { return mask64b; }
        }
    }();
    constexpr auto eos_mask = []() consteval noexcept
    {
        constexpr ::std::uint_least64_t mask64l{0x81010101'01010100u};
        constexpr ::std::uint_least32_t mask32l{0x81010100u};
        constexpr ::std::uint_least64_t mask64b{0x00010101'01010181u};
        constexpr ::std::uint_least32_t mask32b{0x00010181u};
        if constexpr(::std::endian::native == ::std::endian::little)
        {
            if constexpr(sizeof(::std::size_t) == 4) { return mask32l; }
            else { return mask64l; }
        }
        else
        {
            if constexpr(sizeof(::std::size_t) == 4) { return mask32b; }
            else { return mask64b; }
        }
    }();

    [[nodiscard]] inline ::std::size_t strlen_scalar(const char8_t* str) noexcept
    {
        auto* const copy = str;
        auto* eos = reinterpret_cast<const ::std::size_t*>(str);
        while(true)
        {
            auto val{*eos};
            auto ad{val + ::cppfastbox::libc::detail::ad_mask};
            val = ~val;
            val ^= ad;
            if(!(val & ::cppfastbox::libc::detail::eos_mask))
            {
                eos++;
                continue;
            }
            // val中存在\0
            val = *eos;
            auto* ptr = reinterpret_cast<const char8_t*>(eos);

            if constexpr(::std::endian::native == ::std::endian::little)
            {
                if((val & 0x000000ffu) == 0) { return ptr - copy; }
                if((val & 0x0000ff00u) == 0) { return ptr - copy + 1; }
                if((val & 0x00ff0000u) == 0) { return ptr - copy + 2; }
                if((val & 0xff000000u) == 0) { return ptr - copy + 3; }
                if constexpr(sizeof(::std::size_t) == 8)
                {
                    if((val & 0x000000ff'00000000u) == 0) { return ptr - copy + 4; }
                    if((val & 0x0000ff00'00000000u) == 0) { return ptr - copy + 5; }
                    if((val & 0x00ff0000'00000000u) == 0) { return ptr - copy + 6; }
                    if((val & 0xff000000'00000000u) == 0) { return ptr - copy + 7; }
                }
            }
            else
            {
                if constexpr(sizeof(::std::size_t) == 8)
                {
                    if((val & 0xff000000'00000000u) == 0) { return ptr - copy; }
                    if((val & 0x00ff0000'00000000u) == 0) { return ptr - copy + 1; }
                    if((val & 0x0000ff00'00000000u) == 0) { return ptr - copy + 2; }
                    if((val & 0x000000ff'00000000u) == 0) { return ptr - copy + 3; }
                }
                if((val & 0xff000000u) == 0) { return ptr - copy + sizeof(::std::size_t) == 8 ? 4 : 0; }
                if((val & 0x00ff0000u) == 0) { return ptr - copy + sizeof(::std::size_t) == 8 ? 5 : 1; }
                if((val & 0x0000ff00u) == 0) { return ptr - copy + sizeof(::std::size_t) == 8 ? 6 : 2; }
                if((val & 0x000000ffu) == 0) { return ptr - copy + sizeof(::std::size_t) == 8 ? 7 : 3; }
            }
        }
    }

    [[nodiscard]] inline ::std::size_t strlen_scalar(const char16_t* str) noexcept
    {
        auto* const copy = str;
        auto* eos = reinterpret_cast<const ::std::size_t*>(str);
        while(true)
        {
            auto val{*eos};
            auto ad{val + ::cppfastbox::libc::detail::ad_mask};
            val = ~val;
            val ^= ad;
            if(!(val & ::cppfastbox::libc::detail::eos_mask))
            {
                eos++;
                continue;
            }
            // val中存在\0
            val = *eos;
            auto* ptr = reinterpret_cast<const char16_t*>(eos);

            if constexpr(::std::endian::native == ::std::endian::little)
            {
                if((val & 0x0000'ffffu) == 0) { return ptr - copy; }
                if((val & 0xffff'0000u) == 0) { return ptr - copy + 1; }
                if constexpr(sizeof(::std::size_t) == 8)
                {
                    if((val & 0x0000'ffff'0000'0000u) == 0) { return ptr - copy + 2; }
                    if((val & 0xffff'0000'0000'0000u) == 0) { return ptr - copy + 3; }
                }
            }
            else
            {
                if constexpr(sizeof(::std::size_t) == 8)
                {
                    if((val & 0xffff'0000'0000'0000u) == 0) { return ptr - copy; }
                    if((val & 0x0000'ffff'0000'0000u) == 0) { return ptr - copy + 1; }
                }
                if((val & 0xffff'0000u) == 0) { return ptr - copy + sizeof(::std::size_t) == 8 ? 2 : 0; }
                if((val & 0x0000'ffffu) == 0) { return ptr - copy + sizeof(::std::size_t) == 8 ? 3 : 1; }
            }
        }
    }

    [[nodiscard]] inline ::std::size_t strlen_scalar(const char32_t* str) noexcept
    {
        auto* const copy = str;
        if constexpr(sizeof(::std::size_t) == 4)
        {
            while(*str++);
            return str - copy - 1;
        }
        else
        {
            auto* eos = reinterpret_cast<const ::std::size_t*>(str);
            while(true)
            {
                auto val{*eos};
                auto* ptr = reinterpret_cast<const char32_t*>(eos);
                if constexpr(::std::endian::native == ::std::endian::little)
                {
                    if(val << 32 == 0) { return ptr - copy; }
                    if(val >> 32 == 0) { return ptr - copy + 1; }
                }
                else
                {
                    if(val >> 32 == 0) { return ptr - copy; }
                    if(val << 32 == 0) { return ptr - copy + 1; }
                }
                eos++;
            }
        }
    }
}  // namespace cppfastbox::libc::detail

/**
 * @brief x86 strlen向量支持
 *
 */
namespace cppfastbox::libc::detail
{
    constexpr inline auto support_strlen_simd{
#ifdef __SSE2__
        true
#else
        false
#endif
    };

    template <typename char_type>
    [[nodiscard]] inline ::std::size_t strlen_simd(const char_type* str) noexcept
    {
        const auto copy{str};
#if defined(__AVX512F__) && defined(__AVX512BW__)
        while(true)
        {
            using v64i8 [[__gnu__::__vector_size__(64)]] = char;
            v64i8 vc{};
            __builtin_memcpy(&vc, str, 64);
            ::std::uint_least64_t result{};
            if constexpr(sizeof(char_type) == 1)
            {
    #ifndef __clang__
                result = __builtin_ia32_ptestnmb512(vc, vc, -1);  //< avx512bw
    #else
                result = __builtin_ia32_cmpb512_mask(vc & vc, v64i8{}, 0, -1);  //< avx512bw
    #endif
            }
            else if constexpr(sizeof(char_type) == 2)
            {
                using v32i16 [[__gnu__::__vector_size__(64)]] = short;
    #ifndef __clang__
                result = __builtin_ia32_ptestnmw512(::std::bit_cast<v32i16>(vc), ::std::bit_cast<v32i16>(vc), -1);  //< avx512bw
    #else
                result = __builtin_ia32_cmpb512_mask(::std::bit_cast<v32i16>(vc & vc), v32i16{}, 0, -1);  //< avx512bw
    #endif
            }
            else
            {
                using v16i32 [[__gnu__::__vector_size__(64)]] = int;
    #ifndef __clang__
                result = __builtin_ia32_ptestnmd512(::std::bit_cast<v16i32>(vc), ::std::bit_cast<v16i32>(vc), -1);  //< avx512f
    #else
                result = __builtin_ia32_cmpb512_mask(::std::bit_cast<v16i32>(vc & vc), v16i32{}, 0, -1);  //< avx512bw
    #endif
            }
            // 没有结束符
            if(result == 0)
            {
                str += 64 / sizeof(char_type);
                continue;
            }
            // 有结束符
            return str - copy + ::std::countr_zero(result);
        }
#elifdef __SSE2__
        while(true)
        {
    #ifdef __AVX2__
            constexpr auto vector_size{32zu};
    #else
            constexpr auto vector_size{16zu};
    #endif
            using vi [[__gnu__::__vector_size__(vector_size)]] =
                ::std::conditional_t<::std::same_as<char_type, char8_t>, char, ::std::conditional_t<::std::same_as<char_type, char16_t>, short, int>>;
            using vi8 [[__gnu__::__vector_size__(vector_size)]] = char;
            vi vc{};
            __builtin_memcpy(&vc, str, vector_size);  //< sse or avx
            vc = vc == vi{};                          //< sse2 or avx2
    #ifdef __AVX2__
            unsigned int result{static_cast<unsigned int>(__builtin_ia32_pmovmskb256(::std::bit_cast<vi8>(vc)))};  //< avx2
    #else
            unsigned int result{static_cast<unsigned int>(__builtin_ia32_pmovmskb128(::std::bit_cast<vi8>(vc)))};  //< sse2
    #endif
            if(result == 0)
            {
                str += vector_size / sizeof(char_type);
                continue;
            }
            return str - copy + ::std::countr_zero(result) / sizeof(char_type);
        }
#endif
    }
}  // namespace cppfastbox::libc::detail

namespace cppfastbox::libc
{
    template <typename char_type>
    constexpr inline ::std::size_t strlen(const char_type* str) noexcept
    {
        if consteval
        {
            const auto copy{str};
            while(*str++);
            return str - copy;
        }
        else
        {
            using pointer =
                ::std::conditional_t<sizeof(char_type) == 1, const char8_t*, ::std::conditional_t<sizeof(char_type) == 2, const char16_t*, const char32_t*>>;
            auto* ptr{reinterpret_cast<pointer>(str)};
            if constexpr(::cppfastbox::libc::detail::support_strlen_simd) { return ::cppfastbox::libc::detail::strlen_simd(ptr); }
            else { return ::cppfastbox::libc::detail::strlen_scalar(ptr); }
        }
    }
}  // namespace cppfastbox::libc
