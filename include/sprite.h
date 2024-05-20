#ifndef SPRITE_H
#define SPRITE_H

#include "tonc.h"

typedef struct 
{
    OBJ_ATTR *obj;
    u32 tid, pid;
} Sprite;

// SQUARE

// Initialize 8x8 sprite
INLINE void initSprite8x8(Sprite* sprite, OBJ_ATTR* obj, u32 tid, u32 pid) 
{
    sprite->obj = obj;
    sprite->tid = tid;
    sprite->pid = pid;
    obj_set_attr(obj, ATTR0_SQUARE | ATTR0_8BPP | ATTR0_REG, ATTR1_SIZE_8x8, ATTR2_PALBANK(pid) | tid);
}

// Initialize 16x16 sprite
INLINE void initSprite16x16(Sprite* sprite, OBJ_ATTR* obj, u32 tid, u32 pid) 
{
    sprite->obj = obj;
    sprite->tid = tid;
    sprite->pid = pid;
    obj_set_attr(obj, ATTR0_SQUARE | ATTR0_8BPP | ATTR0_REG, ATTR1_SIZE_16x16, ATTR2_PALBANK(pid) | tid);
}

// Initialize 32x32 sprite
INLINE void initSprite32x32(Sprite* sprite, OBJ_ATTR* obj, u32 tid, u32 pid) 
{
    sprite->obj = obj;
    sprite->tid = tid;
    sprite->pid = pid;
    obj_set_attr(obj, ATTR0_SQUARE | ATTR0_8BPP | ATTR0_REG, ATTR1_SIZE_32x32, ATTR2_PALBANK(pid) | tid);
}

// Initialize 64x64 sprite
INLINE void initSprite64x64(Sprite* sprite, OBJ_ATTR* obj, u32 tid, u32 pid) 
{
    sprite->obj = obj;
    sprite->tid = tid;
    sprite->pid = pid;
    obj_set_attr(obj, ATTR0_SQUARE | ATTR0_8BPP | ATTR0_REG, ATTR1_SIZE_64x64, ATTR2_PALBANK(pid) | tid);
}

// WIDE

// Initialize 16x8 sprite
INLINE void initSprite16x8(Sprite* sprite, OBJ_ATTR* obj, u32 tid, u32 pid) 
{
    sprite->obj = obj;
    sprite->tid = tid;
    sprite->pid = pid;
    obj_set_attr(obj, ATTR0_WIDE | ATTR0_8BPP | ATTR0_REG, ATTR1_SIZE_16x8, ATTR2_PALBANK(pid) | tid);
}

// Initialize 32x8 sprite
INLINE void initSprite32x8(Sprite* sprite, OBJ_ATTR* obj, u32 tid, u32 pid) 
{
    sprite->obj = obj;
    sprite->tid = tid;
    sprite->pid = pid;
    obj_set_attr(obj, ATTR0_WIDE | ATTR0_8BPP | ATTR0_REG, ATTR1_SIZE_32x8, ATTR2_PALBANK(pid) | tid);
}

// Initialize 32x16 sprite
INLINE void initSprite32x16(Sprite* sprite, OBJ_ATTR* obj, u32 tid, u32 pid) 
{
    sprite->obj = obj;
    sprite->tid = tid;
    sprite->pid = pid;
    obj_set_attr(obj, ATTR0_WIDE | ATTR0_8BPP | ATTR0_REG, ATTR1_SIZE_32x16, ATTR2_PALBANK(pid) | tid);
}

// Initialize 64x32 sprite
INLINE void initSprite64x32(Sprite* sprite, OBJ_ATTR* obj, u32 tid, u32 pid) 
{
    sprite->obj = obj;
    sprite->tid = tid;
    sprite->pid = pid;
    obj_set_attr(obj, ATTR0_WIDE | ATTR0_8BPP | ATTR0_REG, ATTR1_SIZE_64x32, ATTR2_PALBANK(pid) | tid);
}

// TALL

// Initialize 8x16 sprite
INLINE void initSprite8x16(Sprite* sprite, OBJ_ATTR* obj, u32 tid, u32 pid) 
{
    sprite->obj = obj;
    sprite->tid = tid;
    sprite->pid = pid;
    obj_set_attr(obj, ATTR0_TALL | ATTR0_8BPP | ATTR0_REG, ATTR1_SIZE_8x16, ATTR2_PALBANK(pid) | tid);
}

// Initialize 8x32 sprite
INLINE void initSprite8x32(Sprite* sprite, OBJ_ATTR* obj, u32 tid, u32 pid) 
{
    sprite->obj = obj;
    sprite->tid = tid;
    sprite->pid = pid;
    obj_set_attr(obj, ATTR0_TALL | ATTR0_8BPP | ATTR0_REG, ATTR1_SIZE_8x32, ATTR2_PALBANK(pid) | tid);
}

// Initialize 16x32 sprite
INLINE void initSprite16x32(Sprite* sprite, OBJ_ATTR* obj, u32 tid, u32 pid) 
{
    sprite->obj = obj;
    sprite->tid = tid;
    sprite->pid = pid;
    obj_set_attr(obj, ATTR0_TALL | ATTR0_8BPP | ATTR0_REG, ATTR1_SIZE_16x32, ATTR2_PALBANK(pid) | tid);
}

// Initialize 32x64 sprite
INLINE void initSprite32x64(Sprite* sprite, OBJ_ATTR* obj, u32 tid, u32 pid) 
{
    sprite->obj = obj;
    sprite->tid = tid;
    sprite->pid = pid;
    obj_set_attr(obj, ATTR0_TALL | ATTR0_8BPP | ATTR0_REG, ATTR1_SIZE_32x64, ATTR2_PALBANK(pid) | tid);
}

#endif // SPRITE_H