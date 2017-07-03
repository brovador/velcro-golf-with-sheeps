#pragma bank 2
#include "SpritePlayer.h"
UINT8 bank_SPRITE_PLAYER = 2;

#include "Keys.h"
#include "SpriteManager.h"

void Start_SPRITE_PLAYER() {
}

void Update_SPRITE_PLAYER() {
	if(KEY_PRESSED(J_UP)) {
		THIS->y --;
	} 
	if(KEY_PRESSED(J_DOWN)) {
		THIS->y ++;
	}
	if(KEY_PRESSED(J_LEFT)) {
		THIS->x --;
	}
	if(KEY_PRESSED(J_RIGHT)) {
		THIS->x ++;
	}
}

void Destroy_SPRITE_PLAYER() {
}