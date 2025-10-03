#ifndef CHUNK_SYSTEM_H
#define CHUNK_SYSTEM_H

#include "../../../constants.h"
#include <gb/gb.h>

typedef struct {
  UBYTE loaded;
  UBYTE dirty;
  UBYTE chunk_x, chunk_y;
  UBYTE tiles[CHUNK_SIZE][CHUNK_SIZE];
} chunk_t;

typedef struct {
  UBYTE chunk_id;
  UBYTE loaded;
  UBYTE dirty;
  chunk_t data;
} cached_chunk_t;

void chunk_system_init(void);
void chunk_system_update(void);

chunk_t *chunk_get_at_position(UBYTE world_x, UBYTE world_y);

void chunk_load(UBYTE chunk_x, UBYTE chunk_y);
void chunk_unload(UBYTE chunk_x, UBYTE chunk_y);

UBYTE chunk_get_id(UBYTE world_x, UBYTE world_y);
UBYTE chunk_get_local_x(UBYTE world_x);
UBYTE chunk_get_local_y(UBYTE world_y);

cached_chunk_t *chunk_find_by_id(UBYTE chunk_id);
void chunk_load_from_sram(UBYTE chunk_id);
void chunk_save_to_sram(UBYTE chunk_id);
UINT16 chunk_get_sram_address(UBYTE chunk_id);
void chunk_unload_oldest(void);

#endif // CHUNK_SYSTEM_H