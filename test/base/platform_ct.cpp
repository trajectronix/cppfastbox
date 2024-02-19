/**
 * @file platform_ct.cpp
 * @brief platform.h编译时测试
 *
 * @copyright Copyright (c) 2024-present Trajectronix Open Source Group
 *
 */
#include "../../include/base/platform.h"

using namespace cppfastbox;
using namespace std;

#define SUPPORT "Support int128 extension, but "
#define NONSUPPORT "No int128 extension, but "

constexpr void test_int128() noexcept
{
#ifdef __SIZEOF_INT128__
    static_assert(int128_support, SUPPORT "int128_support is false");
    static_assert(same_as<native_int128_t, __int128_t>, SUPPORT "native_int128_t is not __int128_t");
    static_assert(same_as<native_uint128_t, __uint128_t>, SUPPORT "native_uint128_t is not __uint128_t");
    static_assert(is_native_int128<native_int128_t>, SUPPORT "native_int128_t does not meet is_native_int128 constraint");
    static_assert(is_native_uint128<native_uint128_t>, SUPPORT "native_uint128_t does not meet is_native_uint128 constraint");
#else
    static_assert(!int128_support, NONSUPPORT "int128_support is true");
    static_assert(is_void_v<native_int128_t>, NONSUPPORT "native_int128_t is not void");
    static_assert(is_void_v<native_uint128_t>, NONSUPPORT "native_uint128_t is not void");
    static_assert(!is_native_int128<void>, NONSUPPORT "void meets is_native_int128 constraint");
    static_assert(!is_native_uint128<void>, NONSUPPORT "void meets is_native_uint128 constraint");
#endif
}

#undef SUPPORT
#undef NONSUPPORT

#define SUPPORT "Support float128 extension, but "
#define NONSUPPORT "No float128 extension, but "

constexpr void test_float128() noexcept
{
#ifdef __SIZEOF_FLOAT128__
    static_assert(float128_support, SUPPORT "float128_support is false");
    static_assert(same_as<native_float128_t, __float128>, SUPPORT "native_float128_t is not __float128");
    static_assert(is_native_float128<__float128>, SUPPORT "__float128 does not meet is_native_float128 constraint");
#else
    static_assert(!float128_support, NONSUPPORT "float128_support is true");
    static_assert(is_void_v<native_float128_t>, NONSUPPORT "native_float128_t is not void");
    static_assert(!is_native_float128<void>, NONSUPPORT "void meets is_native_float128 constraint");
#endif
}

#undef SUPPORT
#undef NONSUPPORT
