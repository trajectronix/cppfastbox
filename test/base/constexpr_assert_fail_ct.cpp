/**
 * @file constexpr_assert_fail_ct.cpp
 * @brief constexpr_assert编译时测试，该测试应该编译失败
 *
 * @copyright Copyright 2024-present Trajectronix Open Source Group
 *
 */
#include "../../include/base/assert.h"
using namespace cppfastbox;

consteval void g(int i) noexcept { constexpr_assert(i==0); }
constexpr void h(int i) noexcept { constexpr_assert(i==0); }

void j() noexcept { g(1); }
