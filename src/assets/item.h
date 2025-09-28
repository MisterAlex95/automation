#ifndef ITEM_H
#define ITEM_H

#include "engine/vram_layout.h"

#define ITEMS_VRAM_INDEX_TOTAL 1

#define ITEM_TYPE_NONE 0
#define ITEM_TYPE_INGOT 1

#define ITEM_INGOT_TILE (TILE_ITEMS_START + 0)

extern const unsigned char itemsTiles[];

#endif // ITEM_H
