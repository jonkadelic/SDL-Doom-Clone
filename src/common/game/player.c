// Includes
#include <game/player.h>

#include <game/angle.h>

// Global variables
PLAYER player;

// Function definitions
void Player_SetAngle
(
	PLAYER *	player,
	DEGREES		angle
)
{
	player->angle = Angle_Normalise(angle);
}