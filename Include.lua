local glfwDir = path.join(_SCRIPT_DIR, "lib", "glfw-3.4")

filter "system:windows" -- I have no clue why Visual Studio won't compile without this, frick you, Microsoft
        buildoptions { "/utf-8" }
        defines { "_UNICODE", "UNICODE" }

project "glfw3"
    kind "StaticLib"
    language "C"

    -- We need to compile GLFW manually, as it is not a Premake project
    filter "system:windows"
        prebuildcommands {
            "cmake -S " .. glfwDir .. " .",
            "cmake --build . --config %{cfg.buildcfg}",
            "{COPYFILE} src/%{cfg.buildcfg}/*glfw* bin/%{cfg.buildcfg}"
        }
    filter {}

    filter "system:not windows"
        prebuildcommands {
            "cmake -S " .. glfwDir .. " .",
            "cmake --build . --config %{cfg.buildcfg}",
            "{MKDIR} bin/%{cfg.buildcfg}",
            "{COPYFILE} src/*glfw3* bin/%{cfg.buildcfg}"
        }
    filter {}

project "TinyChernoLib"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    targetdir "%{prj.location}/bin/%{cfg.buildcfg}"
    defines { "SPDLOG_COMPILED_LIB" }

    dependson { "glfw3" }

    files {
        "src/**",
        "lib/glad/src/**",
        "lib/spdlog/src/**"
    }

    includedirs {
        "src",
        "lib/glfw-3.4/include",
        "lib/glad/include",
        "lib/spdlog/include"
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "on"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "on"

    filter "toolset:clang or gcc"
        buildoptions { "-Wall", "-Werror" }
