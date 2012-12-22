function basedir()
	local basedir = ''

	configuration "macosx"
		basedir = "build/project/osx/" .. _ACTION

	configuration "vs*"
		basedir = "build/project/win/" .. _ACTION

	if _OPTIONS.platform ~= nil then
		basedir = "build/project/" .. _OPTIONS.platform .. '/' .. _ACTION
	end

	return basedir
end

solution "Game"
	configurations { "Release", "Debug" }

	local basedir = basedir()
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
	configuration { "ps3", "Debug" }
		buildoptions { "-g" }
		postbuildcommands { "C://usr//local//cell//host-win32//bin//make_fself ..\\..\\..\\debug\\Game.elf ..\\..\\..\\debug\\game.self" }

	configuration { "ps3", "Release" }
		buildoptions { "-O2" }
		postbuildcommands { "C://usr//local//cell//host-win32//bin//make_fself ..\\..\\..\\release\\Game.elf ..\\..\\..\\release\\game.self" }

	configuration { "ps3" }
		defines     { "SN_TARGET_PS3", "__SNC__", "__CELL_ASSERT__"}
		buildoptions { "--diag_suppress=383 --diag_suppress=613 --diag_suppress=1011 -Xc+=exceptions" }

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
		links {
			"libsn.a",
			"libm.a",	
			"libio_stub.a",
			"libfs_stub.a",
			"libgcm_cmd.a",
			"libgcm_sys_stub.a",
			"libsysmodule_stub.a",
			"libsysutil_stub.a",
			"libcgc.a"
		}

	configuration 	{ "Debug" }
		defines     "_DEBUG"
		flags       { "Symbols" }
		
	configuration 	{ "Release" }
		defines     "NDEBUG"
		flags       { "OptimizeSpeed" }

	--
	-- Windows
	--
	configuration 	{ "Debug", "vs2012" }
		targetdir   "build/win/2012/debug/"
		
	configuration 	{ "Release", "vs2012" }
		targetdir   "build/win/2012/release"

	configuration 	{ "Debug", "vs2010" }
		targetdir   "build/win/2010/debug/"
		
	configuration 	{ "Release", "vs2012" }
		targetdir   "build/win/2010/release"

	configuration 	{ "Debug", "vs2008" }
		targetdir   "build/win/2008/debug/"
		
	configuration 	{ "Release", "vs2008" }
		targetdir   "build/win/2008/release"

	configuration { "vs2012", "x32" }
		includedirs {
			"libs/d3dx/include"
		}
		libdirs {
			"libs/d3dx/lib/x32"
		}
		links {
			"d3dx9",
			"d3dx10",
			"d3dx11"
		}

	configuration { "vs*", "x32" }
		defines     { "_CRT_SECURE_NO_WARNINGS" }
		buildoptions "-wd4100"
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
		links {
			"AppKit.framework",
			"Foundation.framework", 
			"CoreServices.framework",
			"ApplicationServices.framework",
			"QuartzCore.framework",
			"OpenGL.framework",
			"IOKit.framework",
			"glfw"
		}
		includedirs { 
			"src/engine/platform/renderer/gl32"
		}
		libdirs {
			"libs/glfw/lib/osx"
		}
		files {
			"src/engine/platform/renderer/gl32/**.h", 
			"src/engine/platform/renderer/gl32/**.cpp"
		}

--
-- A more thorough cleanup.
--

if _ACTION == "clean" then
	os.rmdir("build")
end