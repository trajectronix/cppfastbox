/**
 * @file libc_override.cpp
 * @brief 在独立的翻译单元中覆盖strlen和wcslen
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "../../include/libc/override.h"

extern "C"
{
    ::std::size_t CPPFASTBOX_CDECL strlen(const char* str)
    {
        return ::cppfastbox::libc::strlen(str);
    }
    ::std::size_t CPPFASTBOX_CDECL wcslen(const wchar_t* str)
    {
        return ::cppfastbox::libc::strlen(str);
    }
}
