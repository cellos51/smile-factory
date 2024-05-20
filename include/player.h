#ifndef PLAYER_H
#define PLAYER_H

#include "tonc.h"

#include "sprite.h"

typedef struct 
{
    // sprites
    Sprite body;
    Sprite head;

    // attributes
    FIXED  x, y;
    FIXED hSpeed;
	FIXED vSpeed;
	FIXED diagonalHSpeed;
	FIXED diagonalVSpeed;
} Player;

void player_init(Player* player, OBJ_ATTR* obj_buffer, u32 tid, u32 pid);

void player_update(Player* player);

void player_draw(Player* player);

#endif // PLAYER_H