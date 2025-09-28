#ifndef CHEST_SYSTEM_H
#define CHEST_SYSTEM_H

#include <gb/gb.h>
#include "game.h"

// Chest system
void chest_update_all_items(void);
void chest_process_item(item_t *item);

#endif // CHEST_SYSTEM_H
