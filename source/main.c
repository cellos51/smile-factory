#include <string.h>
#include <tonc.h>
#include <math.h>

#include "camera.h"
#include "util.h"

// objects
#include "player.h"

// tiles
#include "player_gfx.h"
#include "map_gfx.h"

OBJ_ATTR obj_buffer[128];

Player player;

void init()
{
	// init video

	oam_init(obj_buffer, 128);

	memcpy(&tile_mem[4][0], player_gfxTiles, player_gfxTilesLen);
	memcpy(pal_obj_mem, player_gfxPal, player_gfxPalLen);

	memcpy(pal_bg_mem, map_gfxPal, map_gfxPalLen);
	memcpy(&tile_mem[0][0], map_gfxTiles, map_gfxTilesLen);
	memcpy(&se_mem[30][0], map_gfxMap, map_gfxMapLen);

	REG_DISPCNT = DCNT_MODE0 | DCNT_OBJ_1D | DCNT_BG0 | DCNT_OBJ;
	REG_BG0CNT = BG_PRIO(0) | BG_CBB(0) | BG_8BPP | BG_SBB(30) | BG_REG_32x32;

	// init objects

	player_init(&player, obj_buffer, 0, 0);
	camera_init();
	set_camera_target(&player.x, &player.y);
	set_camera_offset((SCREEN_WIDTH - 32) / 2, (SCREEN_HEIGHT - 32) / 2);
	set_camera_delay(16);
}

void update()
{
	player_update(&player);

	camera_update();
}

void draw()
{
	player_draw(&player);

	Vector2i camera = get_camera();
	REG_BG0HOFS = camera.x;
	REG_BG0VOFS = camera.y;

	oam_copy(oam_mem, obj_buffer, 2);
}

int main()
{
	init();

	while(1)
	{
		vid_vsync();
		key_poll();
		update();
		draw();
	}

	return 0;
}
