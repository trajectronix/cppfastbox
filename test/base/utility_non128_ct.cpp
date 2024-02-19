/**
 * @file utility_ct_non128.cpp
 * @brief 无128扩展的utility.h编译时测试
 *
 * @copyright Copyright (c) 2024-present Trajectronix Open Source Group
 *
 */
#undef __SIZEOF_INT128__
#undef __SIZEOF_FLOAT128__
#include "../../include/base/utility.h"

using namespace cppfastbox;
using namespace std;

#define MEET(type, concept) #type " meets " #concept " constraint"
#define UNMEET(type, concept) #type " does not meet " #concept " constraint"

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
#define ASSERT_SAME(is_signed, size, type)                                                                                                      \
    static_assert(std::same_as<fixed_size_integer_t<is_signed, size>, type>,                                                                    \
                  "fixed_size_integer_t<" #is_signed ", " #size "> is different from " #type)

constexpr void test_fixed_size_integer_t() noexcept
{
    ASSERT_SAME(true, 1, std::int8_t);
    ASSERT_SAME(true, 2, std::int16_t);
    ASSERT_SAME(true, 4, std::int32_t);
    ASSERT_SAME(true, 8, std::int64_t);

    ASSERT_SAME(false, 1, std::uint8_t);
    ASSERT_SAME(false, 2, std::uint16_t);
    ASSERT_SAME(false, 4, std::uint32_t);
    ASSERT_SAME(false, 8, std::uint64_t);
}