﻿#pragma once

namespace fast_io::details
{

template <typename T> inline constexpr void clear_basic_io_filter_pointers(T &t) noexcept
{
    using traits_type = typename T::traits_type;
    constexpr auto mode{traits_type::mode};
    if constexpr ((mode & buffer_mode::in) == buffer_mode::in)
    {
        t.input_buffer.buffer_curr = t.input_buffer.buffer_begin;
    }
}

template <typename T> inline constexpr void destroy_basic_io_filter(T &t) noexcept
{
    using traits_type = typename T::traits_type;
    using allocator_type = traits_type::allocator_type;
    constexpr auto mode{traits_type::mode};

    if constexpr ((mode & buffer_mode::in) == buffer_mode::in)
    {
        auto buffer_begin{t.input_buffer.buffer_begin};
        if (buffer_begin)
        {
            if constexpr ((mode & buffer_mode::secure_clear) == buffer_mode::secure_clear)
            {
                secure_clear(buffer_begin,
                             traits_type::input_buffer_size * sizeof(typename traits_type::input_char_type));
            }
            ::fast_io::typed_generic_allocator_adapter<
                allocator_type, typename traits_type::output_char_type>::deallocate_n(buffer_begin,
                                                                                      traits_type::input_buffer_size);
        }
    }
}

} // namespace fast_io::details