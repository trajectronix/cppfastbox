/**
 * @file min_max_ct.cpp
 * @brief min和max函数编译时测试
 *
 * @copyright Copyright (c) 2024-present Trajectronix Open Source Group
 *
 */
#include "../../include/base/min_max.h"
#include <functional>
using namespace cppfastbox;

constexpr void test_min() noexcept
{
    static_assert(min(1, 2) == 1, "min(1,2) is not 1");
    static_assert(min(1, 2, std::less{}) == 1, "min(1, 2, std::less{}) is not 1");
}

constexpr void test_max() noexcept
{
    static_assert(max(1, 2) == 2, "max(1,2) is not 2");
    static_assert(max(1, 2, std::less{}) == 2, "max(1, 2, std::less{}) is not 2");
}
