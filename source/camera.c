#include "camera.h"
#include "math.h"

typedef struct 
{
    POINT position; // fixed
    POINT offset; // int
    POINT* target; // fixed
    int delay;
} Camera;

Camera camera;

void camera_init()
{
    camera.position = (POINT){0, 0};
    camera.offset = (POINT){0, 0};
    camera.target = NULL;
    camera.delay = 1;
}

void camera_update()
{
    if (camera.target != NULL)
    {
        camera.position.x += (camera.target->x - camera.position.x) / camera.delay;
        camera.position.y += (camera.target->y - camera.position.y) / camera.delay;
    }
}

POINT get_camera()
{
    POINT pos = {fx2int(camera.position.x) - camera.offset.x, fx2int(camera.position.y) - camera.offset.y};
    return pos;
}

POINT get_camera_fx()
{
    POINT pos = {camera.position.x - int2fx(camera.offset.x), camera.position.y - int2fx(camera.offset.y)};
    return pos;
}

void set_camera(FIXED x, FIXED y)
{
    camera.position.x = x;
    camera.position.y = y;
}

void set_camera_offset(int x, int y)
{
    camera.offset.x = x;
    camera.offset.y = y;
}

void set_camera_delay(int delay)
{
    camera.delay = delay;
}

void set_camera_target(POINT* target)
{
    camera.target = target;
}

void remove_camera_target()
{
    camera.target = NULL;
}

void move_camera(FIXED x, FIXED y)
{
    camera.position.x += x;
    camera.position.y += y;
}

void move_camera_offset(int x, int y)
{
    camera.offset.x += x;
    camera.offset.y += y;
}

