#include "scene.h"

static Scene *current_scene = 0;

void scene_set(Scene *new_scene)
{
    if (current_scene && current_scene->unload)
    {
        current_scene->unload();
    }

    current_scene = new_scene;
    if (current_scene && current_scene->load)
    {
        current_scene->load();
    }
}

Scene *scene_current(void)
{
    return current_scene;
}

void scene_update(void)
{
    if (current_scene && current_scene->update)
    {
        current_scene->update();
    }
}
