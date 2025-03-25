-- Create the IR project
target("boolean-IR")

    -- Set the project kind to binary
    set_kind("binary")

    -- Add the source files
    add_files("**.cpp")
    add_files("../Shared/**.cpp")

    -- Add the -std=c++23 flag
    add_cxxflags("-std=c++23", "-lstdc++")

    -- Set the target directory to bin/tests
    set_targetdir("../../bin")

    add_includedirs("../Shared")
    add_headerfiles("../Shared/*.h**")

    -- Add the boost library
    add_packages("boost")
    add_packages("nlohmann_json")

    -- Set the warnings to all (-Wall)
    set_warnings("allextra", "pedantic", "more")

    -- Set the build modes
    -- If the mode is debug, set the optimization to none and the symbols to debug
    if is_mode("debug") then
        set_optimize("none")
        set_symbols("debug")
    end

    -- If the mode is release, set the optimization to fastest and the symbols to hidden
    if is_mode("release") then
        set_optimize("fastest")
        set_symbols("hidden")
    end

    -- Define the _CRT_SECURE_NO_WARNINGS macro for the MSVC compiler (in case)
    add_defines("_CRT_SECURE_NO_WARNINGS")