solution "Game"
	configurations { "Release", "Debug" }

	local basedir = "build"
	location(basedir)

project "game"
	targetname  "Game"
	language    "C++"
	kind        "WindowedApp"
	flags       { "FatalWarnings" }	
	
	includedirs { 
		"src/engine/common",
		"libs" 
	}

	files {
		"src/engine/common/**.h", 
		"src/engine/common/**.cpp",
		"src/game/**.h", 
		"src/game/**.cpp"
	}

	excludes { }

	--
	-- PS3
	--
	configuration { "ps3" }
		targetextension(".elf")
		postbuildcommands { "C://usr//local//cell//host-win32//bin//make_fself $(OutDir)//Game.elf $(OutDir)//game.self" }
		defines     { "SN_TARGET_PS3", "__SNC__", "__CELL_ASSERT__", "PLATFORM_PS3"}
		buildoptions "-Xc+=exceptions --diag_suppress=383 --diag_suppress=613 --diag_suppress=1011"
		linkoptions  "-lsn -lm -lio_stub -lfs_stub -lgcm_cmd -lgcm_sys_stub -lsysmodule_stub -lsysutil_stub -lcgc"

		includedirs { 
			"C:/usr/local/cell/target/ppu/include",
			"C:/usr/local/cell/target/common/include"
		}
		includedirs { 
			"src/engine/common/renderer",
			"src/engine/platform/renderer/gcm",
			"src/engine/common/input",
			"src/engine/platform/input/ps3",
			"src/engine/platform/platform/ps3"
		}
		files {
			"src/engine/platform/renderer/gcm/**.h", 
			"src/engine/platform/renderer/gcm/**.cpp",
			"src/engine/platform/platform/ps3/**.h", 
			"src/engine/platform/platform/ps3/**.cpp",
			"src/engine/platform/input/ps3/**.h", 
			"src/engine/platform/input/ps3/**.cpp"
		}
		libdirs {
			"C:/usr/local/cell/target/ppu/lib"
		}

	configuration 	{ "Debug" }
		defines     { "_DEBUG", "GPU_TRACE" }
		flags       { "Symbols" }
		
	configuration 	{ "Release" }
		defines     "NDEBUG"
		flags       { "OptimizeSpeed" }

	--
	-- Windows
	--

	configuration { "vs2008", "x32" }
		defines     { "_CRT_SECURE_NO_WARNINGS", "_WIN32", "PLATFORM_WINDOWS" }
		links {
			"d3dcompiler",
			"dxguid",
			"dinput8",
			"d3d9",
			"d3d11",
			"d3dx10",
			"d3dx11"
		}
		includedirs { 
			"src/engine/common/renderer",
			"src/engine/platform/renderer/dx11",
			"src/engine/common/input",
			"src/engine/platform/input/win",
			"src/engine/platform/platform/win"
		}
		files {
			"src/engine/platform/renderer/dx11/**.h", 
			"src/engine/platform/renderer/dx11/**.cpp",
			"src/engine/platform/platform/win/**.h", 
			"src/engine/platform/platform/win/**.cpp",
			"src/engine/platform/input/win/**.h", 
			"src/engine/platform/input/win/**.cpp"
		}

	-- 
	-- OSX
	--
	configuration "macosx"
		buildoptions "-stdlib=libc++"
		linkoptions  "-stdlib=libc++"
		defines     { "PLATFORM_MAC" }
		links {
			"AppKit.framework",
			"Foundation.framework", 
			"CoreServices.framework",
			"ApplicationServices.framework",
			"QuartzCore.framework",
			"OpenGL.framework",
			"IOKit.framework",
			"glfw",
			"glew"
		}
		includedirs { 
			"src/engine/platform/renderer/gl32",
			"src/engine/common/input",
			"src/engine/platform/input/mac"
		}
		libdirs {
			"libs/glfw/lib/osx"
		}
		files {
			"src/engine/platform/renderer/gl32/**.h", 
			"src/engine/platform/renderer/gl32/**.cpp",
			"src/engine/platform/input/mac/**.h", 
			"src/engine/platform/input/mac/**.cpp"
		}

	-- 
	-- LINUX
	--
	configuration "linux"
		buildoptions ""
		linkoptions  ""
		defines     { "PLATFORM_LINUX" }
		links {
			"GLEW",
			"glfw",
			"GLU"
		}
		includedirs { 
			"src/engine/platform/renderer/gl32",
			"src/engine/common/input",
			"src/engine/platform/input/linux"
		}
		libdirs { }
		files {
			"src/engine/platform/renderer/gl32/**.h", 
			"src/engine/platform/renderer/gl32/**.cpp",
			"src/engine/platform/input/linux/**.h", 
			"src/engine/platform/input/linux/**.cpp"
		}


--
-- A more thorough cleanup.
--

if _ACTION == "clean" then
	os.rmdir("build")
end