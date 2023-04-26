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
        "%{prj.name}/vendor/glm/glm/**.inl",
        "%{prj.name}/res/*.jpg",
        "%{prj.name}/src/Shaders/*.frag",
        "%{prj.name}/src/Shaders/*.vert",
        "%{prj.name}/vendor/stb_image/stb_image.h"
    }

    includedirs
    {
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.glad}",
        "%{IncludeDir.glm}",
        "%{prj.name}/vendor"
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
        "_CRT_SECURE_NO_WARNINGS",
        "STB_IMAGE_IMPLEMENTATION"
    }
    
    cppdialect "C++17"
    runtime "Debug"
    symbols "On"
    systemversion "latest"