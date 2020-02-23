// Includes
#include <stddef.h>
#include <graphics/renderer_map.h>
#include <io/map.h>
#include <graphics/graphics.h>
#include <game/player.h>

// Defines
#define MAP_DRAW_SCALE 100

// Function declarations
void Graphics_DrawBSPNode
(
	FRAMEBUFFER_HANDLE *	handle,
	NODE *					node
);

// Function definitions
void Graphics_DrawMap
(
	FRAMEBUFFER_HANDLE *	handle,
	MAP	*					map
)
{
	RENDERER_POINT playerFacing;
	playerFacing.x = player.position.x + (Angle_Cos(-player.angle) * 10);
	playerFacing.y = player.position.y + (Angle_Sin(-player.angle) * 10);

	Graphics_DrawBSPNode(handle, map->bspRoot);

	Graphics_DrawLine(handle, &(player.position), &playerFacing, 0xFF0000FF);
	Framebuffer_SetPixel(handle, player.position.x, player.position.y, 0xFF00FF00);

	Framebuffer_Blit(handle);
}

void Graphics_DrawBSPNode
(
	FRAMEBUFFER_HANDLE *	handle,
	NODE *	node
)
{
	uint32_t color = 0xFFFFFFFF;
	if (node->draw == true)
	{
		Graphics_DrawLine(handle, &(node->wall.start), &(node->wall.end), color);
	}


	if (node->left != NULL)
	{
		Graphics_DrawBSPNode(handle, node->left);
	}
	if (node->right != NULL)
	{
		Graphics_DrawBSPNode(handle, node->right);
	}
}