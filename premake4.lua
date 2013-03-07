newoption {
   trigger     = "gfxapi",
   value       = "API",
   description = "Choose a particular 3D API for rendering",
   allowed = {
      { "gl",   "OpenGL Desktop (OSX/Linux/Windows)" },
      { "d3d",  "Direct3D 11 (Windows)" },
      { "gcm",  "GCM (PS3)" },
      { "gnm",  "GNM (PS4/Win64)" }
   }
}

solution "Game"
	configurations { "Release", "Debug" }
	location "build"

project "game"
	language    "C++"
	kind        "WindowedApp"
	flags       { "FatalWarnings", "NoIncrementalLink" }	
	targetdir 	"dist"
	
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

	configuration { "ps3" }
		targetextension(".elf")
		postbuildcommands { "C://usr//local//cell.420//host-win32//bin//make_fself $(OutDir)//Game.elf $(OutDir)//game.self",  }
		defines     { "SN_TARGET_PS3", "__SNC__", "__CELL_ASSERT__", "PLATFORM_PS3"}
		defines     { "RENDERER_GCM" }
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

	configuration { "x64" }
		defines     { "_CRT_SECURE_NO_WARNINGS", "_WIN32", "PLATFORM_WINDOWS" }
		includedirs { 
			"src/engine/common/renderer",
			"src/engine/common/input",
			"src/engine/platform/input/win",
			"src/engine/platform/platform/win"
		}
		files {
			"src/engine/platform/platform/win/**.h", 
			"src/engine/platform/platform/win/**.cpp",
			"src/engine/platform/input/win/**.h", 
			"src/engine/platform/input/win/**.cpp"
		}

	configuration { "x32" }
		defines     { "_CRT_SECURE_NO_WARNINGS", "_WIN32", "WIN32", "PLATFORM_WINDOWS" }
		includedirs { 
			"src/engine/common/renderer",
			"src/engine/common/input",
			"src/engine/platform/input/win",
			"src/engine/platform/platform/win"
		}
		files {
			"src/engine/platform/platform/win/**.h", 
			"src/engine/platform/platform/win/**.cpp",
			"src/engine/platform/input/win/**.h", 
			"src/engine/platform/input/win/**.cpp"
		}

	configuration { "x32", "gl" }
		defines     { "GLEW_STATIC" }
		links {
			"GLFW",
			"glew32s"
		}

	configuration { "gl" }
		defines     { "RENDERER_OPENGL" }
		includedirs { 
			"libs/glfw/include",
			"libs/glew/include",
			"src/engine/platform/renderer/gl32",
			"src/engine/platform/input/glfw"
		}
		libdirs {
			"libs/glfw/lib/win",
			"libs/glew/lib"
		}
		files {
			"src/engine/platform/input/glfw/**.h", 
			"src/engine/platform/input/glfw/**.cpp",
			"src/engine/platform/renderer/gl32/**.h", 
			"src/engine/platform/renderer/gl32/**.cpp",
		}

	configuration { "d3d" }
		defines     { "RENDERER_D3D" }
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
			"C:\\Program Files (x86)\\Microsoft DirectX SDK (June 2010)\\Include",
			"src/engine/platform/renderer/dx11",
		}
		libdirs {
			"C:\\Program Files (x86)\\Microsoft DirectX SDK (June 2010)\\Lib\\x32"
		}
		files {
			"src/engine/platform/renderer/dx11/**.h", 
			"src/engine/platform/renderer/dx11/**.cpp",
		}

	configuration { "gnm" }
		defines     { "RENDERER_GNM" }
		links {
			"libSceGnmx-debug"
		}
		local SCE_ORBIS_SDK_DIR = os.getenv("SCE_ORBIS_SDK_DIR")
		
		SCE_ORBIS_SDK_DIR = SCE_ORBIS_SDK_DIR and SCE_ORBIS_SDK_DIR or ''	
		includedirs { 
			"src/engine/platform/renderer/gnm",
			SCE_ORBIS_SDK_DIR .. "/target/include_common"
		}
		libdirs {
			SCE_ORBIS_SDK_DIR .. "/host_tools/lib"
		}
		files {
			"src/engine/platform/renderer/gnm/**.h", 
			"src/engine/platform/renderer/gnm/**.cpp",
		}

	configuration "macosx"
		buildoptions "-stdlib=libc++"
		linkoptions  "-stdlib=libc++"
		defines     { "PLATFORM_MAC" }
		defines     { "RENDERER_OPENGL" }
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

	configuration "linux"
		buildoptions ""
		linkoptions  ""
		defines     { "PLATFORM_LINUX" }
		defines     { "RENDERER_OPENGL" }
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
