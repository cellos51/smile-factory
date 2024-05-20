#ifndef CAMERA_H
#define CAMERA_H

#include "tonc.h"
#include "util.h"

void camera_init();
void camera_update();

Vector2i get_camera();
Vector2fx get_camera_fx();

void set_camera(int x, int y);
void set_camera_offset(int x, int y);
void set_camera_delay(int delay);
void set_camera_target(int* target_x, int* target_y);
void remove_camera_target();

void move_camera(int x, int y);
void move_camera_offset(int x, int y);

#endif // CAMERA_H