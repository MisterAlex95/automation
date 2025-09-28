#ifndef CONVEYOR_SYSTEM_H
#define CONVEYOR_SYSTEM_H

#include <gb/gb.h>
#include "game.h"

// Conveyor belt system
void conveyor_update_all_items(void);
void conveyor_move_item(item_t *item);

#endif // CONVEYOR_SYSTEM_H
