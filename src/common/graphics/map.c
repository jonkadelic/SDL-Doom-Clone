// Includes
#include <stddef.h>
#include <graphics/map.h>
#include <io/map.h>
#include <graphics/graphics.h>

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
	Graphics_DrawBSPNode(handle, map->bspRoot);

	Framebuffer_Blit(handle);
}

void Graphics_DrawBSPNode
(
	FRAMEBUFFER_HANDLE *	handle,
	NODE *	node
)
{
	uint32_t color;
	if (node->wall.front == true)
	{
		color = 0xFF0000FF;
	}
	else
	{
		color = 0xFFFF0000;
	}

	Graphics_DrawLine(handle, &(node->wall.start), &(node->wall.end), color);

	if (node->left != NULL)
	{
		Graphics_DrawBSPNode(handle, node->left);
	}
	if (node->right != NULL)
	{
		Graphics_DrawBSPNode(handle, node->right);
	}
}