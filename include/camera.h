#ifndef CAMERA_H
#define CAMERA_H

#include <tonc.h>

void camera_init();
void camera_update();

POINT get_camera();
POINT get_camera_fx();

void set_camera(FIXED x, FIXED y);
void set_camera_offset(int x, int y);
void set_camera_delay(int delay);
void set_camera_target(POINT* target);
void remove_camera_target();

void move_camera(FIXED x, FIXED y);
void move_camera_offset(int x, int y);

#endif // CAMERA_H