#pragma once
#include "../../base/platform.h"
#include "../strlen.h"

extern "C"
{
    ::std::size_t CPPFASTBOX_CDECL strlen(const char* str);

    ::std::size_t CPPFASTBOX_CDECL wcslen(const wchar_t* str);
}
