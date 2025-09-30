#ifndef UI_H
#define UI_H

#define UI_SPRITE_CURSOR 0
#define SPRITE_VRAM_INDEX_CURSOR 0

// UI Tile definitions
#define UI_CURSOR (TILE_UI_START + 0)
#define UI_EMPTY (TILE_UI_START + 1)
#define UI_HORIZONTAL (TILE_UI_START + 2)
#define UI_ANGLE_BOTTOM_LEFT (TILE_UI_START + 3)
#define UI_ANGLE_BOTTOM_RIGHT (TILE_UI_START + 4)
#define UI_VERTICAL (TILE_UI_START + 5)
#define UI_ANGLE_TOP_RIGHT (TILE_UI_START + 6)
#define UI_ANGLE_TOP_LEFT (TILE_UI_START + 7)

#define UI_TILES_COUNT 8

extern const unsigned char UITiles[];

#endif // UI_H