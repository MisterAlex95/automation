#ifndef CAMERA_H
#define CAMERA_H

#include <gb/gb.h>

#define CAMERA_SPEED 1

extern UINT16 camera_x, camera_y;

void camera_update(int dx, int dy);

#endif // CAMERA_H
