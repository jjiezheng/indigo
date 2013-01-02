########################################################
# PS3 PPU Makefile generated for GNU Make by ProDG VSI #
########################################################

.SILENT:

unexport MAKEFLAGS
unexport MFLAGS

OUTDIR = PS3_SNC_PPU_Debug
INTDIR = PS3_SNC_PPU_Debug

LIBS=\
	c:/Users/NK/Development/game/projects/ps3/engine/PS3_SNC_PPU_Debug/engine.lib\
	libsn.a\
	libm.a\
	libio_stub.a\
	libfs_stub.a\
	libgcm_cmd.a\
	libgcm_sys_stub.a\
	libsysmodule_stub.a\
	libsysutil_stub.a\
	libcgc.a\

WLIBS=\

AS=ppu-lv2-gcc
AS_FLAGS=\
	-DSN_TARGET_PS3\
	-D_DEBUG\
	-D__SNC__\
	-D__CELL_ASSERT__\
	-I../../../src/engine\
	-I../../../libs\
	-I.\
	--diag_suppress=613\
	--diag_suppress=1011\
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
	-I.\
	--diag_suppress=613\
	--diag_suppress=1011\
	-c\
	-Xmserrors\
	-Xdepmode=1\
	-MMD\
	-g\
	-Xc+=exceptions\
	-Xquit=1\

CXX=ps3ppusnc
CXX_FLAGS=\
	-DSN_TARGET_PS3\
	-D_DEBUG\
	-D__SNC__\
	-D__CELL_ASSERT__\
	-I../../../src/engine\
	-I../../../libs\
	-I.\
	--diag_suppress=613\
	--diag_suppress=1011\
	-c\
	-Xmserrors\
	-Xdepmode=1\
	-MMD\
	-g\
	-Xc+=exceptions\
	-Xquit=1\

LD=ps3ppuld
LD_FLAGS=\
	-LC:/usr/local/cell/target/ppu/lib/PSGL/RSX/opt\
	-oformat=fself\

OBJS=\
	"PS3_SNC_PPU_Debug/App.obj"\
	"PS3_SNC_PPU_Debug/Game.obj"\
	"PS3_SNC_PPU_Debug/main.obj"\

CST_OBJS=\

CST_OUTS=\

CUSTOM: $(CST_OUTS) $(CST_OBJS)

COMPILE: $(OBJS)

"PS3_SNC_PPU_Debug/App.obj":
	@echo ProDG Compiling "c:/Users/NK/Development/game/src/game/App.cpp"
	$(CXX) $(CXX_FLAGS) "c:/Users/NK/Development/game/src/game/App.cpp" -o $@

"PS3_SNC_PPU_Debug/Game.obj":
	@echo ProDG Compiling "c:/Users/NK/Development/game/src/game/Game.cpp"
	$(CXX) $(CXX_FLAGS) "c:/Users/NK/Development/game/src/game/Game.cpp" -o $@

"PS3_SNC_PPU_Debug/main.obj":
	@echo ProDG Compiling "c:/Users/NK/Development/game/src/game/main.cpp"
	$(CXX) $(CXX_FLAGS) "c:/Users/NK/Development/game/src/game/main.cpp" -o $@

LINK: "PS3_SNC_PPU_Debug/game.ppu.self"

"PS3_SNC_PPU_Debug/game.ppu.self" : $(CST_OBJS) $(OBJS)\
	"c:/Users/NK/Development/game/projects/ps3/engine/PS3_SNC_PPU_Debug/engine.lib"
	@echo ProDG Linking $@
	$(LD) $(LD_FLAGS) --start-group $(CST_OBJS) $(OBJS) $(LIBS) --end-group -o $@

