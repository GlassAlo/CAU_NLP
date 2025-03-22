set_project("boolean-IR")
set_project("vector-IR")

if is_plat("windows") then
    add_toolchains("msvc")
else
    add_toolchains("clang")
end

set_languages("cxx23")
add_rules("mode.debug", "mode.release")

includes("boolean_src")
includes("vector_src")
