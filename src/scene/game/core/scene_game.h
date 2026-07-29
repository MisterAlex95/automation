#ifndef SCENE_GAME_H
#define SCENE_GAME_H

#include "scene.h"
#include <gb/gb.h>

extern Scene scene_game;

void display_items(void);
void scene_game_set_load_mode(UBYTE from_save);

#endif // SCENE_GAME_H
