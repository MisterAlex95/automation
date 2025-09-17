#ifndef MAP_H
#define MAP_H

#define MAP_WIDTH 10
#define MAP_HEIGHT 10

#define BG_EMPTY 0
#define BG_CONVEYOR_BELT_RIGHT 1
#define BG_CONVEYOR_BELT_DOWN 2
#define BG_CONVEYOR_BELT_LEFT 3
#define BG_CONVEYOR_BELT_UP 4
#define BG_MINER 5
#define BG_MINE 6

#define SPRITE_VRAM_INDEX_TOTAL 7

extern const unsigned char mapTiles[];
extern unsigned char mapBackground[];

#endif // MAP_H
