	solution "Game"
		configurations { "Release", "Debug" }
		location ("build")

		configuration "macosx"
			location ("build/osx")
	
	project "game"
		targetname  "Game"
		language    "C++"
		kind        "WindowedApp"
		flags       { "ExtraWarnings", "FatalWarnings" }	
		
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
			
		configuration "Debug"
			targetdir   "bin/debug"
			defines     "_DEBUG"
			flags       { "Symbols" }
			
		configuration "Release"
			targetdir   "bin/release"
			defines     "NDEBUG"
			flags       { "OptimizeSize" }

		configuration "vs*"
			defines     { "_CRT_SECURE_NO_WARNINGS" }
			
		configuration "macosx"
			buildoptions "-stdlib=libc++"
			linkoptions  "-stdlib=libc++"
			links       {
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
		os.rmdir("bin")
		os.rmdir("build")
	end