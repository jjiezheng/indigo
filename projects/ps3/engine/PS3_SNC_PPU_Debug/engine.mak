########################################################
# PS3 PPU Makefile generated for GNU Make by ProDG VSI #
########################################################

.SILENT:

unexport MAKEFLAGS
unexport MFLAGS

OUTDIR = PS3_SNC_PPU_Debug
INTDIR = PS3_SNC_PPU_Debug

LIBS=\

WLIBS=\

AS=ppu-lv2-gcc
AS_FLAGS=\
	-DSN_TARGET_PS3\
	-D_DEBUG\
	-D__SNC__\
	-D__CELL_ASSERT__\
	-I../../../src/engine\
	-I../../../libs\
	-I../../../libs/assimp/include\
	-I../../../libs/freeimage\
	-I.\
	-c\
	-D__GCC__\
	-g\

CC=ps3ppusnc
CC_FLAGS=\
	-DSN_TARGET_PS3\
	-D_DEBUG\
	-D__SNC__\
	-D__CELL_ASSERT__\
	-I../../../src/engine\
	-I../../../libs\
	-I../../../libs/assimp/include\
	-I../../../libs/freeimage\
	-I.\
	-c\
	-Xmserrors\
	-Xdepmode=1\
	-MMD\
	-g\
	-Xc+=exceptions\

CXX=ps3ppusnc
CXX_FLAGS=\
	-DSN_TARGET_PS3\
	-D_DEBUG\
	-D__SNC__\
	-D__CELL_ASSERT__\
	-I../../../src/engine\
	-I../../../libs\
	-I../../../libs/assimp/include\
	-I../../../libs/freeimage\
	-I.\
	-c\
	-Xmserrors\
	-Xdepmode=1\
	-MMD\
	-g\
	-Xc+=exceptions\

AR=ps3snarl

OBJS=\
	"PS3_SNC_PPU_Debug/GraphicsInterface.obj"\
	"PS3_SNC_PPU_Debug/Clock.obj"\
	"PS3_SNC_PPU_Debug/String.obj"\
	"PS3_SNC_PPU_Debug/Angles.obj"\
	"PS3_SNC_PPU_Debug/Interpolation.obj"\
	"PS3_SNC_PPU_Debug/Matrix3x3.obj"\
	"PS3_SNC_PPU_Debug/IGraphicsInterface.obj"\
	"PS3_SNC_PPU_Debug/Random.obj"\
	"PS3_SNC_PPU_Debug/Vector2.obj"\
	"PS3_SNC_PPU_Debug/Vector3.obj"\
	"PS3_SNC_PPU_Debug/Vector4.obj"\
	"PS3_SNC_PPU_Debug/PS3GCMGraphicsInterface.obj"\
	"PS3_SNC_PPU_Debug/DeferredFXAAPass.obj"\
	"PS3_SNC_PPU_Debug/DeferredGeometryPass.obj"\
	"PS3_SNC_PPU_Debug/DeferredInitRenderStage.obj"\
	"PS3_SNC_PPU_Debug/DeferredLightingRenderStage.obj"\
	"PS3_SNC_PPU_Debug/DeferredPointLightsPass.obj"\
	"PS3_SNC_PPU_Debug/DeferredPostProcessingStage.obj"\
	"PS3_SNC_PPU_Debug/DeferredPresentPass.obj"\
	"PS3_SNC_PPU_Debug/DeferredPresentStage.obj"\
	"PS3_SNC_PPU_Debug/DeferredShadowPass.obj"\
	"PS3_SNC_PPU_Debug/DeferredSkyBoxPass.obj"\
	"PS3_SNC_PPU_Debug/DeferredSkyRenderStage.obj"\
	"PS3_SNC_PPU_Debug/DeferredSpotLightsPass.obj"\
	"PS3_SNC_PPU_Debug/DeferredSSAOPass.obj"\
	"PS3_SNC_PPU_Debug/DeferredClearBuffersPass.obj"\
	"PS3_SNC_PPU_Debug/DeferredCompositionPass.obj"\
	"PS3_SNC_PPU_Debug/DeferredDirectionalLightsPass.obj"\
	"PS3_SNC_PPU_Debug/DeferredFullScreenBlurPass.obj"\
	"PS3_SNC_PPU_Debug/Renderer3dDeferred.obj"\
	"PS3_SNC_PPU_Debug/IEffect.obj"\
	"PS3_SNC_PPU_Debug/Color3.obj"\
	"PS3_SNC_PPU_Debug/Color4.obj"\
	"PS3_SNC_PPU_Debug/Geometry.obj"\
	"PS3_SNC_PPU_Debug/Log.obj"\
	"PS3_SNC_PPU_Debug/Material.obj"\
	"PS3_SNC_PPU_Debug/SkyDome.obj"\
	"PS3_SNC_PPU_Debug/GaussianBlur.obj"\
	"PS3_SNC_PPU_Debug/AverageBlur.obj"\
	"PS3_SNC_PPU_Debug/PointLight.obj"\
	"PS3_SNC_PPU_Debug/SpotLight.obj"\
	"PS3_SNC_PPU_Debug/EffectCache.obj"\
	"PS3_SNC_PPU_Debug/Mesh.obj"\
	"PS3_SNC_PPU_Debug/Model.obj"\
	"PS3_SNC_PPU_Debug/Path.obj"\
	"PS3_SNC_PPU_Debug/WorldLoader.obj"\
	"PS3_SNC_PPU_Debug/Matrix4x4.obj"\
	"PS3_SNC_PPU_Debug/Texture.obj"\
	"PS3_SNC_PPU_Debug/HeightMap.obj"\
	"PS3_SNC_PPU_Debug/Camera.obj"\
	"PS3_SNC_PPU_Debug/PS3CGMCGEffect.obj"\

CST_OBJS=\

CST_OUTS=\

CUSTOM: $(CST_OUTS) $(CST_OBJS)

COMPILE: $(OBJS)

"PS3_SNC_PPU_Debug/GraphicsInterface.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/GraphicsInterface.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/GraphicsInterface.cpp" -o $@

"PS3_SNC_PPU_Debug/Clock.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/core/Clock.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/core/Clock.cpp" -o $@

"PS3_SNC_PPU_Debug/String.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/core/String.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/core/String.cpp" -o $@

"PS3_SNC_PPU_Debug/Angles.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/maths/Angles.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/maths/Angles.cpp" -o $@

"PS3_SNC_PPU_Debug/Interpolation.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/maths/Interpolation.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/maths/Interpolation.cpp" -o $@

"PS3_SNC_PPU_Debug/Matrix3x3.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/maths/Matrix3x3.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/maths/Matrix3x3.cpp" -o $@

"PS3_SNC_PPU_Debug/IGraphicsInterface.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/IGraphicsInterface.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/IGraphicsInterface.cpp" -o $@

"PS3_SNC_PPU_Debug/Random.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/maths/Random.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/maths/Random.cpp" -o $@

"PS3_SNC_PPU_Debug/Vector2.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/maths/Vector2.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/maths/Vector2.cpp" -o $@

"PS3_SNC_PPU_Debug/Vector3.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/maths/Vector3.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/maths/Vector3.cpp" -o $@

"PS3_SNC_PPU_Debug/Vector4.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/maths/Vector4.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/maths/Vector4.cpp" -o $@

"PS3_SNC_PPU_Debug/PS3GCMGraphicsInterface.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/PS3GCMGraphicsInterface.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/PS3GCMGraphicsInterface.cpp" -o $@

"PS3_SNC_PPU_Debug/DeferredFXAAPass.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/DeferredFXAAPass.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/DeferredFXAAPass.cpp" -o $@

"PS3_SNC_PPU_Debug/DeferredGeometryPass.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/DeferredGeometryPass.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/DeferredGeometryPass.cpp" -o $@

"PS3_SNC_PPU_Debug/DeferredInitRenderStage.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/DeferredInitRenderStage.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/DeferredInitRenderStage.cpp" -o $@

"PS3_SNC_PPU_Debug/DeferredLightingRenderStage.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/DeferredLightingRenderStage.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/DeferredLightingRenderStage.cpp" -o $@

"PS3_SNC_PPU_Debug/DeferredPointLightsPass.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/DeferredPointLightsPass.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/DeferredPointLightsPass.cpp" -o $@

"PS3_SNC_PPU_Debug/DeferredPostProcessingStage.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/DeferredPostProcessingStage.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/DeferredPostProcessingStage.cpp" -o $@

"PS3_SNC_PPU_Debug/DeferredPresentPass.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/DeferredPresentPass.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/DeferredPresentPass.cpp" -o $@

"PS3_SNC_PPU_Debug/DeferredPresentStage.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/DeferredPresentStage.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/DeferredPresentStage.cpp" -o $@

"PS3_SNC_PPU_Debug/DeferredShadowPass.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/DeferredShadowPass.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/DeferredShadowPass.cpp" -o $@

"PS3_SNC_PPU_Debug/DeferredSkyBoxPass.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/DeferredSkyBoxPass.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/DeferredSkyBoxPass.cpp" -o $@

"PS3_SNC_PPU_Debug/DeferredSkyRenderStage.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/DeferredSkyRenderStage.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/DeferredSkyRenderStage.cpp" -o $@

"PS3_SNC_PPU_Debug/DeferredSpotLightsPass.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/DeferredSpotLightsPass.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/DeferredSpotLightsPass.cpp" -o $@

"PS3_SNC_PPU_Debug/DeferredSSAOPass.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/DeferredSSAOPass.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/DeferredSSAOPass.cpp" -o $@

"PS3_SNC_PPU_Debug/DeferredClearBuffersPass.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/DeferredClearBuffersPass.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/DeferredClearBuffersPass.cpp" -o $@

"PS3_SNC_PPU_Debug/DeferredCompositionPass.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/DeferredCompositionPass.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/DeferredCompositionPass.cpp" -o $@

"PS3_SNC_PPU_Debug/DeferredDirectionalLightsPass.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/DeferredDirectionalLightsPass.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/DeferredDirectionalLightsPass.cpp" -o $@

"PS3_SNC_PPU_Debug/DeferredFullScreenBlurPass.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/DeferredFullScreenBlurPass.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/DeferredFullScreenBlurPass.cpp" -o $@

"PS3_SNC_PPU_Debug/Renderer3dDeferred.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/Renderer3dDeferred.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/Renderer3dDeferred.cpp" -o $@

"PS3_SNC_PPU_Debug/IEffect.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/IEffect.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/IEffect.cpp" -o $@

"PS3_SNC_PPU_Debug/Color3.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/Color3.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/Color3.cpp" -o $@

"PS3_SNC_PPU_Debug/Color4.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/Color4.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/Color4.cpp" -o $@

"PS3_SNC_PPU_Debug/Geometry.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/Geometry.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/Geometry.cpp" -o $@

"PS3_SNC_PPU_Debug/Log.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/io/Log.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/io/Log.cpp" -o $@

"PS3_SNC_PPU_Debug/Material.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/Material.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/Material.cpp" -o $@

"PS3_SNC_PPU_Debug/SkyDome.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/SkyDome.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/SkyDome.cpp" -o $@

"PS3_SNC_PPU_Debug/GaussianBlur.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/GaussianBlur.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/GaussianBlur.cpp" -o $@

"PS3_SNC_PPU_Debug/AverageBlur.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/AverageBlur.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/AverageBlur.cpp" -o $@

"PS3_SNC_PPU_Debug/PointLight.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/PointLight.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/PointLight.cpp" -o $@

"PS3_SNC_PPU_Debug/SpotLight.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/SpotLight.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/SpotLight.cpp" -o $@

"PS3_SNC_PPU_Debug/EffectCache.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/EffectCache.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/EffectCache.cpp" -o $@

"PS3_SNC_PPU_Debug/Mesh.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/Mesh.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/Mesh.cpp" -o $@

"PS3_SNC_PPU_Debug/Model.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/Model.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/Model.cpp" -o $@

"PS3_SNC_PPU_Debug/Path.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/io/Path.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/io/Path.cpp" -o $@

"PS3_SNC_PPU_Debug/WorldLoader.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/WorldLoader.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/WorldLoader.cpp" -o $@

"PS3_SNC_PPU_Debug/Matrix4x4.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/maths/Matrix4x4.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/maths/Matrix4x4.cpp" -o $@

"PS3_SNC_PPU_Debug/Texture.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/Texture.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/Texture.cpp" -o $@

"PS3_SNC_PPU_Debug/HeightMap.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/HeightMap.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/HeightMap.cpp" -o $@

"PS3_SNC_PPU_Debug/Camera.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/Camera.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/Camera.cpp" -o $@

"PS3_SNC_PPU_Debug/PS3CGMCGEffect.obj":
	@echo ProDG Compiling "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/PS3CGMCGEffect.cpp"
	$(CXX) $(CXX_FLAGS) "c:/cygwin/home/GBkosteni/Development/game/src/engine/renderer/PS3CGMCGEffect.cpp" -o $@

LIB: "PS3_SNC_PPU_Debug/engine.lib"

"PS3_SNC_PPU_Debug/engine.lib" : $(CST_OBJS) $(OBJS)
	@echo ProDG Creating Library $@
	$(AR) -M <"$(INTDIR)/engine_lib.txt"

