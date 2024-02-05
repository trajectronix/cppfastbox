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

option("check_platform")
    set_showmenu(false)
    on_check(function (option)
        if not has_config("toolchain") then
            raise("${color.failure}The option \"toolchain\" should be set.")
        end
        if get_config("kind") == "binary" then
            raise("${color.failure}The option \"kind\" should be set to static or shared.")
        end
        local plat = get_config("plat")
        if is_plat("cross") then
            plat = get_config("target_os")
            if plat == nil then
                raise("${color.failure}The option \"target_os\" should be set to the target os or platform.")
            end
        end
        local is_cross_compile = ""
        if string.lower(plat) ~= string.lower(get_config("host")) then
            is_cross_compile = "${color.success}yes"
        else
            is_cross_compile = "${color.failure}no"
        end
        cprint("checking for cross compile ... "..is_cross_compile)
        option:enable(true)
    end)
option_end()
option("style")
    set_default("gnu")
    set_values("gnu", "msvc")
    set_description("Set the style of toolchain")
option_end()
