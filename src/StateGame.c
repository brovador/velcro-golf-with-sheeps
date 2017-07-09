#pragma bank 2
#include "StateGame.h"
#include <gb/gb.h>
UINT8 bank_STATE_GAME = 2;

#include "../res/src/tiles.h"
#include "../res/src/map.h"
#include "../res/src/gamegui.h"

#include "BankManager.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"

UINT8 collision_tiles[] = {1, 2, 0};
UINT8 points = 100;

extern UINT8 n_sprite_types;
void Start_STATE_GAME() {
	UINT8 i;

	SPRITES_8x16;
	for(i = 0; i != n_sprite_types; ++ i) {
		SpriteManagerLoad(i);
	}
	SHOW_SPRITES;

	WY_REG = 120;
	InitWindow(0, 0, gameuiWidth, gameuiHeight, gameui, 3, NULL);
	SHOW_WIN;

	scroll_target = SpriteManagerAdd(SPRITE_PLAYER, 10, 10);
	InitScrollTiles(0, 15, tiles, 3);
	InitScroll(mapWidth, mapHeight, map, collision_tiles, 0, 3);
	SHOW_BKG;
	
	
}

void Update_STATE_GAME() {

}