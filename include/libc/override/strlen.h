/**
 * @file strlen.h
 * @brief 声明C风格的strlen和wcslen
 *
 * @copyright Copyright (c) 2024-present Trajectronix Open Source Group
 *
 */
#pragma once
#include "../../base/platform.h"
#include "../strlen.h"

extern "C"
{
    ::std::size_t CPPFASTBOX_CDECL strlen(const char* str);

    ::std::size_t CPPFASTBOX_CDECL wcslen(const wchar_t* str);
}
