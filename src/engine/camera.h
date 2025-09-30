#ifndef CAMERA_H
#define CAMERA_H

#include <gb/gb.h>

#define CAMERA_SPEED 1

typedef struct {
    UINT16 x;
    UINT16 y;
} camera_t;

extern camera_t camera;

void camera_init(void);
void camera_update(int dx, int dy);
UINT16 camera_get_x(void);
UINT16 camera_get_y(void);

UBYTE camera_can_move_left(void);
UBYTE camera_can_move_right(void);
UBYTE camera_can_move_up(void);
UBYTE camera_can_move_down(void);

UINT16 world_to_screen_x(UINT16 world_x);
UINT16 world_to_screen_y(UINT16 world_y);
UINT16 screen_to_world_x(UINT16 screen_x);
UINT16 screen_to_world_y(UINT16 screen_y);
UINT8 world_to_tile_x(UINT16 world_x);
UINT8 world_to_tile_y(UINT16 world_y);
UINT16 tile_to_world_x(UINT8 tile_x);
UINT16 tile_to_world_y(UINT8 tile_y);

void entity_update_screen_position(UINT16 world_x, UINT16 world_y, UBYTE sprite_id);
void entity_set_world_position(UINT16 *world_x, UINT16 *world_y, UINT8 tile_x, UINT8 tile_y);
void camera_update_all_entity_positions(void);

#endif // CAMERA_H
