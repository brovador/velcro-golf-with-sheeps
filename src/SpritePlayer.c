#pragma bank 2
#include "ZGBMain.h"
#include "SpritePlayer.h"
UINT8 bank_SPRITE_PLAYER = 2;

#include "Keys.h"
#include "SpriteManager.h"

const UINT8 anim_idle[] = {1, 0};
const UINT8 anim_walk[] = {2, 1, 2};

void Start_SPRITE_PLAYER() {
	THIS->coll_x = 2;
	THIS->coll_y = 0;
	THIS->coll_w = 12;
	THIS->coll_h = 16;
}

void Update_SPRITE_PLAYER() {
	UINT8 i;
	struct Sprite* spr;

	SPRITEMANAGER_ITERATE(i, spr) {
		if(spr->type == SPRITE_ENEMY) {
			if(CheckCollision(THIS, spr)) {
				SetState(STATE_GAME);
			}
		}
	}

	if(KEY_PRESSED(J_UP)) {
		TranslateSprite(THIS, 0, -1 << delta_time);
		SetSpriteAnim(THIS, anim_walk, 15);
	} 
	if(KEY_PRESSED(J_DOWN)) {
		TranslateSprite(THIS, 0, 1 << delta_time);
		SetSpriteAnim(THIS, anim_walk, 15);
	}
	if(KEY_PRESSED(J_LEFT)) {
		TranslateSprite(THIS, -1 << delta_time, 0);
		SetSpriteAnim(THIS, anim_walk, 15);
	}
	if(KEY_PRESSED(J_RIGHT)) {
		TranslateSprite(THIS, 1 << delta_time, 0);
		SetSpriteAnim(THIS, anim_walk, 15);
	}
	if(keys == 0) {
		SetSpriteAnim(THIS, anim_idle, 15);
	}
}

void Destroy_SPRITE_PLAYER() {
}