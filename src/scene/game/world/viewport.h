#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <gb/gb.h>

void viewport_init(void);
void viewport_rebuild(void);
void viewport_patch_tile(UBYTE world_tx, UBYTE world_ty);
void viewport_restore_screen_rect(UBYTE sx, UBYTE sy, UBYTE w, UBYTE h);

#endif // VIEWPORT_H
