/**
 * @file split_into_native_ls_lanes_rt.cpp
 * @brief 测试split_into_native_ls_lanes的运行时实现
 *
 * @copyright Copyright (c) 2024-present Trajectronix Open Source Group
 *
 */
#include "../../include/base/utility.h"
#ifdef CPPFASTBOX_HOSTED_TEST
    #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
    #include <doctest/doctest.h>
    #define CPPFASTBOX_ASSERT CHECK
    #define CPPFASTBOX_TEST(name) TEST_CASE(#name)
#else
    #include "../../include/libc/assert.h"
    #define CPPFASTBOX_ASSERT always_assert
    #define CPPFASTBOX_TEST(name) void name() noexcept
#endif
using namespace cppfastbox;

CPPFASTBOX_TEST(test_split_into_native_ls_lanes_64)
{
    constexpr auto size{128 + 64 + 32 + 16 + 8 + 4 + 2 + 1};
    auto lanes{split_into_native_ls_lanes<64>(size)};
    CPPFASTBOX_ASSERT(lanes.l64 == 3);
    CPPFASTBOX_ASSERT(lanes.l32 == 1);
    CPPFASTBOX_ASSERT(lanes.l16 == 1);
    CPPFASTBOX_ASSERT(lanes.l8 == 1);
    CPPFASTBOX_ASSERT(lanes.l4 == 1);
    CPPFASTBOX_ASSERT(lanes.l2 == 1);
    CPPFASTBOX_ASSERT(lanes.l1 == 1);
}

CPPFASTBOX_TEST(test_split_into_native_ls_lanes_32)
{
    constexpr auto size{128 + 64 + 32 + 16 + 4 + 2};
    auto lanes{split_into_native_ls_lanes<32>(size)};
    CPPFASTBOX_ASSERT(lanes.l64 == 0);
    CPPFASTBOX_ASSERT(lanes.l32 == 7);
    CPPFASTBOX_ASSERT(lanes.l16 == 1);
    CPPFASTBOX_ASSERT(lanes.l8 == 0);
    CPPFASTBOX_ASSERT(lanes.l4 == 1);
    CPPFASTBOX_ASSERT(lanes.l2 == 1);
    CPPFASTBOX_ASSERT(lanes.l1 == 0);
}

CPPFASTBOX_TEST(test_split_into_native_ls_lanes_16)
{
    constexpr auto size{128 + 64 + 8 + 4 + 2};
    auto lanes{split_into_native_ls_lanes<16>(size)};
    CPPFASTBOX_ASSERT(lanes.l64 == 0);
    CPPFASTBOX_ASSERT(lanes.l32 == 0);
    CPPFASTBOX_ASSERT(lanes.l16 == 12);
    CPPFASTBOX_ASSERT(lanes.l8 == 1);
    CPPFASTBOX_ASSERT(lanes.l4 == 1);
    CPPFASTBOX_ASSERT(lanes.l2 == 1);
    CPPFASTBOX_ASSERT(lanes.l1 == 0);
}

CPPFASTBOX_TEST(test_split_into_native_ls_lanes_8)
{
    constexpr auto size{128 + 64 + 32 + 16 + 4 + 2 + 1};
    auto lanes{split_into_native_ls_lanes<8>(size)};
    CPPFASTBOX_ASSERT(lanes.l64 == 0);
    CPPFASTBOX_ASSERT(lanes.l32 == 0);
    CPPFASTBOX_ASSERT(lanes.l16 == 0);
    CPPFASTBOX_ASSERT(lanes.l8 == 30);
    CPPFASTBOX_ASSERT(lanes.l4 == 1);
    CPPFASTBOX_ASSERT(lanes.l2 == 1);
    CPPFASTBOX_ASSERT(lanes.l1 == 1);
}

CPPFASTBOX_TEST(test_split_into_native_ls_lanes_4)
{
    constexpr auto size{32 + 16 + 8 + 4 + 2 + 1};
    auto lanes{split_into_native_ls_lanes<4>(size)};
    CPPFASTBOX_ASSERT(lanes.l64 == 0);
    CPPFASTBOX_ASSERT(lanes.l32 == 0);
    CPPFASTBOX_ASSERT(lanes.l16 == 0);
    CPPFASTBOX_ASSERT(lanes.l8 == 0);
    CPPFASTBOX_ASSERT(lanes.l4 == 15);
    CPPFASTBOX_ASSERT(lanes.l2 == 1);
    CPPFASTBOX_ASSERT(lanes.l1 == 1);
}

CPPFASTBOX_TEST(test_split_into_native_ls_lanes_small)
{
    {
        constexpr auto size{2 + 1};
        auto lanes{split_into_native_ls_lanes<4>(size)};
        CPPFASTBOX_ASSERT(lanes.l64 == 0);
        CPPFASTBOX_ASSERT(lanes.l32 == 0);
        CPPFASTBOX_ASSERT(lanes.l16 == 0);
        CPPFASTBOX_ASSERT(lanes.l8 == 0);
        CPPFASTBOX_ASSERT(lanes.l4 == 0);
        CPPFASTBOX_ASSERT(lanes.l2 == 1);
        CPPFASTBOX_ASSERT(lanes.l1 == 1);
    }
    {
        constexpr auto size{1};
        auto lanes{split_into_native_ls_lanes<4>(size)};
        CPPFASTBOX_ASSERT(lanes.l64 == 0);
        CPPFASTBOX_ASSERT(lanes.l32 == 0);
        CPPFASTBOX_ASSERT(lanes.l16 == 0);
        CPPFASTBOX_ASSERT(lanes.l8 == 0);
        CPPFASTBOX_ASSERT(lanes.l4 == 0);
        CPPFASTBOX_ASSERT(lanes.l2 == 0);
        CPPFASTBOX_ASSERT(lanes.l1 == 1);
    }
    {
        constexpr auto size{0};
        auto lanes{split_into_native_ls_lanes<4>(size)};
        CPPFASTBOX_ASSERT(lanes.l64 == 0);
        CPPFASTBOX_ASSERT(lanes.l32 == 0);
        CPPFASTBOX_ASSERT(lanes.l16 == 0);
        CPPFASTBOX_ASSERT(lanes.l8 == 0);
        CPPFASTBOX_ASSERT(lanes.l4 == 0);
        CPPFASTBOX_ASSERT(lanes.l2 == 0);
        CPPFASTBOX_ASSERT(lanes.l1 == 0);
    }
}

#ifndef CPPFASTBOX_HOSTED_TEST
int main()
{
    test_split_into_native_ls_lanes_64();
    test_split_into_native_ls_lanes_32();
    test_split_into_native_ls_lanes_16();
    test_split_into_native_ls_lanes_8();
    test_split_into_native_ls_lanes_4();
    test_split_into_native_ls_lanes_small();
}
#endif
