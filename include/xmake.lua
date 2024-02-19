-- Copyright (c) 2024-present Trajectronix Open Source Group
target("container")
    set_kind("headeronly")
    add_headerfiles("container/*.h", {prefixdir = "container"})
target_end()
target("libc-header")
    set_kind("headeronly")
    add_headerfiles("libc/*.h", {prefixdir = "libc"})
target_end()
target("base")
    set_kind("headeronly")
    add_headerfiles("base/*.h", {prefixdir = "base"})
target_end()
