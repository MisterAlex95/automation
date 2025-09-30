#include "camera.h"
#include "constants.h"
#include "graphics.h"

// Position in pixels
UINT16 camera_x = 0, camera_y = 0;

void camera_update(int dx, int dy)
{
  int new_camera_x = camera_x + dx * TILE_SIZE;
  int new_camera_y = camera_y + dy * TILE_SIZE;

  if (new_camera_x < 0)
    new_camera_x = 0;
  if (new_camera_y < 0)
    new_camera_y = 0;

  if (new_camera_x > (MAP_WIDTH_PIXEL - SCREEN_WIDTH))
    new_camera_x = MAP_WIDTH_PIXEL - SCREEN_WIDTH;
  if (new_camera_y > (MAP_HEIGHT_PIXEL - SCREEN_HEIGHT))
    new_camera_y = MAP_HEIGHT_PIXEL - SCREEN_HEIGHT;

  camera_x = new_camera_x;
  camera_y = new_camera_y;

  move_bkg(camera_x, camera_y);
}