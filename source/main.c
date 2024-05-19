#include <string.h>
#include <tonc.h>
#include <math.h>

#include "player.h"
#include "map.h"

OBJ_ATTR obj_buffer[128];
OBJ_AFFINE *obj_aff_buffer = (OBJ_AFFINE *)obj_buffer;

int movement_map[3][3] = {
	{6, 7, 8},
	{5, 0, 1},
	{4, 3, 2}
}; // i had to figure this out manually 😭

void obj_test()
{
	FIXED hSpeed = float2fx(1);
	FIXED vSpeed = float2fx(1);
	FIXED diagonalHSpeed = float2fx(1);
	FIXED diagonalVSpeed = float2fx(0.5f);

	FIXED x = 0, y = 0;
	FIXED camX = 0, camY = 0;
	int camOffsetX = (240 - 32) / 2, camOffsetY = (160 - 96) / 2;

	u32 tid = 0, pb = 0;
	OBJ_ATTR *player = &obj_buffer[0];
	obj_set_attr(player, ATTR0_TALL | ATTR0_8BPP, ATTR1_SIZE_32x64, ATTR2_PALBANK(pb) | tid); // palbank 0, tile 0
	obj_set_pos(player, x, y);

	while (1)
	{
		vid_vsync();
		key_poll();

		int movement = movement_map[key_tri_horz() + 1][key_tri_vert() + 1];

		switch (movement)
		{
		case 0:
			// do nothing if no movement
			break;
		case 1:
			tid = 0;
			y = fxadd(y, vSpeed);
			break;
		case 2:
			tid = 64;
			x = fxadd(x, diagonalHSpeed);
			y = fxadd(y, diagonalVSpeed);
			break;
		case 3:
			tid = 128;
			x += hSpeed;
			break;
		case 4:
			tid = 192;
			x = fxadd(x, diagonalHSpeed);
			y = fxadd(y, -diagonalVSpeed);
			break;
		case 5:
			tid = 256;
			y = fxadd(y, -vSpeed);
			break;
		case 6:
			tid = 320;
			x = fxadd(x, -diagonalHSpeed);
			y = fxadd(y, -diagonalVSpeed);
			break;
		case 7:
			tid = 384;
			x -= hSpeed;
			break;
		case 8:
			tid = 448;
			x = fxadd(x, -diagonalHSpeed);
			y = fxadd(y, diagonalVSpeed);
			break;
		}

		camX -= (x + camX) / 16;
		camY -= (y + camY) / 16;

		player->attr2 = ATTR2_BUILD(tid, pb, 0);
		obj_set_pos(player, fx2int(x + camX) + camOffsetX, fx2int(y + camY) + camOffsetY);

		oam_copy(oam_mem, obj_buffer, 1); // only need to update one

		REG_BG0HOFS = -fx2int(camX) + camOffsetX;
		REG_BG0VOFS = -fx2int(camY) + camOffsetY;
	}
}

int main()
{
	memcpy(&tile_mem[4][0], playerTiles, playerTilesLen);
	memcpy(pal_obj_mem, playerPal, playerPalLen);

	oam_init(obj_buffer, 128);

	memcpy(pal_bg_mem, mapPal, mapPalLen);
	memcpy(&tile_mem[0][0], mapTiles, mapTilesLen);
	memcpy(&se_mem[30][0], mapMap, mapMapLen);

	REG_BG0CNT= BG_CBB(0) | BG_SBB(30) | BG_8BPP | BG_REG_32x32;
	REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_OBJ | DCNT_OBJ_1D;

	obj_test();

	return 0;
}
