workspace "LearnOpengl"
    architecture "x64"
    startproject "LearnOpengl"

    configurations
    {
        "Debug", 
		"Release"
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    IncludeDir = {}
    IncludeDir["GLFW"] = "LearnOpengl/vendor/GLFW/include"
    IncludeDir["glad"] = "LearnOpengl/vendor/glad/include"
    IncludeDir["glm"] = "LearnOpengl/vendor/glm"

    group "Dependencies"
        include "LearnOpengl/vendor/GLFW"
        include "LearnOpengl/vendor/glad"
    group ""

project "LearnOpengl"
    location "LearnOpengl"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files 
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl"
    }

    includedirs
    {
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.glad}",
        "%{IncludeDir.glm}"
    }

    links
    {
        "GLFW",
        "glad",
        "opengl32.lib"
    }

    defines
    {
        "GLFW_INCLUDE_NONE",
        "_CRT_SECURE_NO_WARNINGS"
    }
    
    cppdialect "C++17"
    runtime "Debug"
    symbols "On"
    systemversion "latest"