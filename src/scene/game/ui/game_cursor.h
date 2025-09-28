#ifndef GAME_CURSOR_H
#define GAME_CURSOR_H

#include "game.h"
#include "graphics.h"
#include "map.h"
#include "ui.h"

void game_move_cursor(int dx, int dy);
void game_display_cursor(void);
UINT8 game_get_cursor_x(void);
UINT8 game_get_cursor_y(void);

#endif // GAME_CURSOR_H