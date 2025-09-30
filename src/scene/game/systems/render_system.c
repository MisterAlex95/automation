#include "render_system.h"
#include "graphics.h"
#include "camera.h"

void render_display_items(void)
{
    UINT8 sprite_ids[MAX_ITEMS] = {0};
    UINT8 x_positions[MAX_ITEMS] = {0};
    UINT8 y_positions[MAX_ITEMS] = {0};
    UINT8 count = 0;

    UBYTE *activeItemsIds = game_get_active_items();

    for (UBYTE i = 0; activeItemsIds[i] < 0xFF; i++)
    {
        item_t *item = &game.items[activeItemsIds[i]];
        if (item->type != ITEM_TYPE_NONE)
        {
            sprite_ids[count] = item->sprite_id;
            x_positions[count] = world_to_screen_x(item->world_x);
            y_positions[count] = world_to_screen_y(item->world_y);
            count++;
        }
    }
    graphics_batch_move_sprites(sprite_ids, x_positions, y_positions, count);
}

void render_update_item_positions(void)
{
    render_display_items();
}
