#ifndef GAME_PLAYER_H_
#define GAME_PLAYER_H_

// Includes
#include <game/data.h>

#include <game/angle.h>

// Defines
#define PLAYER_HEIGHT	32
#define PLAYER_FOV		90.0

// Typedefs
typedef struct player
{
	MAP_POINT	position;
	int			height;
	DEGREES		angle;
	DEGREES		fov;
} PLAYER;

// Global variables
extern PLAYER player;

// Function declarations
void Player_SetAngle
(
	PLAYER *	player,
	DEGREES		angle
);

#endif