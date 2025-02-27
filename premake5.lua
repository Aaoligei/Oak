workspace "Oak"
	architecture "x64"

	configuration{
		"Debug",
		"Release",
		"Dist"
	}

	outputdir="%{cfg.buildcfg}-%{cfg.system}-%^{cfg.atchitecture}"

project "Oak"
	location "Oak"
	kind "SharedLib"
	language "C++"

	targerdir ("bin/" .. outputdir .. "/%{prj.name}")
	obj ("bin-int/" .. outputdir .. "/%{prj.name}")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs{
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntion "On"
		systemversion "10.0.22621.0"

		defines{
			"OAK_PLATFORM_WINDOWS",
			"OAK_BUILD_DLL",
		}

		postbuildcommands{
			("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "OAK_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "OAK_RELEASE"
		symbols "On"

	filter "configurations:Dist"
		defines "OAK_DIST"
		symbols "On"

project "Sandbox"
	location "Sandbox
	kind "ConsoleApp"
	language "C++"

	targerdir ("bin/" .. outputdir .. "/%{prj.name}")
	obj ("bin-int/" .. outputdir .. "/%{prj.name}")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs{
		"Oak/vendor/spdlog/include",
		"Oak/src"
	}

	links{
		"Oak"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntion "On"
		systemversion "10.0.22621.0"

		defines{
			"OAK_PLATFORM_WINDOWS"
		}

		
	filter "configurations:Debug"
		defines "OAK_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "OAK_RELEASE"
		symbols "On"

	filter "configurations:Dist"
		defines "OAK_DIST"
		symbols "On"