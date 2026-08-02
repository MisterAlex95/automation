#include "viewport.h"
#include "chunk_system.h"
#include "camera.h"
#include "graphics.h"
#include "constants.h"

// WRAM shadow of the visible BG — enables cheap scrolls without reading VRAM
static UBYTE screen_buf[SCREEN_TILE_HEIGHT][SCREEN_TILE_WIDTH];

static void viewport_blit_row(UBYTE sy)
{
  graphics_draw_background_partial(screen_buf[sy], SCREEN_TILE_WIDTH, 1, 0, sy);
}

static void viewport_blit_all(void)
{
  for (UBYTE sy = 0; sy < SCREEN_TILE_HEIGHT; sy++)
    viewport_blit_row(sy);
}

static void viewport_fill_row_from_world(UBYTE sy, UBYTE cam_tx, UBYTE cam_ty)
{
  UBYTE wy = cam_ty + sy;
  for (UBYTE sx = 0; sx < SCREEN_TILE_WIDTH; sx++)
    screen_buf[sy][sx] = chunk_peek_tile(cam_tx + sx, wy);
}

static void viewport_fill_col_from_world(UBYTE sx, UBYTE cam_tx, UBYTE cam_ty)
{
  UBYTE wx = cam_tx + sx;
  for (UBYTE sy = 0; sy < SCREEN_TILE_HEIGHT; sy++)
    screen_buf[sy][sx] = chunk_peek_tile(wx, cam_ty + sy);
}

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
    viewport_fill_row_from_world(sy, cam_tx, cam_ty);

  viewport_blit_all();
  move_bkg(0, 0);
}

void viewport_scroll(INT8 dtx, INT8 dty)
{
  // Only pure single-tile steps are incremental; diagonals / jumps rebuild
  if ((dtx != 0 && dty != 0) || dtx < -1 || dtx > 1 || dty < -1 || dty > 1)
  {
    viewport_rebuild();
    return;
  }
  if (dtx == 0 && dty == 0)
    return;

  UBYTE cam_tx = camera_get_tile_x();
  UBYTE cam_ty = camera_get_tile_y();
  chunk_ensure_around_camera(cam_tx, cam_ty);

  if (dtx == 1)
  {
    for (UBYTE sy = 0; sy < SCREEN_TILE_HEIGHT; sy++)
    {
      for (UBYTE sx = 0; sx < SCREEN_TILE_WIDTH - 1; sx++)
        screen_buf[sy][sx] = screen_buf[sy][sx + 1];
    }
    viewport_fill_col_from_world(SCREEN_TILE_WIDTH - 1, cam_tx, cam_ty);
    viewport_blit_all();
  }
  else if (dtx == -1)
  {
    for (UBYTE sy = 0; sy < SCREEN_TILE_HEIGHT; sy++)
    {
      for (UBYTE sx = SCREEN_TILE_WIDTH - 1; sx > 0; sx--)
        screen_buf[sy][sx] = screen_buf[sy][sx - 1];
    }
    viewport_fill_col_from_world(0, cam_tx, cam_ty);
    viewport_blit_all();
  }
  else if (dty == 1)
  {
    for (UBYTE sy = 0; sy < SCREEN_TILE_HEIGHT - 1; sy++)
    {
      for (UBYTE sx = 0; sx < SCREEN_TILE_WIDTH; sx++)
        screen_buf[sy][sx] = screen_buf[sy + 1][sx];
    }
    viewport_fill_row_from_world(SCREEN_TILE_HEIGHT - 1, cam_tx, cam_ty);
    viewport_blit_all();
  }
  else if (dty == -1)
  {
    for (UBYTE sy = SCREEN_TILE_HEIGHT - 1; sy > 0; sy--)
    {
      for (UBYTE sx = 0; sx < SCREEN_TILE_WIDTH; sx++)
        screen_buf[sy][sx] = screen_buf[sy - 1][sx];
    }
    viewport_fill_row_from_world(0, cam_tx, cam_ty);
    viewport_blit_all();
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
  UBYTE tile = chunk_get_tile(world_tx, world_ty);
  screen_buf[sy][sx] = tile;
  graphics_draw_background_at(tile, sx, sy);
}

void viewport_restore_screen_rect(UBYTE sx, UBYTE sy, UBYTE w, UBYTE h)
{
  UBYTE cam_tx = camera_get_tile_x();
  UBYTE cam_ty = camera_get_tile_y();
  UBYTE x, y;

  chunk_ensure_around_camera(cam_tx, cam_ty);

  for (y = sy; y < sy + h && y < SCREEN_TILE_HEIGHT; y++)
  {
    for (x = sx; x < sx + w && x < SCREEN_TILE_WIDTH; x++)
    {
      UBYTE tile = chunk_peek_tile(cam_tx + x, cam_ty + y);
      screen_buf[y][x] = tile;
      graphics_draw_background_at(tile, x, y);
    }
  }
}
