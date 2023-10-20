workspace "Quartz"
	architecture "x64"
	startproject "sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Quartz/vendor/glfw/include"
IncludeDir["Glad"] = "Quartz/vendor/glad/include"
IncludeDir["ImGui"] = "Quartz/vendor/imgui"
IncludeDir["glm"] = "Quartz/vendor/glm"
IncludeDir["stb_image"] = "Quartz/vendor/stb_image"

include "Quartz/vendor/glfw"
include "Quartz/vendor/glad"
include "Quartz/vendor/imgui"

project "Quartz"
	location "Quartz"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "qtpch.h"
	pchsource "Quartz/src/qtpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:Windows"
		systemversion "latest"

		defines
		{
			"QT_PLATFORM_WINDOWS",
			"QT_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "QT_DEBUG"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines "QT_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "QT_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Quartz/vendor/spdlog/include",
		"Quartz/src",
		"Quartz/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Quartz"
	}

	filter "system:Windows"
		systemversion "latest"

		defines
		{
			"QT_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "QT_DEBUG"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines "QT_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "QT_DIST"
		runtime "Release"
		optimize "on"