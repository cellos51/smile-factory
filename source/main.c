#include <string.h>
#include <tonc.h>
#include <math.h>
#include "player.h"

#define COORDINATE_PRECISION 8

OBJ_ATTR obj_buffer[128];
OBJ_AFFINE *obj_aff_buffer = (OBJ_AFFINE *)obj_buffer;

int movement_map[3][3] = {
	{6, 7, 8},
	{5, 0, 1},
	{4, 3, 2}
}; // i had to figure this out manually 😭

void obj_test()
{

	int playerSpeed = 6;
	int playerSpeedDiagonal = (int)(playerSpeed / sqrt(2));

	int x = 96, y = 32;
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
			y += playerSpeed;
			break;
		case 2:
			tid = 64;
			x += playerSpeedDiagonal;
			y += playerSpeedDiagonal;
			break;
		case 3:
			tid = 128;
			x += playerSpeed;
			break;
		case 4:
			tid = 192;
			x += playerSpeedDiagonal;
			y -= playerSpeedDiagonal;
			break;
		case 5:
			tid = 256;
			y -= playerSpeed;
			break;
		case 6:
			tid = 320;
			x -= playerSpeedDiagonal;
			y -= playerSpeedDiagonal;
			break;
		case 7:
			tid = 384;
			x -= playerSpeed;
			break;
		case 8:
			tid = 448;
			x -= playerSpeedDiagonal;
			y += playerSpeedDiagonal;
			break;
		}

		player->attr2 = ATTR2_BUILD(tid, pb, 0);
		obj_set_pos(player, x / COORDINATE_PRECISION, y / COORDINATE_PRECISION);

		oam_copy(oam_mem, obj_buffer, 1); // only need to update one
	}
}

int main()
{
	memcpy(&tile_mem[4][0], playerTiles, playerTilesLen);
	memcpy(pal_obj_mem, playerPal, playerPalLen);

	oam_init(obj_buffer, 128);
	REG_DISPCNT = DCNT_OBJ | DCNT_OBJ_1D;

	obj_test();

	while (1);

	return 0;
}
