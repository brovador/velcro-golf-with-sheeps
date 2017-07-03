#pragma bank 2
#include "SpriteEnemy.h"
UINT8 bank_SPRITE_ENEMY = 2;

#include "SpriteManager.h"

struct EnemyInfo {
	INT8 vy;
};

void Start_SPRITE_ENEMY() {
	struct EnemyInfo* data = (struct EnemyInfo*)(THIS->custom_data);
	data->vy = 1;
}

void Update_SPRITE_ENEMY() {
	struct EnemyInfo* data = (struct EnemyInfo*)(THIS->custom_data);
	if(TranslateSprite(THIS, 0, data->vy << delta_time)) {
		data->vy = -data->vy;
	}
}

void Destroy_SPRITE_ENEMY() {
}