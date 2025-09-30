#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <gb/gb.h>
#include "game.h"

void ui_draw_hud(void);
void ui_draw_timer(void);
void ui_draw_nbr_active_items(void);
void ui_cursor_position(void);
void ui_draw_item_x_info(UBYTE x);
void ui_draw_miner_x_info(UBYTE x);
void ui_draw_tile_info_under_cursor(void);
void ui_draw_camera_debug(void);

#endif // UI_MANAGER_H