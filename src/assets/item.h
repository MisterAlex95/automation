#ifndef ITEM_H
#define ITEM_H

#include "engine/vram_layout.h"

#define ITEMS_VRAM_INDEX_TOTAL 2

#define ITEM_INGOT_TILE (TILE_ITEMS_START + 0)
#define ITEM_ORE_TILE (TILE_ITEMS_START + 1)

extern const unsigned char itemsTiles[];

#endif // ITEM_H
