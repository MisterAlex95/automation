#ifndef MAP_H
#define MAP_H

#define MAP_WIDTH 10
#define MAP_HEIGHT 10

#define BG_EMPTY 0
#define BG_CONVEYOR_BELT_RIGHT 1
#define BG_CONVEYOR_BELT_CORNER_RIGHT_DOWN 2
#define BG_CONVEYOR_BELT_DOWN 3
#define BG_CONVEYOR_BELT_CORNER_DOWN_LEFT 4
#define BG_CONVEYOR_BELT_LEFT 5
#define BG_CONVEYOR_BELT_CORNER_LEFT_UP 6
#define BG_CONVEYOR_BELT_UP 7
#define BG_CONVEYOR_BELT_CORNER_UP_RIGHT 8

#define SPRITE_VRAM_INDEX_TOTAL 19

extern const unsigned char mapTiles[];
extern const unsigned char mapBackground[];

#endif // MAP_H
