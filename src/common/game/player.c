// Includes
#include <game/player.h>

// Defines
#define MAX_PLAYER_ANGLE	3600

// Global variables
PLAYER player;

// Function definitions
void Player_SetAngle
(
	PLAYER *	player,
	int 		angle
)
{
	player->angle = angle % MAX_PLAYER_ANGLE;
}