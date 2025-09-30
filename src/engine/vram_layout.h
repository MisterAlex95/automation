#ifndef VRAM_LAYOUT_H
#define VRAM_LAYOUT_H

// --- HUD + FONT (0–127) - Console system uses this range
#define TILE_FONT_START      0
#define TILE_FONT_COUNT      128

// --- BG Factory (128–191)
#define TILE_FACTORY_START   128
#define TILE_FACTORY_COUNT   64

// --- Items / Resources (192–223)
#define TILE_ITEMS_START     192
#define TILE_ITEMS_COUNT     32

// --- UI Elements (224–255)
#define TILE_UI_START        224
#define TILE_UI_COUNT        32

// --- Tilemaps
#define MAP_BG0_ADDR         0x9800  // Tilemap 0 (32x32)
#define MAP_BG1_ADDR         0x9C00  // Tilemap 1 (32x32)

#endif // VRAM_LAYOUT_H
