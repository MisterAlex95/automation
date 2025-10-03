# GBDK Makefile for Game Boy development
# Based on GBDK-2020

# ============================================================================
# PROJECT CONFIGURATION
# ============================================================================

PROJECT = gameboy_project
BUILD_DIR = build
SRC_DIR = src
SRC_ENGINE_DIR = src/engine
SRC_SYSTEM_DIR = src/system
SRC_SCENE_DIR = src/scene
SRC_SCENE_GAME = src/scene/game
SRC_SCENE_MENU = src/scene/menu
SRC_UTILS_DIR = src/utils
SRC_ASSETS_DIR = src/assets

# ============================================================================
# OS DETECTION AND GBDK CONFIGURATION
# ============================================================================

# Detect operating system
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    # Linux configuration
    GBDK_HOME = /home/alex/gbdk
    OPEN_CMD = /snap/bin/sameboy
else ifeq ($(UNAME_S),Darwin)
    # macOS configuration
    GBDK_HOME = /Users/alex/gbdk
    OPEN_CMD = open
else
    # Default to Linux if unknown
    GBDK_HOME = /home/alex/gbdk
    OPEN_CMD = xdg-open
endif

CC = $(GBDK_HOME)/bin/lcc
AS = $(GBDK_HOME)/bin/lcc
OBJCOPY = $(GBDK_HOME)/bin/objcopy

# ============================================================================
# SOURCE FILES
# ============================================================================

SOURCES = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/game.c \
	$(SRC_SYSTEM_DIR)/scene.c \
	$(SRC_ENGINE_DIR)/camera.c \
	$(SRC_ENGINE_DIR)/graphics.c \
	$(SRC_ENGINE_DIR)/timer.c \
	$(SRC_ENGINE_DIR)/input.c \
	$(SRC_SCENE_MENU)/scene_menu.c \
	$(SRC_SCENE_GAME)/core/game_logic.c \
	$(SRC_SCENE_GAME)/core/sram_system.c \
	$(SRC_SCENE_GAME)/ui/game_cursor.c \
	$(SRC_SCENE_GAME)/ui/cursor_camera_controller.c \
	$(SRC_SCENE_GAME)/ui/input_handler.c \
	$(SRC_SCENE_GAME)/core/scene_game.c \
	$(SRC_SCENE_GAME)/ui/ui_manager.c \
	$(SRC_SCENE_GAME)/world/game_map.c \
	$(SRC_SCENE_GAME)/world/chunk_system.c \
	$(SRC_SCENE_GAME)/ui/menu/menu.c \
	$(SRC_SCENE_GAME)/entities/item_system.c \
	$(SRC_SCENE_GAME)/entities/miner_system.c \
	$(SRC_SCENE_GAME)/systems/conveyor_system.c \
	$(SRC_SCENE_GAME)/systems/chest_system.c \
	$(SRC_SCENE_GAME)/systems/render_system.c \
	$(SRC_ASSETS_DIR)/map.c \
	$(SRC_ASSETS_DIR)/item.c \
	$(SRC_ASSETS_DIR)/ui.c \
	$(SRC_UTILS_DIR)/math.c

# ============================================================================
# COMPILER FLAGS
# ============================================================================

// 110: unused parameter
// 158: unused variable
WARNING_FLAGS = -Wf--disable-warning=110 -Wf--disable-warning=158

CFLAGS = -Wa-l -Wl-m -Wl-j -I$(GBDK_HOME)/include -I$(SRC_DIR) \
	-I$(SRC_ENGINE_DIR) \
	-I$(SRC_SYSTEM_DIR) \
	-I$(SRC_SCENE_GAME) \
	-I$(SRC_SCENE_GAME)/menu \
	-I$(SRC_SCENE_MENU) \
	-I$(SRC_ASSETS_DIR) \
	-I$(SRC_UTILS_DIR) \
	$(WARNING_FLAGS)


# MBC5 + RAM + BATTERY
CARTRIDGE_TYPE = -Wl-yt5 -Wl-ya4

# ============================================================================
# TARGETS
# ============================================================================

# Default target
all: $(BUILD_DIR)/$(PROJECT).gb

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compile the ROM
$(BUILD_DIR)/$(PROJECT).gb: $(SOURCES) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CARTRIDGE_TYPE) -o $@ $(SOURCES)

# Clean build files
clean:
	rm -rf $(BUILD_DIR)

# Rebuild (clean + make)
re: clean all

# Run in emulator (requires an emulator like SameBoy, BGB, or VBA)
run: $(BUILD_DIR)/$(PROJECT).gb
	${OPEN_CMD} $(BUILD_DIR)/$(PROJECT).gb

# Debug build with additional symbols
debug: CFLAGS += -Wl-y
debug: $(BUILD_DIR)/$(PROJECT).gb

.PHONY: all clean re run debug
