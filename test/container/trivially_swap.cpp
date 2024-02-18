#include "../../include/container/algorithm.h"
#ifdef CPPFASTBOX_HOSTED_TEST
    #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
    #include <doctest/doctest.h>
#else
    #include "../../include/libc/assert.h"
#endif
using namespace cppfastbox;

template <::std::size_t size>
struct test_integer_impl
{
    using type = fixed_size_integer_t<true, size>;
    type a{}, padding_a{}, b{}, padding_b{};

    [[gnu::noinline]] test_integer_impl(type a_in, type b_in) noexcept : a{a_in}, b{b_in} {}

    [[gnu::noinline]] bool operator() () noexcept
    {
        auto old_a{a}, old_b{b};
        trivially_swap(a, b);
        return padding_a == 0 && padding_b == 0 && old_a == b && old_b == a;
    }
};

template <std::size_t size>
struct test_unaligned_array_swap_impl
{
    char a[size]{};
    char padding_a{};
    char b[size]{};
    char padding_b{};

    [[gnu::noinline]] test_unaligned_array_swap_impl(const char a_in, const char b_in) noexcept
    {
        __builtin_memset(a, a_in, size);
        __builtin_memset(b, b_in, size);
    }

    [[gnu::noinline]] bool operator() () noexcept
    {
        char old_a[size]{}, old_b[size]{};
        __builtin_memcpy(old_a, a, size);
        __builtin_memcpy(old_b, b, size);
        trivially_swap(a, b);
        return __builtin_memcmp(a, old_b, size) == 0 && __builtin_memcmp(b, old_a, size) == 0 && padding_a == 0 && padding_b == 0;
    }
};

template <std::size_t size>
    requires (std::has_single_bit(size) && size >= 16 && size <= 64)
struct test_aligned_array_swap_impl
{
    alignas(size) char a[size]{};
    char padding_a{};
    alignas(size) char b[size]{};
    char padding_b{};

    [[gnu::noinline]] test_aligned_array_swap_impl(const char a_in, const char b_in) noexcept
    {
        __builtin_memset(a, a_in, size);
        __builtin_memset(b, b_in, size);
    }

    [[gnu::noinline]] bool operator() () noexcept
    {
        char old_a[size]{}, old_b[size]{};
        __builtin_memcpy(old_a, a, size);
        __builtin_memcpy(old_b, b, size);
        trivially_swap<size>(a, b);
        return __builtin_memcmp(a, old_b, 3) == 0 && __builtin_memcmp(b, old_a, 3) == 0 && padding_a == 0 && padding_b == 0;
    }
};

#ifdef CPPFASTBOX_HOSTED_TEST
TEST_CASE("trivially swap integer")
{
    CHECK(test_integer_impl<1>{12, 34}());
    CHECK(test_integer_impl<2>{12, 34}());
    CHECK(test_integer_impl<4>{12, 34}());
    CHECK(test_integer_impl<8>{12, 34}());
}

TEST_CASE("trivially swap unaligned array")
{
    CHECK(test_unaligned_array_swap_impl<1>{1, 2}());   //< 1
    CHECK(test_unaligned_array_swap_impl<3>{1, 2}());   //< 1+2
    CHECK(test_unaligned_array_swap_impl<5>{1, 2}());   //< 4+1
    CHECK(test_unaligned_array_swap_impl<7>{1, 2}());   //< 4+3
    CHECK(test_unaligned_array_swap_impl<9>{1, 2}());   //< 8+1
    CHECK(test_unaligned_array_swap_impl<11>{1, 2}());  //< 8+3
    CHECK(test_unaligned_array_swap_impl<17>{1, 2}());  //< 16+1
    CHECK(test_unaligned_array_swap_impl<19>{1, 2}());  //< 16+3
    CHECK(test_unaligned_array_swap_impl<33>{1, 2}());  //< 32+1
    CHECK(test_unaligned_array_swap_impl<35>{1, 2}());  //< 32+3
    CHECK(test_unaligned_array_swap_impl<65>{1, 2}());  //< 64+1
    CHECK(test_unaligned_array_swap_impl<67>{1, 2}());  //< 64+3
}

TEST_CASE("trivially swap aligned array")
{
    CHECK(test_aligned_array_swap_impl<16>{1, 2}());  //< 16
    CHECK(test_aligned_array_swap_impl<32>{1, 2}());  //< 32
    CHECK(test_aligned_array_swap_impl<64>{1, 2}());  //< 64
}
#else
int main()
{
    // trivially swap integer
    always_assert(test_integer_impl<1>{12, 34}());
    always_assert(test_integer_impl<2>{12, 34}());
    always_assert(test_integer_impl<4>{12, 34}());
    always_assert(test_integer_impl<8>{12, 34}());
    // trivially swap unaligned array
    always_assert(test_unaligned_array_swap_impl<1>{1, 2}());   //< 1
    always_assert(test_unaligned_array_swap_impl<3>{1, 2}());   //< 1+2
    always_assert(test_unaligned_array_swap_impl<5>{1, 2}());   //< 4+1
    always_assert(test_unaligned_array_swap_impl<7>{1, 2}());   //< 4+3
    always_assert(test_unaligned_array_swap_impl<9>{1, 2}());   //< 8+1
    always_assert(test_unaligned_array_swap_impl<11>{1, 2}());  //< 8+3
    always_assert(test_unaligned_array_swap_impl<17>{1, 2}());  //< 16+1
    always_assert(test_unaligned_array_swap_impl<19>{1, 2}());  //< 16+3
    always_assert(test_unaligned_array_swap_impl<33>{1, 2}());  //< 32+1
    always_assert(test_unaligned_array_swap_impl<35>{1, 2}());  //< 32+3
    always_assert(test_unaligned_array_swap_impl<65>{1, 2}());  //< 64+1
    always_assert(test_unaligned_array_swap_impl<67>{1, 2}());  //< 64+3
    // trivially swap aligned array
    always_assert(test_aligned_array_swap_impl<16>{1, 2}());  //< 16
    always_assert(test_aligned_array_swap_impl<32>{1, 2}());  //< 32
    always_assert(test_aligned_array_swap_impl<64>{1, 2}());  //< 64
}
#endif
