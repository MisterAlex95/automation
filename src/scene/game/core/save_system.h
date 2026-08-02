#ifndef SAVE_SYSTEM_H
#define SAVE_SYSTEM_H

#include <gb/gb.h>

UBYTE save_exists(void);
void save_game(void);
void load_game(void);
void save_new_game(void);

#endif // SAVE_SYSTEM_H
