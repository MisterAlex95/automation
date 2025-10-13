#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <gb/gb.h>
#include "vram_layout.h"

// Memory management for Game Boy
// Handles VRAM allocation, SRAM operations, and memory optimization

// VRAM Management
typedef struct {
    UINT8 start_index;
    UINT8 count;
    UINT8 used;
} vram_block_t;

// Memory pool for efficient allocation
typedef struct {
    vram_block_t blocks[16];
    UINT8 total_blocks;
    UINT8 free_blocks;
} vram_pool_t;

// VRAM allocation functions
UINT8 memory_allocate_vram_tiles(UINT8 tile_count);
void memory_free_vram_tiles(UINT8 start_index, UINT8 count);
void memory_init_vram_pool(void);

// SRAM operations (if needed for save data)
void memory_save_to_sram(const void* data, UINT16 size, UINT16 offset);
void memory_load_from_sram(void* data, UINT16 size, UINT16 offset);

// Memory utilities
void memory_clear_vram_range(UINT8 start_index, UINT8 count);
void memory_copy_vram_tiles(UINT8 src_index, UINT8 dest_index, UINT8 count);

// Chunk management for world data
typedef struct {
    UINT8 x, y;
    UINT8 data[16][16]; // 16x16 chunk data
    UBYTE dirty; // Flag for unsaved changes
} chunk_t;

// Chunk system functions
chunk_t* chunk_get(UINT8 chunk_x, UINT8 chunk_y);
void chunk_set_tile(UINT8 chunk_x, UINT8 chunk_y, UINT8 local_x, UINT8 local_y, UINT8 tile_id);
UINT8 chunk_get_tile(UINT8 chunk_x, UINT8 chunk_y, UINT8 local_x, UINT8 local_y);
void chunk_mark_dirty(UINT8 chunk_x, UINT8 chunk_y);
void chunk_clear_dirty(UINT8 chunk_x, UINT8 chunk_y);
void chunk_init_system(void);

#endif // MEMORY_MANAGER_H