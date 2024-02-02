option("march")
    set_default("native")
    set_description("Set compiler option \"-march\"")
    after_check(function (option)
        import("core.tool.compiler")
        local flag = vformat("-march=$(march)")
        if not compiler.has_flags("cxx", flag) then
            raise("${color.failure}The compiler doesn't support \"%s\" option.", flag)
        end
        option:add("cxflags", flag)
    end)
option_end()
option("mtune")
    set_default("native")
    set_description("Set compiler option \"-mtune\"")
    after_check(function (option)
        import("core.tool.compiler")
        local flag = vformat("-mtune=$(mtune)")
        if not compiler.has_flags("cxx", flag) then
            raise("${color.failure}The compiler doesn't support \"%s\" option.", flag)
        end
        option:add("cxflags", flag)
    end)
option_end()
option("coroutines")
    set_description("Whether the compiler support -fcoroutines")
    on_check(function (option)
        import("core.tool.compiler")
        if compiler.has_flags("cxx", "-fcoroutines") then
            option:add("cxxflags", "-fcoroutines")
            option:enable(true)
        end
    end)
option_end()
