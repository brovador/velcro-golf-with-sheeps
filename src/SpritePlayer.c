#pragma bank 2
#include "SpritePlayer.h"
UINT8 bank_SPRITE_PLAYER = 2;

#include "StateGame.h"

#include "ZGBMain.h"
#include "Print.h"
#include "Keys.h"
#include "SpriteManager.h"

#define PLAYER_STATE_INIT 		0
#define PLAYER_STATE_ROTATING	1
#define PLAYER_STATE_MOVING		2

UINT8 playerState = 0;
UINT8 angle = 0;
UINT8 frameCount = 0;

UINT8 anim_idle[] = {1, 0};
UINT8 anim_angle[] = {1, 0};

#define MAX_DISTANCE 32 * 4
#define X_MOVEMENT(_ANGLE) movementsX[_ANGLE % 8]
#define Y_MOVEMENT(_ANGLE) movementsY[_ANGLE % 8]

const UINT8 movementsX[] = {
	0, 1, 1, 1, 0, -1, -1, -1
};
const UINT8 movementsY[] = {
	-1, -1, 0, 1, 1, 1, 0, -1
};

void Start_SPRITE_PLAYER() {
	THIS->coll_x = 2;
	THIS->coll_y = 2;
	THIS->coll_w = 12;
	THIS->coll_h = 12;
	playerState = PLAYER_STATE_INIT;
	angle = 0xFF;
}

void Update_SPRITE_PLAYER() {

	UINT8 i, x, y, coll, oldx, oldy;
	struct Sprite* spr;

	SPRITEMANAGER_ITERATE(i, spr) {
		if(spr->type == SPRITE_ENEMY) {
			if(CheckCollision(THIS, spr)) {
				SetState(STATE_GAME);
				return;
			}
		} else if (spr->type == SPRITE_COIN) {
			if (CheckCollision(THIS, spr)) {
				SpriteManagerRemoveSprite(spr);
			}
		}
	}

	frameCount++;

	if (KEY_PRESSED(J_A)) {
		if (playerState == PLAYER_STATE_INIT || playerState == PLAYER_STATE_MOVING) {
			playerState = PLAYER_STATE_ROTATING;
			SetSpriteAnim(THIS, anim_idle, 10);
			StateGame_AddMoves(1);
		}
	} else {
		if (playerState == PLAYER_STATE_ROTATING) {
			playerState = PLAYER_STATE_MOVING;
			anim_angle[1] = angle;
			SetSpriteAnim(THIS, anim_angle, 10);
		}
	}

	switch(playerState) {
		case PLAYER_STATE_INIT: {
			//nothing here...
			break;
		}
		case PLAYER_STATE_ROTATING: {
			angle = angle == 0 ? 1 : angle;
			angle = (angle + 1 * ((frameCount % 11) == 0)) % 8;
			anim_idle[1] = angle;
			break;
		}
		case PLAYER_STATE_MOVING: {
			oldx = THIS->x;
			oldy = THIS->y;
			x = X_MOVEMENT(angle) << delta_time;
			y = Y_MOVEMENT(angle) << delta_time;
			coll = TranslateSprite(THIS, x, y);
			
			if (coll == GAME_TILE_GRASS) {
				if (angle == 0) angle = 4;
				else if (angle == 1) angle = (THIS->y == oldy) ? 3 : 7;
				else if (angle == 2) angle = 6;
				else if (angle == 3) angle = (THIS->y == oldy) ? 1 : 5;
				else if (angle == 4) angle = 0;
				else if (angle == 5) angle = (THIS->y == oldy) ? 7 : 3;
				else if (angle == 6) angle = 2;
				else if (angle == 7) angle = (THIS->y == oldy) ? 5 : 1;
				anim_angle[1] = angle;
			} else if (coll == GAME_TILE_VELCRO) {
				SetState(STATE_GAME);
				return;
			} else if (coll == GAME_TILE_HOLE) {
				//Win
				SetState(STATE_GAME);
				return;
			}
			break;
		}
	}
}

void Destroy_SPRITE_PLAYER() {
}