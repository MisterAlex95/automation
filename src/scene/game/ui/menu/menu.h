#ifndef MENU_H
#define MENU_H

#include "constants.h"
#include <gb/gb.h>

void menu_show_tile_selection(void);
void menu_show_orientation_selection(void);
void menu_clear(void);
void menu_close(void);
UBYTE menu_is_open(void);
void menu_handle_input(UINT8 keys, UINT8 keys_prev);

#endif // MENU_H
