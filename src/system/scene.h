#ifndef SCENE_H
#define SCENE_H

#include <gb/gb.h>

typedef void (*SceneLoadFunc)(void);
typedef void (*SceneUpdateFunc)(void);
typedef void (*SceneUnloadFunc)(void);
typedef void (*SceneInputHandler)(UINT8 keys, UINT8 keys_prev);

typedef struct
{
    SceneLoadFunc load;
    SceneUpdateFunc update;
    SceneUnloadFunc unload;
    SceneInputHandler handle_input;
} Scene;

void scene_set(Scene *new_scene);
Scene *scene_current(void);
void scene_update(void);

#endif
