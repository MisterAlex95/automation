#ifndef CHUNK_SYSTEM_H
#define CHUNK_SYSTEM_H

#include <gb/gb.h>
#include "constants.h"

// Payload persisted in SRAM — no runtime flags
typedef struct {
  UBYTE tiles[CHUNK_SIZE][CHUNK_SIZE];
} chunk_data_t;

#define SRAM_CHUNK_SIZE ((UINT16)sizeof(chunk_data_t))
#define SRAM_TOTAL_CHUNKS (CHUNK_COUNT_X * CHUNK_COUNT_Y)

typedef struct {
  UBYTE chunk_id;
  UBYTE loaded;
  UBYTE dirty;
  UBYTE last_used;
  chunk_data_t data;
} cached_chunk_t;

void chunk_system_init(void);
void chunk_system_update(void);
void chunk_flush_all(void);

UBYTE chunk_get_tile(UBYTE world_tx, UBYTE world_ty);
void chunk_set_tile(UBYTE world_tx, UBYTE world_ty, UBYTE tile_value);

UBYTE chunk_get_id_from_tile(UBYTE world_tx, UBYTE world_ty);
UBYTE chunk_get_local_x(UBYTE world_tx);
UBYTE chunk_get_local_y(UBYTE world_ty);

cached_chunk_t *chunk_ensure_loaded(UBYTE chunk_id);
void chunk_ensure_around_camera(UBYTE cam_tx, UBYTE cam_ty);
void chunk_save_to_sram(UBYTE chunk_id);
UINT16 chunk_get_sram_address(UBYTE chunk_id);

void world_seed_from_template(void);
UBYTE world_sram_is_valid(void);
void world_sram_write_header(void);
void world_init(UBYTE force_new);

#endif // CHUNK_SYSTEM_H
