#ifndef MAP_H
#define MAP_H

#include "engine/vram_layout.h"

#define MAP_WIDTH 10
#define MAP_HEIGHT 10

#define BG_EMPTY (TILE_FACTORY_START + 0)
#define BG_CONVEYOR_BELT_RIGHT (TILE_FACTORY_START + 1)
#define BG_CONVEYOR_BELT_DOWN (TILE_FACTORY_START + 2)
#define BG_CONVEYOR_BELT_LEFT (TILE_FACTORY_START + 3)
#define BG_CONVEYOR_BELT_UP (TILE_FACTORY_START + 4)
#define BG_MINER (TILE_FACTORY_START + 5)
#define BG_MINE (TILE_FACTORY_START + 6)
#define BG_CHEST (TILE_FACTORY_START + 7)
#define BG_WALL (TILE_FACTORY_START + 8)

#define SPRITE_VRAM_INDEX_TOTAL 9

extern const unsigned char mapTiles[];
extern unsigned char mapBackground[];

#endif // MAP_H
