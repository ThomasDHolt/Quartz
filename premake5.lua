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

project "Quartz"
	location "Quartz"
	kind "SharedLib"
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
		"${prj.name}/src",
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:Windows"
		cppdialect = "C++14"
		staticruntime = "On"
		systemversion "latest"

		defines
		{
			"QT_PLATFORM_WINDOWS",
			"QT_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/sandbox")
		}

	filter "configurations:Debug"
		defines "QT_DEBUG"
		symbols "On"
	
	filter "configurations:Release"
		defines "QT_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "QT_DIST"
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
		symbols "On"
	
	filter "configurations:Release"
		defines "QT_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "QT_DIST"
		optimize "On"