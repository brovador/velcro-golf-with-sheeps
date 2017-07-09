#pragma bank 2
#include "SpriteCoin.h"
UINT8 bank_SPRITE_COIN = 2;

#include "SpriteManager.h"

const UINT8 coin_anim_idle[] = {3, 0, 1, 2};

void Start_SPRITE_COIN() {
	SetSpriteAnim(THIS, coin_anim_idle, 10);
}

void Update_SPRITE_COIN() {
}

void Destroy_SPRITE_COIN() {
}