#include "player.h"
#include "camera.h"
#include "util.h"

static const int body_tid_lut[8][4] =
{
    {0, 32, 0, 64},
    {96, 128, 96, 160},
    {192, 224, 192, 256},
    {288, 320, 288, 352},
    {384, 416, 384, 448},
    {288, 320, 288, 352},
    {192, 224, 192, 256},
    {96, 128, 96, 160}
};

static const int head_tid_lut[8][4] = // genuinely fuck my partner for making the sprite layout this way
{
    {480, 516, 480, 532},
    {488, 496, 488, 504},
    {484, 496, 484, 500},
    {508, 512, 508, 520},
    {528, 524, 528, 524},
    {508, 512, 508, 520},
    {484, 496, 484, 500},
    {488, 496, 488, 504}
};

#define PLAYER_ANIMATION_SPEED 8 // in frames per second (1 to 60)

void player_init(Player *player, OBJ_ATTR *obj_buffer, u32 tid, u32 pid)
{
    player->body.obj = &obj_buffer[0];
    player->head.obj = &obj_buffer[1];
    player->body.tid = tid;
    player->body.pid = pid;
    player->head.tid = tid + 32 * 15; // head sprites come 128 tiles after body sprites
    player->head.pid = pid;

    initSprite32x32(&player->body, player->body.obj, player->body.tid, player->body.pid);
    initSprite16x8(&player->head, player->head.obj, player->head.tid, player->head.pid);

    player->x = SCREEN_WIDTH / 2;
    player->y = SCREEN_HEIGHT / 2;

    player->hSpeed = float2fx(1.0f);
    player->vSpeed = float2fx(1.0f);
    player->diagonalHSpeed = float2fx(1.0f);
    player->diagonalVSpeed = float2fx(0.5f);
}

void player_update(Player *player)
{
    int movement = movement_lut[key_tri_horz() + 1][key_tri_vert() + 1];

    static u32 frame = 0;
    frame++;

    static u32 animate = 0;
    if (frame % PLAYER_ANIMATION_SPEED == 0)
    {
        animate = (animate + 1) % 4; // 4 frames per animation
    }

    static int last_movement = 1;

    if (movement != 0)
    {
        last_movement = movement;

        player->body.tid = body_tid_lut[movement - 1][animate];
        player->head.tid = head_tid_lut[movement - 1][animate];

        if (movement > 5)
        {
            player->body.obj->attr1 |= ATTR1_HFLIP;
            player->head.obj->attr1 |= ATTR1_HFLIP;
        }
        else
        {
            player->body.obj->attr1 &= ~ATTR1_HFLIP;
            player->head.obj->attr1 &= ~ATTR1_HFLIP;
        }
    }
    else
    {
        player->body.tid = body_tid_lut[last_movement - 1][0];
        player->head.tid = head_tid_lut[last_movement - 1][0];
    }

    switch (movement)
    {
    case 0:
        // do nothing if no movement
        break;
    case 1:
        player->y = fxadd(player->y, player->vSpeed);
        break;
    case 2:
        player->x = fxadd(player->x, player->diagonalHSpeed);
        player->y = fxadd(player->y, player->diagonalVSpeed);
        break;
    case 3:
        player->x = fxadd(player->x, player->hSpeed);
        break;
    case 4:
        player->x = fxadd(player->x, player->diagonalHSpeed);
        player->y = fxadd(player->y, -player->diagonalVSpeed);
        break;
    case 5:
        player->y = fxadd(player->y, -player->vSpeed);
        break;
    case 6:
        player->x = fxadd(player->x, -player->diagonalHSpeed);
        player->y = fxadd(player->y, -player->diagonalVSpeed);
        break;
    case 7:
        player->x = fxadd(player->x, -player->hSpeed);
        break;
    case 8:
        player->x = fxadd(player->x, -player->diagonalHSpeed);
        player->y = fxadd(player->y, player->diagonalVSpeed);
        break;
    }
}

void player_draw(Player *player)
{
    Vector2fx camera = get_camera_fx();

    int ix, iy;
    ix = fx2int(player->x - camera.x);
    iy = fx2int(player->y - camera.y);

    player->body.obj->attr2 = ATTR2_BUILD(player->body.tid, player->body.pid, 0);
    player->head.obj->attr2 = ATTR2_BUILD(player->head.tid, player->head.pid, 0);

    obj_set_pos(player->body.obj, ix, iy);
    obj_set_pos(player->head.obj, ix + 8, iy - 8);
}