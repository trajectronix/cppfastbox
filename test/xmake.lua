includes("*/xmake.lua")

if get_config("hosted_test") then
    add_defines("CPPFASTBOX_HOSTED_TEST")
    add_requires("doctest")
end

target("unit_test")
    set_kind("phony")
    add_deps("base_uint_test", "container_uint_test")
target_end()
