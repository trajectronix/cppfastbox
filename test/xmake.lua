-- Copyright (c) 2024-present Trajectronix Open Source Group
if get_config("hosted_test") then
    add_defines("CPPFASTBOX_HOSTED_TEST")
    add_requires("doctest")
end
for _, dir in ipairs(os.dirs("./*")) do
test_name = "unit_test_" .. dir
target(test_name.."_ct")
    set_default(false)
    set_kind("object")
    add_files("null.cpp")
    for _, file in ipairs(os.files(dir.."/*_ct.cpp")) do
        name = string.sub(path.basename(file), 1, -4)
        if name:endswith("fail") then
            add_tests(name, {files = file, build_should_fail = true, group = test_name})
        else
            add_tests(name, {files = file, build_should_pass = true, group = test_name})
        end
    end
    set_group(test_name)
target_end()
target(test_name.."_rt")
    set_default(false)
    set_kind("binary")
    add_files("null.cpp")
    for _, file in ipairs(os.files(dir.."/*_rt.cpp")) do
        name = string.sub(path.basename(file), 1, -4)
        add_tests(name, {files = file, remove_files = "null.cpp", packages = get_config("hosted_test") and "doctest" or nil, group = test_name})
    end
    set_group(test_name)
target_end()
end
