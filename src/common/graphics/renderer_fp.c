// Includes
#include <graphics/renderer_fp.h>

#include <stdlib.h>
#include <math.h>

#include <graphics/graphics.h>
#include <game/data.h>
#include <game/player.h>
#include <graphics/bsp.h>

// Defines
#define HEIGHT_SCALE	512.0

// Function declarations
void Graphics_RenderWall
(
	FRAMEBUFFER_HANDLE *	handle,
	MAP_WALL *				wall
);

void Graphics_GetPointTopBottom
(
	FRAMEBUFFER_HANDLE *	handle,
	MAP_POINT *				point,
	int *					top,
	int *					bottom
);

void Graphics_GetPointX
(
	FRAMEBUFFER_HANDLE *	handle,
	MAP_POINT *				point,
	int *					x
);

// Function definitions
void Graphics_RenderFirstPerson
(
	FRAMEBUFFER_HANDLE *	handle,
	MAP *					map
)
{
	int i;
	MAP_WALL *	wallSet = malloc(sizeof(MAP_WALL) * map->nodeCount);

	// Get ordered list of walls
	BSP_GenerateOrderedLineSet(&(player.position), map->bspRoot, wallSet);

	for (i = map->nodeCount - 1; i >= 0; i--)
	{
		Graphics_RenderWall(handle, &(wallSet[i]));
	}

	free(wallSet);
}

void Graphics_RenderWall
(
	FRAMEBUFFER_HANDLE *	handle,
	MAP_WALL *				wall
)
{
	RENDERER_POINT startTop;
	RENDERER_POINT startBottom;
	RENDERER_POINT endTop;
	RENDERER_POINT endBottom;
	RENDERER_POLYGON polygon;
	uint32_t argb;

	Graphics_GetPointTopBottom(handle, &(wall->start), &(startTop.y), &(startBottom.y));
	Graphics_GetPointX(handle, &(wall->start), &(startTop.x));
	startBottom.x = startTop.x;
	Graphics_GetPointTopBottom(handle, &(wall->end), &(endTop.y), &(endBottom.y));
	Graphics_GetPointX(handle, &(wall->end), &(endTop.x));
	endBottom.x = endTop.x;

	polygon.points = malloc(4 * sizeof(RENDERER_POINT*));
	polygon.count = 4;
	polygon.points[0] = startTop;
	polygon.points[1] = startBottom;
	polygon.points[2] = endBottom;
	polygon.points[3] = endTop;

	argb = 0xFF000000 | ((0x00FFFFFF & wall->start.x) << 16) | ((0x00FFFFFF & wall->start.y) << 8) | ((0x00FFFFFF & wall->end.x));

	Graphics_DrawFilledPolygon(handle, &polygon, argb);

	free(polygon.points);
}

void Graphics_GetPointTopBottom
(
	FRAMEBUFFER_HANDLE *	handle,
	MAP_POINT *				point,
	int *					top,
	int *					bottom
)
{
	int dx, dy;
	int dist;

	int fbMidY = Framebuffer_GetHeight(handle) / 2;

	dx = player.position.x - point->x;
	dy = player.position.y - point->y;
	dist = (int)sqrt(pow(dx, 2) + pow(dy, 2));

	*bottom = fbMidY + (player.height * (HEIGHT_SCALE/dist));
	*top = fbMidY - (32 * (HEIGHT_SCALE/dist));
}

void Graphics_GetPointX
(
	FRAMEBUFFER_HANDLE *	handle,
	MAP_POINT *				point,
	int *					x
)
{
	int dx, dy;
	DEGREES halfFov = player.fov / 2;
	DEGREES angle;
	float f;

	int fbMidX = Framebuffer_GetWidth(handle) / 2;

	dx = point->x - player.position.x;
	dy = point->y - player.position.y;
	angle = Angle_Atan2(dy, dx) + player.angle;

	f = angle / halfFov;
	*x = Framebuffer_GetWidth(handle) * f;
}