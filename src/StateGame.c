#pragma bank 2
#include "StateGame.h"
#include <gb/gb.h>
UINT8 bank_STATE_GAME = 2;

#include "../res/src/font.h"
#include "../res/src/tiles.h"
#include "../res/src/map.h"
#include "../res/src/gamegui.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"

#define INT_TO_SPRITES(_I, _PTR_SPRITES) \
	_PTR_SPRITES[0] = FONT_NUMBERS_START + _I / 10; \
	_PTR_SPRITES[1] = FONT_NUMBERS_START + _I % 10; \

#define FONT_LETTERS_START 16
#define FONT_NUMBERS_START 42

#define UIFLAGS_UPDATE_MOVES 0x01
UINT8 UIFLAGS;

UINT8 collisionTiles[] = {GAME_TILE_GRASS, GAME_TILE_VELCRO, GAME_TILE_HOLE, 0};
UINT8 numberSprites[2];
UINT8 levelMoves = 0;
UINT8 levelIdx = 1;

extern UINT8 n_sprite_types;

void Start_STATE_GAME() {
	UINT8 i;

	//Setup level info
	levelMoves = 0;
	levelIdx = 1;

	//Setup sprites
	SPRITES_8x16;
	for(i = 0; i != n_sprite_types; ++ i) {
		SpriteManagerLoad(i);
	}
	SHOW_SPRITES;

	//Setup window
	WY_REG = 128;
	InitWindow(0, 0, gameuiWidth, gameuiHeight, gameui, 3, NULL);
	INT_TO_SPRITES(levelIdx, numberSprites);
	set_win_tiles(7, 1, 2, 1, numberSprites);
	SHOW_WIN;

	//Setup background
	scroll_target = SpriteManagerAdd(SPRITE_PLAYER, 10, 10);
	InitScrollTiles(0, 15, tiles, 3);
	InitScrollTiles(15, 45, font, 3);
	InitScroll(mapWidth, mapHeight, map, collisionTiles, 0, 3);
	SHOW_BKG;
}

void Update_STATE_GAME() {
	
	//Update UI
	if (UIFLAGS & UIFLAGS_UPDATE_MOVES) {
		INT_TO_SPRITES(levelMoves, numberSprites);
		set_win_tiles(17, 1, 2, 1, numberSprites);
	}
	UIFLAGS = 0x00;
}


void StateGame_AddMoves(UINT8 movesToAdd)
{
	if (movesToAdd != 0) {
		levelMoves += movesToAdd;
		UIFLAGS |= UIFLAGS_UPDATE_MOVES;
	}
}