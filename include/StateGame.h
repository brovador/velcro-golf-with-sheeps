#ifndef STATE_GAME_H
#define STATE_GAME_H

#include "main.h"

#define GAME_TILE_EMPTY 	0
#define GAME_TILE_GRASS 	1
#define GAME_TILE_VELCRO	2
#define GAME_TILE_HOLE  	14

DECLARE_STATE(STATE_GAME);

void StateGame_AddMoves(UINT8 movesToAdd);

#endif