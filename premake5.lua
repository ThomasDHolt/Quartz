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

include "Quartz/vendor/glfw"
include "Quartz/vendor/glad"
include "Quartz/vendor/imgui"

project "Quartz"
	location "Quartz"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "qtpch.h"
	pchsource "Quartz/src/qtpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:Windows"
		cppdialect = "C++14"
		staticruntime = "On"
		systemversion "latest"

		defines
		{
			"QT_PLATFORM_WINDOWS",
			"QT_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/sandbox")
		}

	filter "configurations:Debug"
		defines "QT_DEBUG"
		buildoptions "/MDd"
		symbols "On"
	
	filter "configurations:Release"
		defines "QT_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "QT_DIST"
		buildoptions "/MD"
		optimize "On"

project "Sandbox"
	location "sandbox"
	kind "ConsoleApp"
	language "C++"

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
		"Quartz/src"
	}

	links
	{
		"Quartz"
	}

	filter "system:Windows"
		cppdialect = "C++14"
		staticruntime = "On"
		systemversion "latest"

		defines
		{
			"QT_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "QT_DEBUG"
		buildoptions "/MDd"
		symbols "On"
	
	filter "configurations:Release"
		defines "QT_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "QT_DIST"
		buildoptions "/MD"
		optimize "On"