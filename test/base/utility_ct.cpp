#include "../../include/base/utility.h"
using namespace cppfastbox;

#define MEET(type, concept) #type " meets " #concept " constraint"
#define UNMEET(type, concept) #type " does not meet " #concept " constraint"

constexpr void test_integer() noexcept
{
    static_assert(signed_integral<signed char>, UNMEET(signed char, signed_integral));
    static_assert(signed_integral<short>, UNMEET(short, signed_integral));
    static_assert(signed_integral<int>, UNMEET(int, signed_integral));
    static_assert(signed_integral<long>, UNMEET(long, signed_integral));
    static_assert(signed_integral<long long>, UNMEET(long long, signed_integral));
    static_assert(!signed_integral<void>, MEET(void, signed_integral));
    static_assert(!signed_integral<float>, MEET(float, signed_integral));
    static_assert(!signed_integral<double>, MEET(double, signed_integral));
    static_assert(!signed_integral<long double>, MEET(long double, signed_integral));
#ifdef __SIZEOF_INT128__
    static_assert(signed_integral<__int128_t>, UNMEET(__int128_t, signed_integral));
#endif

    static_assert(unsigned_integral<unsigned char>, UNMEET(unsigned char, unsigned_integral));
    static_assert(unsigned_integral<unsigned short>, UNMEET(unsigned short, unsigned_integral));
    static_assert(unsigned_integral<unsigned int>, UNMEET(unsigned int, unsigned_integral));
    static_assert(unsigned_integral<unsigned long>, UNMEET(unsigned long, unsigned_integral));
    static_assert(unsigned_integral<unsigned long long>, UNMEET(unsigned long long, unsigned_integral));
    static_assert(!unsigned_integral<void>, MEET(void, unsigned_integral));
    static_assert(!unsigned_integral<float>, MEET(float, unsigned_integral));
    static_assert(!unsigned_integral<double>, MEET(double, unsigned_integral));
    static_assert(!unsigned_integral<long double>, MEET(long double, unsigned_integral));
#ifdef __SIZEOF_INT128__
    static_assert(unsigned_integral<__uint128_t>, UNMEET(__uint128_t, unsigned_integral));
#endif

    static_assert(integral<char>, UNMEET(char, integral));
    static_assert(integral<signed char>, UNMEET(signed char, integral));
    static_assert(integral<short>, UNMEET(short, integral));
    static_assert(integral<int>, UNMEET(int, integral));
    static_assert(integral<long>, UNMEET(long, integral));
    static_assert(integral<long long>, UNMEET(long long, integral));
    static_assert(integral<unsigned char>, UNMEET(unsigned char, integral));
    static_assert(integral<unsigned short>, UNMEET(unsigned short, integral));
    static_assert(integral<unsigned int>, UNMEET(unsigned int, integral));
    static_assert(integral<unsigned long>, UNMEET(unsigned long, integral));
    static_assert(integral<unsigned long long>, UNMEET(unsigned long long, integral));
    static_assert(!integral<void>, MEET(void, integral));
    static_assert(!integral<float>, MEET(float, integral));
    static_assert(!integral<double>, MEET(double, integral));
    static_assert(!integral<long double>, MEET(long double, integral));
#ifdef __SIZEOF_INT128__
    static_assert(integral<__int128_t>, UNMEET(__int128_t, integral));
    static_assert(integral<__uint128_t>, UNMEET(__uint128_t, integral));
#endif
}

constexpr void test_fixed_size_integer() noexcept
{
    static_assert(fixed_size_signed_integral<std::int8_t>, UNMEET(std::int8_t, fixed_size_signed_integral));
    static_assert(fixed_size_signed_integral<std::int16_t>, UNMEET(std::int16_t, fixed_size_signed_integral));
    static_assert(fixed_size_signed_integral<std::int32_t>, UNMEET(std::int32_t, fixed_size_signed_integral));
    static_assert(fixed_size_signed_integral<std::int64_t>, UNMEET(std::int64_t, fixed_size_signed_integral));
    static_assert(!fixed_size_signed_integral<void>, MEET(void, fixed_size_signed_integral));
    static_assert(!fixed_size_signed_integral<float>, MEET(float, fixed_size_signed_integral));
    static_assert(!fixed_size_signed_integral<double>, MEET(double, fixed_size_signed_integral));
    static_assert(!fixed_size_signed_integral<long double>, MEET(long double, fixed_size_signed_integral));
#ifdef __SIZEOF_INT128__
    static_assert(fixed_size_signed_integral<__int128_t>, UNMEET(__int128_t, fixed_size_signed_integral));
#endif
    {
        using unfixed_size_integer = std::conditional_t<std::same_as<std::int32_t, int>, long, int>;
        static_assert(!fixed_size_signed_integral<unfixed_size_integer> || sizeof(int) != sizeof(long),
                      MEET(unfixed_size_integer, fixed_size_signed_integral));
    }
    {
        using unfixed_size_integer = std::conditional_t<std::same_as<std::int64_t, long>, long long, long>;
        static_assert(!fixed_size_signed_integral<unfixed_size_integer> || sizeof(long) != sizeof(long long),
                      MEET(unfixed_size_integer, fixed_size_signed_integral));
    }

    static_assert(fixed_size_unsigned_integral<std::uint8_t>, UNMEET(std::uint8_t, fixed_size_unsigned_integral));
    static_assert(fixed_size_unsigned_integral<std::uint16_t>, UNMEET(std::uint16_t, fixed_size_unsigned_integral));
    static_assert(fixed_size_unsigned_integral<std::uint32_t>, UNMEET(std::uint32_t, fixed_size_unsigned_integral));
    static_assert(fixed_size_unsigned_integral<std::uint64_t>, UNMEET(std::uint64_t, fixed_size_unsigned_integral));
    static_assert(!fixed_size_unsigned_integral<void>, MEET(void, fixed_size_unsigned_integral));
    static_assert(!fixed_size_unsigned_integral<float>, MEET(float, fixed_size_unsigned_integral));
    static_assert(!fixed_size_unsigned_integral<double>, MEET(double, fixed_size_unsigned_integral));
    static_assert(!fixed_size_unsigned_integral<long double>, MEET(long double, fixed_size_unsigned_integral));
#ifdef __SIZEOF_INT128__
    static_assert(fixed_size_unsigned_integral<__uint128_t>, UNMEET(__uint128_t, fixed_size_unsigned_integral));
#endif
    {
        using unfixed_size_integer = std::conditional_t<std::same_as<std::uint32_t, unsigned int>, unsigned long, unsigned int>;
        static_assert(!fixed_size_unsigned_integral<unfixed_size_integer> || sizeof(unsigned int) != sizeof(unsigned long),
                      MEET(unfixed_size_integer, fixed_size_unsigned_integral));
    }
    {
        using unfixed_size_integer = std::conditional_t<std::same_as<std::uint64_t, unsigned long>, unsigned long long, unsigned long>;
        static_assert(!fixed_size_unsigned_integral<unfixed_size_integer> || sizeof(unsigned long) != sizeof(unsigned long long),
                      MEET(unfixed_size_integer, fixed_size_unsigned_integral));
    }

    static_assert(fixed_size_integral<std::int8_t>, UNMEET(std::int8_t, fixed_size_integral));
    static_assert(fixed_size_integral<std::int16_t>, UNMEET(std::int16_t, fixed_size_integral));
    static_assert(fixed_size_integral<std::int32_t>, UNMEET(std::int32_t, fixed_size_integral));
    static_assert(fixed_size_integral<std::int64_t>, UNMEET(std::int64_t, fixed_size_integral));
    static_assert(fixed_size_integral<std::uint8_t>, UNMEET(std::uint8_t, fixed_size_integral));
    static_assert(fixed_size_integral<std::uint16_t>, UNMEET(std::uint16_t, fixed_size_integral));
    static_assert(fixed_size_integral<std::uint32_t>, UNMEET(std::uint32_t, fixed_size_integral));
    static_assert(fixed_size_integral<std::uint64_t>, UNMEET(std::uint64_t, fixed_size_integral));
    static_assert(!fixed_size_integral<void>, MEET(void, fixed_size_integral));
    static_assert(!fixed_size_integral<float>, MEET(float, fixed_size_integral));
    static_assert(!fixed_size_integral<double>, MEET(double, fixed_size_integral));
    static_assert(!fixed_size_integral<long double>, MEET(long double, fixed_size_integral));
#ifdef __SIZEOF_INT128__
    static_assert(fixed_size_integral<__int128_t>, UNMEET(__int128_t, fixed_size_integral));
    static_assert(fixed_size_integral<__uint128_t>, UNMEET(__uint128_t, fixed_size_integral));
#endif
    {
        using unfixed_size_integer = std::conditional_t<std::same_as<std::int32_t, int>, long, int>;
        static_assert(!fixed_size_integral<unfixed_size_integer> || sizeof(int) != sizeof(long),
                      MEET(unfixed_size_integer, fixed_size_integral));
    }
    {
        using unfixed_size_integer = std::conditional_t<std::same_as<std::int64_t, long>, long long, long>;
        static_assert(!fixed_size_integral<unfixed_size_integer> || sizeof(long) != sizeof(long long),
                      MEET(unfixed_size_integer, fixed_size_integral));
    }
    {
        using unfixed_size_integer = std::conditional_t<std::same_as<std::uint32_t, unsigned int>, unsigned long, unsigned int>;
        static_assert(!fixed_size_integral<unfixed_size_integer> || sizeof(unsigned int) != sizeof(unsigned long),
                      MEET(unfixed_size_integer, fixed_size_integral));
    }
    {
        using unfixed_size_integer = std::conditional_t<std::same_as<std::uint64_t, unsigned long>, unsigned long long, unsigned long>;
        static_assert(!fixed_size_integral<unfixed_size_integer> || sizeof(unsigned long) != sizeof(unsigned long long),
                      MEET(unfixed_size_integer, fixed_size_integral));
    }
}

constexpr void test_character() noexcept
{
    static_assert(character<char>, UNMEET(char, character));
    static_assert(character<wchar_t>, UNMEET(wchar_t, character));
    static_assert(character<char8_t>, UNMEET(char8_t, character));
    static_assert(character<char16_t>, UNMEET(char16_t, character));
    static_assert(character<char32_t>, UNMEET(char32_t, character));

    static_assert(!character<short>, MEET(short, character));
    static_assert(!character<int>, MEET(int, character));
    static_assert(!character<long>, MEET(long, character));
    static_assert(!character<long long>, MEET(long long, character));
    static_assert(!character<unsigned short>, MEET(unsigned short, character));
    static_assert(!character<unsigned int>, MEET(unsigned int, character));
    static_assert(!character<unsigned long>, MEET(unsigned long, character));
    static_assert(!character<unsigned long long>, MEET(unsigned long long, character));
    static_assert(!character<void>, MEET(void, character));
    static_assert(!character<float>, MEET(float, character));
    static_assert(!character<double>, MEET(double, character));
    static_assert(!character<long double>, MEET(long double, character));
#ifdef __SIZEOF_INT128__
    static_assert(!character<__int128_t>, MEET(__int128_t, character));
    static_assert(!character<__uint128_t>, MEET(__uint128_t, character));
#endif
}

constexpr void test_fixed_size_character() noexcept
{
    static_assert(fixed_size_character<char8_t>, UNMEET(char8_t, fixed_size_character));
    static_assert(fixed_size_character<char16_t>, UNMEET(char16_t, fixed_size_character));
    static_assert(fixed_size_character<char32_t>, UNMEET(char32_t, fixed_size_character));

    static_assert(!fixed_size_character<char>, MEET(char, fixed_size_character));
    static_assert(!fixed_size_character<wchar_t>, MEET(wchar_t, fixed_size_character));
    static_assert(!fixed_size_character<short>, MEET(short, fixed_size_character));
    static_assert(!fixed_size_character<int>, MEET(int, fixed_size_character));
    static_assert(!fixed_size_character<long>, MEET(long, fixed_size_character));
    static_assert(!fixed_size_character<long long>, MEET(long long, fixed_size_character));
    static_assert(!fixed_size_character<unsigned short>, MEET(unsigned short, fixed_size_character));
    static_assert(!fixed_size_character<unsigned int>, MEET(unsigned int, fixed_size_character));
    static_assert(!fixed_size_character<unsigned long>, MEET(unsigned long, fixed_size_character));
    static_assert(!fixed_size_character<unsigned long long>, MEET(unsigned long long, fixed_size_character));
    static_assert(!fixed_size_character<void>, MEET(void, fixed_size_character));
    static_assert(!fixed_size_character<float>, MEET(float, fixed_size_character));
    static_assert(!fixed_size_character<double>, MEET(double, fixed_size_character));
    static_assert(!fixed_size_character<long double>, MEET(long double, fixed_size_character));
#ifdef __SIZEOF_INT128__
    static_assert(!fixed_size_character<__int128_t>, MEET(__int128_t, fixed_size_character));
    static_assert(!fixed_size_character<__uint128_t>, MEET(__uint128_t, fixed_size_character));
#endif
}

constexpr void test_simd_integer() noexcept
{
    static_assert(simd_signed_integral<cppfastbox::simd_int8_t>, UNMEET(cppfastbox::simd_int8_t, simd_signed_integral));
    static_assert(simd_signed_integral<cppfastbox::simd_int16_t>, UNMEET(cppfastbox::simd_int16_t, simd_signed_integral));
    static_assert(simd_signed_integral<cppfastbox::simd_int32_t>, UNMEET(cppfastbox::simd_int32_t, simd_signed_integral));
    static_assert(simd_signed_integral<cppfastbox::simd_int64_t>, UNMEET(cppfastbox::simd_int64_t, simd_signed_integral));
    static_assert(!simd_signed_integral<void>, MEET(void, simd_signed_integral));
    static_assert(!simd_signed_integral<float>, MEET(float, simd_signed_integral));
    static_assert(!simd_signed_integral<double>, MEET(double, simd_signed_integral));
    static_assert(!simd_signed_integral<long double>, MEET(long double, simd_signed_integral));
#ifdef __SIZEOF_INT128__
    static_assert(!simd_signed_integral<__int128_t>, MEET(__int128_t, simd_signed_integral));
#endif

    static_assert(simd_unsigned_integral<cppfastbox::simd_uint8_t>, UNMEET(cppfastbox::simd_uint8_t, simd_unsigned_integral));
    static_assert(simd_unsigned_integral<cppfastbox::simd_uint16_t>, UNMEET(cppfastbox::simd_uint16_t, simd_unsigned_integral));
    static_assert(simd_unsigned_integral<cppfastbox::simd_uint32_t>, UNMEET(cppfastbox::simd_uint32_t, simd_unsigned_integral));
    static_assert(simd_unsigned_integral<cppfastbox::simd_uint64_t>, UNMEET(cppfastbox::simd_uint64_t, simd_unsigned_integral));
    static_assert(!simd_unsigned_integral<void>, MEET(void, simd_unsigned_integral));
    static_assert(!simd_unsigned_integral<float>, MEET(float, simd_unsigned_integral));
    static_assert(!simd_unsigned_integral<double>, MEET(double, simd_unsigned_integral));
    static_assert(!simd_unsigned_integral<long double>, MEET(long double, simd_unsigned_integral));
#ifdef __SIZEOF_INT128__
    static_assert(!simd_unsigned_integral<__uint128_t>, MEET(__uint128_t, simd_unsigned_integral));
#endif

    static_assert(simd_integral<cppfastbox::simd_int8_t>, UNMEET(cppfastbox::simd_int8_t, simd_integral));
    static_assert(simd_integral<cppfastbox::simd_int16_t>, UNMEET(cppfastbox::simd_int16_t, simd_integral));
    static_assert(simd_integral<cppfastbox::simd_int32_t>, UNMEET(cppfastbox::simd_int32_t, simd_integral));
    static_assert(simd_integral<cppfastbox::simd_int64_t>, UNMEET(cppfastbox::simd_int64_t, simd_integral));
    static_assert(simd_integral<cppfastbox::simd_uint8_t>, UNMEET(cppfastbox::simd_uint8_t, simd_integral));
    static_assert(simd_integral<cppfastbox::simd_uint16_t>, UNMEET(cppfastbox::simd_uint16_t, simd_integral));
    static_assert(simd_integral<cppfastbox::simd_uint32_t>, UNMEET(cppfastbox::simd_uint32_t, simd_integral));
    static_assert(simd_integral<cppfastbox::simd_uint64_t>, UNMEET(cppfastbox::simd_uint64_t, simd_integral));
    static_assert(!simd_integral<void>, MEET(void, simd_integral));
    static_assert(!simd_integral<float>, MEET(float, simd_integral));
    static_assert(!simd_integral<double>, MEET(double, simd_integral));
    static_assert(!simd_integral<long double>, MEET(long double, simd_integral));
    static_assert(!simd_integral<void>, MEET(void, simd_integral));
    static_assert(!simd_integral<float>, MEET(float, simd_integral));
    static_assert(!simd_integral<double>, MEET(double, simd_integral));
    static_assert(!simd_integral<long double>, MEET(long double, simd_integral));
#ifdef __SIZEOF_INT128__
    static_assert(!simd_integral<__int128_t>, MEET(__int128_t, simd_integral));
    static_assert(!simd_integral<__uint128_t>, MEET(__uint128_t, simd_integral));
#endif
}

int main() { return 0; }
