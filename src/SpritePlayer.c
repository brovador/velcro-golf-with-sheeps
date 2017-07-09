#pragma bank 2
#include "ZGBMain.h"
#include "SpritePlayer.h"
#include "Print.h"
UINT8 bank_SPRITE_PLAYER = 2;

#include "Keys.h"
#include "SpriteManager.h"

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
		angle = angle == 0 ? 1 : angle;
		angle = (angle + 1 * ((frameCount % 11) == 0)) % 8;
		anim_idle[1] = angle;
		SetSpriteAnim(THIS, anim_idle, 10);
	} else if (angle != 0xFF) {
		oldx = THIS->x;
		oldy = THIS->y;
		x = X_MOVEMENT(angle) << delta_time;
		y = Y_MOVEMENT(angle) << delta_time;
		coll = TranslateSprite(THIS, x, y);
		
		if (coll == 1) {
			if (angle == 0) angle = 4;
			else if (angle == 1) angle = (THIS->y == oldy) ? 3 : 7;
			else if (angle == 2) angle = 6;
			else if (angle == 3) angle = (THIS->y == oldy) ? 1 : 5;
			else if (angle == 4) angle = 0;
			else if (angle == 5) angle = (THIS->y == oldy) ? 7 : 3;
			else if (angle == 6) angle = 2;
			else if (angle == 7) angle = (THIS->y == oldy) ? 5 : 1;
		} else if (coll == 2) {
			SetState(STATE_GAME);
			return;
		}
		anim_angle[1] = angle;
		SetSpriteAnim(THIS, anim_angle, 10);
	}
}

void Destroy_SPRITE_PLAYER() {
}