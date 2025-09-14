#ifndef INPUT_H
#define INPUT_H

#include <gb/gb.h>
#include "scene.h"

void input_init(void);
void input_update(Scene *current_scene);

UINT8 input_get_pressed(void);
UINT8 input_get_released(void);

#endif
