set_project("boolean-IR")
set_project("vector-IR")

add_requires("boost", "nlohmann_json")

if is_os("windows") then
    add_toolchains("msvc")
else
    add_toolchains("clang")
end

set_languages("cxx23")
add_rules("mode.debug", "mode.release")

includes("src")
