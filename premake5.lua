workspace "brickstone"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release"
	}
	
outputDir = "%{cfg.buildcfg}-%{cfg.architecture}"
	
includeDir = {}
libDir = {}

--SPDLOG
includeDir["SPDLOG"] = "vendor/spdlog/include"

--GLEW
includeDir["GLEW"] = "vendor/GLEW/include"
libDir["GLEW"] = "vendor/GLEW/lib"

--SDL
includeDir["SDL"] = "vendor/SDL/include"
libDir["SDL"] = "vendor/SDL/lib"

--ASSIMP
includeDir["ASSIMP"] = "vendor/assimp/include"
libDir["ASSIMP"] = "vendor/assimp/lib"

project "brickstone"
	location "brickstone"
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")
	
	pchheader "bspch.h"
	pchsource "brickstone/src/bspch.cpp"
	
	ignoredefaultlibraries { "libcmt.lib" }
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{includeDir.SPDLOG}",
		"%{includeDir.GLEW}",
		"%{includeDir.SDL}",
		"%{includeDir.ASSIMP}"
	}
	
	libdirs
	{
		"%{libDir.GLEW}",
		"%{libDir.SDL}",
		"%{libDir.ASSIMP}"
	}
	
	links
	{	
		"SDL2.lib",
		"SDL2main.lib",
		"glu32.lib",
		"glew32s.lib",
		"opengl32.lib",
		"assimp-vc140-mt.lib"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"BS_PLATFORM_WINDOWS",
			"NOMINMAX",
			"GLEW_STATIC",
			"_CRT_SECURE_NO_WARNINGS"
		}
		
	filter "configurations:Debug"
		defines "BS_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "BS_RELEASE"
		optimize "On"