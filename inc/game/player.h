#ifndef GAME_PLAYER_H_
#define GAME_PLAYER_H_

// Includes
#include <game/data.h>

// Typedefs
typedef struct player
{
	POINT	position;
	int		angle;
} PLAYER;

// Global variables
extern PLAYER player;

#endif