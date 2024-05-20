#include "camera.h"
#include "math.h"

typedef struct 
{
    FIXED fx, fy;
    int x, y;
    int offset_x, offset_y;
    FIXED* target_x, *target_y;
    int delay;
} Camera;

Camera camera;

void camera_init()
{
    camera.fx = int2fx(0); // fx and fy are the camera's position and x and y are the camera's goal position
    camera.fy = int2fx(0);
    camera.x = 0;
    camera.y = 0;
    camera.offset_x = 0;
    camera.offset_y = 0;
    camera.delay = 1;
}

void camera_update()
{
    FIXED goal_x;
    FIXED goal_y;
    if (camera.target_x != NULL && camera.target_y != NULL)
    {
        goal_x = *camera.target_x;
        goal_y = *camera.target_y;
    }   
    else
    {
        goal_x = int2fx(camera.x);
        goal_y = int2fx(camera.y);
    }
    camera.fx += (goal_x - camera.fx) / camera.delay;
    camera.fy += (goal_y - camera.fy) / camera.delay;
}

Vector2i get_camera()
{
    Vector2i v = {fx2int(camera.fx) - camera.offset_x, fx2int(camera.fy) - camera.offset_y};
    return v;
}

Vector2fx get_camera_fx()
{
    Vector2fx v = {camera.fx - int2fx(camera.offset_x), camera.fy - int2fx(camera.offset_y)};
    return v;
}

void set_camera(int x, int y)
{
    camera.x = x;
    camera.y = y;
}

void set_camera_offset(int x, int y)
{
    camera.offset_x = x;
    camera.offset_y = y;
}

void set_camera_delay(int delay)
{
    camera.delay = delay;
}

void set_camera_target(FIXED* target_x, FIXED* target_y)
{
    camera.target_x = target_x;
    camera.target_y = target_y;
}

void remove_camera_target()
{
    camera.target_x = NULL;
    camera.target_y = NULL;
}

void move_camera(int x, int y)
{
    camera.x += x;
    camera.y += y;
}

void move_camera_offset(int x, int y)
{
    camera.offset_x += x;
    camera.offset_y += y;
}

