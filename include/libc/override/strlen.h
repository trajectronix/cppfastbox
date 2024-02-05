#pragma once
#include "../../base/platform.h"
#include "../strlen.h"

extern "C"
{
    
    ::std::size_t CPPFASTBOX_CDECL strlen(const char* str) { return ::traject::libc::strlen(str); }

    ::std::size_t CPPFASTBOX_CDECL wcslen(const wchar_t* str) { return ::traject::libc::strlen(str); }
}
