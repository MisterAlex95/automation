#include "ui_manager.h"
#include "graphics.h"
#include "game.h"
#include "constants.h"
#include "camera.h"
#include "menu/menu.h"
#include <stdio.h>

#define HUD_WIN_X 7
#define HUD_WIN_Y 136

static UBYTE hud_dirty = 1;
static UINT16 hud_last_score = 0xFFFF;
static UBYTE hud_last_cx = 0xFF;
static UBYTE hud_last_cy = 0xFF;
static UBYTE overlay_mode = 0; // 0=hud, 1=pause, 2=win

static void ui_show_hud_window(void)
{
    graphics_fill_window_rect(0, 0, 20, 2, 0);
    graphics_move_window(HUD_WIN_X, HUD_WIN_Y);
    graphics_show_window();
    overlay_mode = 0;
    hud_dirty = 1;
}

static void ui_draw_hud_contents(void)
{
    char buf[20];
    UBYTE wx = cursor_screen_to_world_x(game.cursor_x);
    UBYTE wy = cursor_screen_to_world_y(game.cursor_y);

    sprintf(buf, "(%u,%u)  ", (unsigned)wx, (unsigned)wy);
    graphics_draw_window_text(0, 0, buf);

    sprintf(buf, "S:%u  ", (unsigned)game.score);
    graphics_draw_window_text(10, 0, buf);

    hud_last_score = game.score;
    hud_last_cx = wx;
    hud_last_cy = wy;
    hud_dirty = 0;
}

void ui_draw_hud(void)
{
    static UBYTE was_menu = 0;

    if (menu_is_open())
    {
        was_menu = 1;
        return;
    }

    if (was_menu)
    {
        was_menu = 0;
        ui_show_hud_window();
    }

    if (game.won)
    {
        if (overlay_mode != 2)
        {
            graphics_fill_window_rect(0, 0, 20, 6, 0);
            graphics_move_window(HUD_WIN_X, 64);
            graphics_show_window();
            graphics_draw_window_text(5, 1, "YOU WIN!");
            graphics_draw_window_text(3, 3, "START:Menu");
            overlay_mode = 2;
        }
        return;
    }

    if (game.paused)
    {
        if (overlay_mode != 1)
        {
            graphics_fill_window_rect(0, 0, 20, 4, 0);
            graphics_move_window(HUD_WIN_X, 72);
            graphics_show_window();
            graphics_draw_window_text(6, 1, "PAUSED");
            overlay_mode = 1;
        }
        return;
    }

    if (overlay_mode != 0)
        ui_show_hud_window();
    else
    {
        graphics_move_window(HUD_WIN_X, HUD_WIN_Y);
        graphics_show_window();
    }

    {
        UBYTE wx = cursor_screen_to_world_x(game.cursor_x);
        UBYTE wy = cursor_screen_to_world_y(game.cursor_y);
        if (hud_dirty || game.score != hud_last_score || wx != hud_last_cx || wy != hud_last_cy)
            ui_draw_hud_contents();
    }
}
