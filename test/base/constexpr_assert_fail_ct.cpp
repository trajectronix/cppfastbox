#include "../../include/base/assert.h"
using namespace cppfastbox;

consteval void g(int i) noexcept { constexpr_assert(i==0); }
constexpr void h(int i) noexcept { constexpr_assert(i==0); }

void j() noexcept { g(1); }
