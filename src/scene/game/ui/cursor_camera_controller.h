#ifndef CURSOR_CAMERA_CONTROLLER_H
#define CURSOR_CAMERA_CONTROLLER_H

#include <gb/gb.h>

void cursor_camera_handle_movement(int dx, int dy, UINT8 *cursor_x,
                                   UINT8 *cursor_y);
void cursor_camera_center_cursor(UINT8 *cursor_x, UINT8 *cursor_y);

#endif // CURSOR_CAMERA_CONTROLLER_H
