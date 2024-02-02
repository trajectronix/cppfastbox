﻿#pragma once
#if !defined(__cplusplus)
#error "You are not using a C++ compiler"
#endif

#if !defined(__cpp_concepts)
#error "fast_io requires at least C++20 standard compiler."
#else
// fast_io_legacy.h deals with legacy C++ <iostream>/<fstream>/<sstream> interface
#if ((__STDC_HOSTED__ == 1 && (!defined(_GLIBCXX_HOSTED) || _GLIBCXX_HOSTED == 1) &&                                   \
      !defined(_LIBCPP_FREESTANDING)) ||                                                                               \
     defined(FAST_IO_ENABLE_HOSTED_FEATURES))

#if defined(_MSC_VER) && !defined(__clang__)
#pragma warning(push)
#pragma warning(disable : 4514)
#pragma warning(disable : 4668)
#pragma warning(disable : 4710)
#pragma warning(disable : 4711)
#pragma warning(disable : 4820)
#endif

#include <streambuf>
#include <fstream>
#include <sstream>

#if 1
#include "fast_io.h"
#else
#include "fast_io_hosted.h"
#include "fast_io_legacy_impl/c/impl.h"
#endif

#include "fast_io_legacy_impl/filebuf/streambuf_io_observer.h"
#if !defined(_LIBCPP_HAS_NO_FILESYSTEM) || defined(_LIBCPP_HAS_FSTREAM)
#include "fast_io_legacy_impl/filebuf/filebuf_file.h"
#endif
#include "fast_io_legacy_impl/filebuf/op_out.h"
#if defined(_MSC_VER) && !defined(__clang__)
#pragma warning(pop)
#endif

#endif

#endif
