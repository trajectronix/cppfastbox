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