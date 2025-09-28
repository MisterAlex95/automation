#ifndef ITEM_SYSTEM_H
#define ITEM_SYSTEM_H

#include <gb/gb.h>
#include "game.h"

// Item management
item_t *item_spawn(UBYTE type, UINT8 x, UINT8 y, UBYTE direction);
item_t *item_get_free_slot(void);
void item_destroy(item_t *item);

// Item movement
void item_update_movement(item_t *item);

#endif // ITEM_SYSTEM_H
