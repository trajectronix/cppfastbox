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

#define ASSERT_SAME(is_signed, size, type)                                                                                                      \
    static_assert(std::same_as<fixed_size_integer_t<is_signed, size>, type>,                                                                    \
                  "fixed_size_integer_t<" #is_signed ", " #size "> is different from " #type)

constexpr void test_fixed_size_integer_t() noexcept
{
    ASSERT_SAME(true, 1, std::int8_t);
    ASSERT_SAME(true, 2, std::int16_t);
    ASSERT_SAME(true, 4, std::int32_t);
    ASSERT_SAME(true, 8, std::int64_t);
#ifdef __SIZEOF_INT128__
    ASSERT_SAME(true, 16, native_int128_t);
#endif

    ASSERT_SAME(false, 1, std::uint8_t);
    ASSERT_SAME(false, 2, std::uint16_t);
    ASSERT_SAME(false, 4, std::uint32_t);
    ASSERT_SAME(false, 8, std::uint64_t);
#ifdef __SIZEOF_INT128__
    ASSERT_SAME(false, 16, native_uint128_t);
#endif
}

#undef ASSERT_SAME
#define ASSERT_SAME(size, type)                                                                                                                 \
    static_assert(std::same_as<fixed_size_character_t<size>, type>, "fixed_size_character_t<" #size "> is different from " #type)

constexpr void test_fixed_size_character_t() noexcept
{
    ASSERT_SAME(1, char8_t);
    ASSERT_SAME(2, char16_t);
    ASSERT_SAME(4, char32_t);
}

#undef ASSERT_SAME
#define ASSERT_SAME(type)                                                                                                                       \
    static_assert(std::same_as<to_fixed_size_integer_t<type>, fixed_size_integer_t<signed_integral<type>, sizeof(type)>>,                       \
                  "to_fixed_size_integer_t<" #type "> is different from fixed_size_integer_t<signed_integral<" #type ">, sizeof(" #type ")>")

constexpr void test_to_fixed_integer_size_t() noexcept
{
    ASSERT_SAME(bool);
    ASSERT_SAME(char);
    ASSERT_SAME(signed char);
    ASSERT_SAME(unsigned char);
    ASSERT_SAME(int);
    ASSERT_SAME(unsigned int);
    ASSERT_SAME(long);
    ASSERT_SAME(unsigned long);
    ASSERT_SAME(long long);
    ASSERT_SAME(unsigned long long);
#ifdef __SIZEOF_INT128__
    ASSERT_SAME(native_int128_t);
    ASSERT_SAME(native_uint128_t);
#endif
}

#undef ASSERT_SAME
#define ASSERT_SAME(type)                                                                                                                       \
    static_assert(std::same_as<to_fixed_size_character_t<type>, fixed_size_character_t<sizeof(type)>>,                                          \
                  "fixed_size_character_t<" #type "> is different from fixed_size_integer_t<sizeof(" #type ")>")

constexpr void test_to_fixed_character_size_t() noexcept
{
    ASSERT_SAME(char);
    ASSERT_SAME(wchar_t);
    ASSERT_SAME(char8_t);
    ASSERT_SAME(char16_t);
    ASSERT_SAME(char32_t);
}

#undef ASSERT_SAME
#define ASSERT_SAME(is_move, type, expect)                                                                                                      \
    static_assert(std::same_as<cond_move_t<is_move, type>, expect>, "cond_move_t<" #is_move ", " #type "> is different from " #expect)

constexpr void test_cond_move_t() noexcept
{
    ASSERT_SAME(true, int, int&&);
    ASSERT_SAME(true, int&, int&&);
    ASSERT_SAME(true, int&&, int&&);
    ASSERT_SAME(false, int, int&&);
    ASSERT_SAME(false, int&, int&);
    ASSERT_SAME(false, int&&, int&&);
}

#undef ASSERT_SAME
#define ASSERT_SAME(is_move, type)                                                                                                              \
    static_assert(std::same_as<decltype(cond_move_v<is_move>(std::declval<type>())), cond_move_t<is_move, type>>,                               \
                  "decltype(cond_move_v<" #is_move ">(std::declval<" #type ">())) is different from cond_move_t<" #is_move ", " #type ">")

constexpr void test_cond_move_v() noexcept
{
    ASSERT_SAME(true, int);
    ASSERT_SAME(true, int&);
    ASSERT_SAME(true, int&&);
    ASSERT_SAME(false, int);
    ASSERT_SAME(false, int&);
    ASSERT_SAME(false, int&&);
}

#undef ASSERT_SAME
#define ASSERT_SAME(is_rvalue, type, expect)                                                                                                    \
    static_assert(std::same_as<cond_forward_t<is_rvalue, type>, expect>, "cond_forward_t<" #is_rvalue ", " #type "> is different from " #expect)

constexpr void test_cond_forward_t() noexcept
{
    ASSERT_SAME(true, int, int&&);
    ASSERT_SAME(true, int&, int&&);
    ASSERT_SAME(true, int&&, int&&);
    ASSERT_SAME(false, int, int&);
    ASSERT_SAME(false, int&, int&);
    ASSERT_SAME(false, int&&, int&);
}

#undef ASSERT_SAME
#define ASSERT_SAME(is_rvalue, type)                                                                                                            \
    static_assert(std::same_as<decltype(cond_forward_v<is_rvalue>(std::declval<type>())), cond_forward_t<is_rvalue, type>>,                     \
                  "decltype(cond_forward_v<" #is_rvalue ">(std::declval<" #type ">())) is different from cond_forward_t<" #is_rvalue ", " #type \
                  ">")

constexpr void test_cond_forward_v() noexcept
{
    ASSERT_SAME(true, int);
    ASSERT_SAME(true, int&);
    ASSERT_SAME(true, int&&);
    ASSERT_SAME(false, int);
    ASSERT_SAME(false, int&);
    ASSERT_SAME(false, int&&);
}

#undef ASSERT_SAME

template <typename type>
struct test_forward_without_impl
{
};

template <typename type>
struct test_forward_without_const_t_impl : forward_without_const_t<type, std::false_type, test_forward_without_const_t_impl>
{
};

template <typename type>
struct test_forward_without_const_t_impl<test_forward_without_impl<type>> : std::true_type
{
};

template <typename type>
concept test_forward_without_const_t_ = test_forward_without_const_t_impl<type>::value;

constexpr void test_forward_without_const_t() noexcept
{
    static_assert(test_forward_without_const_t_<test_forward_without_impl<int>>);
    static_assert(test_forward_without_const_t_<const test_forward_without_impl<int>>);
    static_assert(!test_forward_without_const_t_<volatile test_forward_without_impl<int>>);
    static_assert(!test_forward_without_const_t_<const volatile test_forward_without_impl<int>>);
    static_assert(!test_forward_without_const_t_<void>);
}

template <typename type>
struct test_forward_without_volatile_t_impl : forward_without_volatile_t<type, std::false_type, test_forward_without_volatile_t_impl>
{
};

template <typename type>
struct test_forward_without_volatile_t_impl<test_forward_without_impl<type>> : std::true_type
{
};

template <typename type>
concept test_forward_without_volatile_t_ = test_forward_without_volatile_t_impl<type>::value;

constexpr void test_forward_without_volatile_t() noexcept
{
    static_assert(test_forward_without_volatile_t_<test_forward_without_impl<int>>);
    static_assert(!test_forward_without_volatile_t_<const test_forward_without_impl<int>>);
    static_assert(test_forward_without_volatile_t_<volatile test_forward_without_impl<int>>);
    static_assert(!test_forward_without_volatile_t_<const volatile test_forward_without_impl<int>>);
    static_assert(!test_forward_without_volatile_t_<void>);
}

template <typename type>
struct test_forward_without_cv_t_impl : forward_without_cv_t<type, std::false_type, test_forward_without_cv_t_impl>
{
};

template <typename type>
struct test_forward_without_cv_t_impl<test_forward_without_impl<type>> : std::true_type
{
};

template <typename type>
concept test_forward_without_cv_t_ = test_forward_without_cv_t_impl<type>::value;

constexpr void test_forward_without_cv_t() noexcept
{
    static_assert(test_forward_without_cv_t_<test_forward_without_impl<int>>);
    static_assert(test_forward_without_cv_t_<const test_forward_without_impl<int>>);
    static_assert(test_forward_without_cv_t_<volatile test_forward_without_impl<int>>);
    static_assert(test_forward_without_cv_t_<const volatile test_forward_without_impl<int>>);
    static_assert(!test_forward_without_cv_t_<void>);
}

constexpr void test_split_into_native_ls_lanes_64() noexcept
{
    constexpr auto size{128 + 64 + 32 + 16 + 8 + 4 + 2 + 1};
    constexpr auto lanes{split_into_native_ls_lanes<64>(size)};
    static_assert(lanes.l64 == 3);
    static_assert(lanes.l32 == 1);
    static_assert(lanes.l16 == 1);
    static_assert(lanes.l8 == 1);
    static_assert(lanes.l4 == 1);
    static_assert(lanes.l2 == 1);
    static_assert(lanes.l1 == 1);
}

constexpr void test_split_into_native_ls_lanes_32() noexcept
{
    constexpr auto size{128 + 64 + 32 + 16 + 4 + 2};
    constexpr auto lanes{split_into_native_ls_lanes<32>(size)};
    static_assert(lanes.l64 == 0);
    static_assert(lanes.l32 == 7);
    static_assert(lanes.l16 == 1);
    static_assert(lanes.l8 == 0);
    static_assert(lanes.l4 == 1);
    static_assert(lanes.l2 == 1);
    static_assert(lanes.l1 == 0);
}

constexpr void test_split_into_native_ls_lanes_16() noexcept
{
    constexpr auto size{128 + 64 + 8 + 4 + 2};
    constexpr auto lanes{split_into_native_ls_lanes<16>(size)};
    static_assert(lanes.l64 == 0);
    static_assert(lanes.l32 == 0);
    static_assert(lanes.l16 == 12);
    static_assert(lanes.l8 == 1);
    static_assert(lanes.l4 == 1);
    static_assert(lanes.l2 == 1);
    static_assert(lanes.l1 == 0);
}

constexpr void test_split_into_native_ls_lanes_8() noexcept
{
    constexpr auto size{128 + 64 + 32 + 16 + 4 + 2 + 1};
    constexpr auto lanes{split_into_native_ls_lanes<8>(size)};
    static_assert(lanes.l64 == 0);
    static_assert(lanes.l32 == 0);
    static_assert(lanes.l16 == 0);
    static_assert(lanes.l8 == 30);
    static_assert(lanes.l4 == 1);
    static_assert(lanes.l2 == 1);
    static_assert(lanes.l1 == 1);
}

constexpr void test_split_into_native_ls_lanes_4() noexcept
{
    constexpr auto size{32 + 16 + 8 + 4 + 2 + 1};
    constexpr auto lanes{split_into_native_ls_lanes<4>(size)};
    static_assert(lanes.l64 == 0);
    static_assert(lanes.l32 == 0);
    static_assert(lanes.l16 == 0);
    static_assert(lanes.l8 == 0);
    static_assert(lanes.l4 == 15);
    static_assert(lanes.l2 == 1);
    static_assert(lanes.l1 == 1);
}

constexpr void test_split_into_native_ls_lanes_small() noexcept
{
    {
        constexpr auto size{2 + 1};
        constexpr auto lanes{split_into_native_ls_lanes<4>(size)};
        static_assert(lanes.l64 == 0);
        static_assert(lanes.l32 == 0);
        static_assert(lanes.l16 == 0);
        static_assert(lanes.l8 == 0);
        static_assert(lanes.l4 == 0);
        static_assert(lanes.l2 == 1);
        static_assert(lanes.l1 == 1);
    }
    {
        constexpr auto size{1};
        constexpr auto lanes{split_into_native_ls_lanes<4>(size)};
        static_assert(lanes.l64 == 0);
        static_assert(lanes.l32 == 0);
        static_assert(lanes.l16 == 0);
        static_assert(lanes.l8 == 0);
        static_assert(lanes.l4 == 0);
        static_assert(lanes.l2 == 0);
        static_assert(lanes.l1 == 1);
    }
    {
        constexpr auto size{0};
        constexpr auto lanes{split_into_native_ls_lanes<4>(size)};
        static_assert(lanes.l64 == 0);
        static_assert(lanes.l32 == 0);
        static_assert(lanes.l16 == 0);
        static_assert(lanes.l8 == 0);
        static_assert(lanes.l4 == 0);
        static_assert(lanes.l2 == 0);
        static_assert(lanes.l1 == 0);
    }
}
