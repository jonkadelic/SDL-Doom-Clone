// Includes
#include <graphics/map.h>
#include <io/map.h>
#include <graphics/graphics.h>

// Defines
#define MAP_DRAW_SCALE 100

// Function declarations
void Graphics_DrawBSPNode
(
	NODE *	node
);

// Function definitions
void Graphics_DrawMap
(
	MAP	*	map
)
{
	Graphics_StartFrameRender();

	Graphics_DrawBSPNode(map->bspRoot);

	Graphics_EndFrameRender();
}

void Graphics_DrawBSPNode
(
	NODE *	node
)
{
	if (node->line.front == true)
	{
		Graphics_SetDrawColor(0, 0, 255, 255);
	}
	else
	{
		Graphics_SetDrawColor(255, 0, 0, 255);
	}

	Graphics_DrawLine(&(node->line));

	if (node->left != NULL)
	{
		Graphics_DrawBSPNode(node->left);
	}
	if (node->right != NULL)
	{
		Graphics_DrawBSPNode(node->right);
	}
}