#ifndef ZGBMAIN_H
#define ZGBMAIN_H

#include "main.h"

typedef enum {
	STATE_GAME,

	N_STATES
} STATE;

typedef enum {
	SPRITE_PLAYER,
	SPRITE_ENEMY,
	SPRITE_COIN,

	N_SPRITE_TYPES
} SPRITE_TYPE;

#endif