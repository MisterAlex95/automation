#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <gb/gb.h>

void viewport_init(void);
void viewport_rebuild(void);
// Scroll the on-screen cache by one tile step (falls back to full rebuild if needed)
void viewport_scroll(INT8 dtx, INT8 dty);
void viewport_patch_tile(UBYTE world_tx, UBYTE world_ty);
void viewport_restore_screen_rect(UBYTE sx, UBYTE sy, UBYTE w, UBYTE h);

#endif // VIEWPORT_H
