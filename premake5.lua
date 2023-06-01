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
    IncludeDir["GLFW"]      = "LearnOpenGL/vendor/GLFW/include"
    IncludeDir["glad"]      = "LearnOpenGL/vendor/glad/include"
    IncludeDir["assimp"]    = "LearnOpenGL/vendor/assimp/include"
    IncludeDir["glm"]       = "LearnOpenGL/vendor/glm"

    group "Dependencies"
        include "LearnOpengl/vendor/GLFW"
        include "LearnOpengl/vendor/glad"
        include "LearnOpengl/vendor/assimp"
    group ""

project "LearnOpengl"
    location "LearnOpengl"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    runtime "Debug"
    symbols "on"

    staticruntime "on"

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
        "%{IncludeDir.assimp}",
        "%{IncludeDir.glm}",
        "%{prj.name}/vendor"
    }

    links
    {
        "GLFW",
        "glad",
        "assimp",
        "opengl32.lib"
    }

    defines
    {
        "GLFW_INCLUDE_NONE",
        "_CRT_SECURE_NO_WARNINGS",
        "STB_IMAGE_IMPLEMENTATION"
    }
    
    filter "system:windows"
        systemversion "latest"