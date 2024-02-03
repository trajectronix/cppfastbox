/**
 * @file assert.h
 * @brief 断言实现
 *
 * @copyright Copyright 2024-present Trajectronix Open Source Group
 *
 */
#pragma once
#include <source_location>
#include <utility>
#if __has_include(<cstdio>)
    #include <cstdio>
    #define CPPFASTBOX_ASSERT_WITH_MESSAGE
#endif
#include "../base/assert.h"
// 实现itoa后替换此处
#include <charconv>
#undef assert

namespace cppfastbox
{
    namespace detail
    {
#if __has_include(<cstdio>)
        [[noreturn]] inline void assert_failed(const char* file, unsigned line, unsigned colum, const char* function) noexcept
        {
            fwrite("Assert failed: In ", 1, 18, stderr);
            fwrite(file, 1, __builtin_strlen(file), stderr);
            fwrite(" ", 1, 1, stderr);
            char buf[32]{};
            auto res{std::to_chars(buf, buf + 32, line).ptr};
            *res++ = ':';
            res = std::to_chars(res, buf + 32, colum).ptr;
            __builtin_memcpy(res, " function: ", 11);
            fwrite(buf, 1, res - buf, stderr);
            fwrite(function, 1, __builtin_strlen(function), stderr);
            fast_fail();
        }
#else
        [[noreturn]] inline void assert_failed(const char*, unsigned, unsigned, const char*) noexcept { fast_fail(); }
#endif
    }  // namespace detail

    /**
     * @brief 断言
     *
     * @param expression 要断言的表达式
     * @param location 要输出的位置信息
     * @note 需要libc才能输出错误消息
     */
    constexpr inline void assert(bool expression, std::source_location location = std::source_location::current()) noexcept
    {
        if consteval { constexpr_assert(expression); }
        else
        {
            if constexpr(!is_release)
            {
                if(!expression) [[unlikely]]
                {
                    detail::assert_failed(location.file_name(), location.line(), location.column(), location.function_name());
                }
            }
        }
    }

    /**
     * @brief 不受is_release影响的断言
     *
     * @param expression 要断言的表达式
     * @param location 要输出的位置信息
     * @note 需要libc才能输出错误消息
     */
    constexpr inline void always_assert(bool expression, std::source_location location = std::source_location::current()) noexcept
    {
        if consteval { constexpr_assert(expression); }
        else
        {
            if(!expression) { detail::assert_failed(location.file_name(), location.line(), location.column(), location.function_name()); }
        }
    }
}  // namespace cppfastbox
