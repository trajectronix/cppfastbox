/**
 * @file constexpr_assert_pass_ct.cpp
 * @brief constexpr_assert编译时测试
 *
 * @copyright Copyright (c) 2024-present Trajectronix Open Source Group
 *
 */
#include "../../include/base/assert.h"
using namespace cppfastbox;

consteval void g(int i) noexcept { constexpr_assert(i == 0); }

constexpr void h(int i) noexcept { constexpr_assert(i == 0); }

void j() noexcept { g(0); }
