-- Copyright (c) 2024-present Trajectronix Open Source Group
target("libc-lib")
    add_files("libc/*.cpp")
    set_kind("$(kind)")
    set_basename("override")
    set_prefixname(is_config("style", "gnu") and "lib" or "")
    set_extension(is_config("style", "gnu") and ".a" or ".lib")
target_end()
