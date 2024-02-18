/**
 * @file assert.h
 * @brief 基础断言实现
 *
 * @copyright Copyright 2024-present Trajectronix Open Source Group
 *
 */
#pragma once
#include <utility>
#include <cstdlib>
#include "platform.h"

namespace cppfastbox
{
    /**
     * @brief 快速退出程序
     *
     */
    [[noreturn]] inline void fast_fail() noexcept { ::std::_Exit(1); }

    /**
     * @brief 若expression为false则引发编译期计算失败
     *
     * @param expression 要断言的表达式
     */
    constexpr inline void constexpr_assert(bool expression) noexcept
    {
        if(!expression) { std::unreachable(); }
    }

    namespace detail
    {
        /**
         * @brief 不依赖系统的断言
         *
         * @param expression 要断言的表达式
         * @note 不会输出错误信息
         */
        constexpr inline void assert(bool expression) noexcept
        {
            if consteval { constexpr_assert(expression); }
            else
            {
                if constexpr(!is_release)
                {
                    if(!expression) [[unlikely]] { fast_fail(); }
                }
            }
        }

        /**
         * @brief 不受is_release影响的，不依赖系统的断言
         *
         * @param expression 要断言的表达式
         * @note 不会输出错误信息
         */
        constexpr inline void always_assert(bool expression) noexcept
        {
            if consteval { constexpr_assert(expression); }
            else
            {
                if(!expression) [[unlikely]] { fast_fail(); }
            }
        }
    }  // namespace detail
}  // namespace cppfastbox
