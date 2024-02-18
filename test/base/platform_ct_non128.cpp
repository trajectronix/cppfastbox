/**
 * @file platform_ct_nonextension.cpp
 *
 * @copyright Copyright 2024-present Trajectronix Open Source Group
 *
 */
#undef __SIZEOF_INT128__
#undef __SIZEOF_FLOAT128__
#include "../../include/base/platform.h"

using namespace cppfastbox;
using namespace std;

#define NONSUPPORT "No int128 extension, but "

constexpr void test_int128() noexcept
{
    static_assert(!int128_support, NONSUPPORT "int128_support is true");
    static_assert(is_void_v<native_int128_t>, NONSUPPORT "native_int128_t is not void");
    static_assert(is_void_v<native_uint128_t>, NONSUPPORT "native_uint128_t is not void");
    static_assert(!is_native_int128<void>, NONSUPPORT "void meets is_native_int128 constraint");
    static_assert(!is_native_uint128<void>, NONSUPPORT "void meets is_native_uint128 constraint");
}

#undef NONSUPPORT

#define NONSUPPORT "No float128 extension, but "

constexpr void test_float128() noexcept
{
    static_assert(!float128_support, NONSUPPORT "float128_support is true");
    static_assert(is_void_v<native_float128_t>, NONSUPPORT "native_float128_t is not void");
    static_assert(!is_native_float128<void>, NONSUPPORT "void meets is_native_float128 constraint");
}

#undef NONSUPPORT

int main()
{
    test_int128();
    test_float128();
}
