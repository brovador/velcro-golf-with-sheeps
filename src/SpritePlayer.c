#pragma bank 2
#include "ZGBMain.h"
#include "SpritePlayer.h"
#include "Print.h"
UINT8 bank_SPRITE_PLAYER = 2;

#include "Keys.h"
#include "SpriteManager.h"

UINT8 angle = 0;
UINT8 distance = 0;

const UINT8 anim_idle[] = {8, 0, 1, 2, 3, 4, 5, 6, 7};
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
	THIS->coll_x = 4;
	THIS->coll_y = 4;
	THIS->coll_w = 4;
	THIS->coll_h = 4;

	distance = MAX_DISTANCE;
	angle = 3;
}

void Update_SPRITE_PLAYER() {

	UINT8 i, x, y, coll;
	struct Sprite* spr;

	if (distance < MAX_DISTANCE) {
		x = X_MOVEMENT(angle) << delta_time;
		y = Y_MOVEMENT(angle) << delta_time;

		coll = TranslateSprite(THIS, x, y);
		distance += x * x + y * y;
		
		if (coll == 1) {

			//Ugly but functional			
			if (angle == 0) angle = 4;
			else if (angle == 1) angle = 3;
			else if (angle == 2) angle = 6;
			else if (angle == 3) angle = 1;
			else if (angle == 4) angle = 0;
			else if (angle == 5) angle = 7;
			else if (angle == 6) angle = 2;
			else if (angle == 7) angle = 5;

			anim_angle[1] = angle % 8;
		}
	} else {
		SetSpriteAnim(THIS, anim_idle, 4);
	}

	if (distance >= MAX_DISTANCE) {
		if (KEY_PRESSED(J_A)) {
			distance = 0;
			angle = THIS->current_frame;
			anim_angle[1] = angle;
			SetSpriteAnim(THIS, anim_angle, 15);
		}
	}
}

void Destroy_SPRITE_PLAYER() {
}