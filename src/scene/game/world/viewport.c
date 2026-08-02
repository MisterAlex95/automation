#include "viewport.h"
#include "chunk_system.h"
#include "camera.h"
#include "graphics.h"
#include "constants.h"

void viewport_init(void)
{
  move_bkg(0, 0);
  viewport_rebuild();
}

void viewport_rebuild(void)
{
  UBYTE cam_tx = camera_get_tile_x();
  UBYTE cam_ty = camera_get_tile_y();

  chunk_ensure_around_camera(cam_tx, cam_ty);

  for (UBYTE sy = 0; sy < SCREEN_TILE_HEIGHT; sy++)
  {
    for (UBYTE sx = 0; sx < SCREEN_TILE_WIDTH; sx++)
    {
      UBYTE wx = cam_tx + sx;
      UBYTE wy = cam_ty + sy;
      UBYTE tile = chunk_get_tile(wx, wy);
      graphics_draw_background_at(tile, sx, sy);
    }
  }

  move_bkg(0, 0);
}

void viewport_patch_tile(UBYTE world_tx, UBYTE world_ty)
{
  UBYTE cam_tx = camera_get_tile_x();
  UBYTE cam_ty = camera_get_tile_y();

  if (world_tx < cam_tx || world_ty < cam_ty)
    return;
  if (world_tx >= cam_tx + SCREEN_TILE_WIDTH)
    return;
  if (world_ty >= cam_ty + SCREEN_TILE_HEIGHT)
    return;

  UBYTE sx = world_tx - cam_tx;
  UBYTE sy = world_ty - cam_ty;
  graphics_draw_background_at(chunk_get_tile(world_tx, world_ty), sx, sy);
}

void viewport_restore_screen_rect(UBYTE sx, UBYTE sy, UBYTE w, UBYTE h)
{
  UBYTE cam_tx = camera_get_tile_x();
  UBYTE cam_ty = camera_get_tile_y();
  UBYTE x, y;

  for (y = sy; y < sy + h && y < SCREEN_TILE_HEIGHT; y++)
  {
    for (x = sx; x < sx + w && x < SCREEN_TILE_WIDTH; x++)
    {
      graphics_draw_background_at(chunk_get_tile(cam_tx + x, cam_ty + y), x, y);
    }
  }
}
