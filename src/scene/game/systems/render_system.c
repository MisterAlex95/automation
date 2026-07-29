#include "render_system.h"
#include "graphics.h"
#include "camera.h"
#include "constants.h"
#include <gb/hardware.h>

void render_display_items(void)
{
    UINT8 sprite_ids[MAX_ITEMS];
    UINT8 x_positions[MAX_ITEMS];
    UINT8 y_positions[MAX_ITEMS];
    UINT8 count = 0;

    UBYTE *activeItemsIds = game_get_active_items();

    for (UBYTE i = 0; activeItemsIds[i] < 0xFF; i++)
    {
        item_t *item = &game.items[activeItemsIds[i]];
        if (item->type == ITEM_TYPE_NONE)
            continue;

        INT16 sx = (INT16)world_to_screen_x(item->world_x) + (INT16)DEVICE_SPRITE_PX_OFFSET_X;
        INT16 sy = (INT16)world_to_screen_y(item->world_y) + (INT16)DEVICE_SPRITE_PX_OFFSET_Y;

        if (sx < 0 || sy < 0 || sx > (INT16)(SCREEN_WIDTH + 8) || sy > (INT16)(SCREEN_HEIGHT + 16))
        {
            graphics_hide_sprite(item->sprite_id);
            continue;
        }

        sprite_ids[count] = item->sprite_id;
        x_positions[count] = (UINT8)sx;
        y_positions[count] = (UINT8)sy;
        count++;
    }
    graphics_batch_move_sprites(sprite_ids, x_positions, y_positions, count);
}

void render_update_item_positions(void)
{
    render_display_items();
}
