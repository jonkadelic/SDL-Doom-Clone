// Includes
#include <graphics/renderer_fp.h>

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <graphics/graphics.h>
#include <game/data.h>
#include <game/player.h>
#include <graphics/bsp.h>

// Defines
#define DIST_SCALE	50000

// Local variables
static bool drawNode = true;

// Function declarations
void renderWall
(
	FRAMEBUFFER_HANDLE *	handle,
	NODE *					node
);

DEGREES getColumnAngle
(
	MAP_POINT *	point
);

int flattenAngle
(
	DEGREES angle
);

int getColumnHeight
(
	MAP_POINT *	point
);

void fixOverdraw
(
	DEGREES	a,
	DEGREES	b,
	int *	ax,
	int *	bx
);

MAP_POINT getLineIntersect
(
	MAP_POINT *	a1,
	MAP_POINT *	a2,
	MAP_POINT *	b1,
	MAP_POINT *	b2
);

MAP_WALL constrainWallToViewplane
(
	MAP_WALL *	wall
);

// Function definitions
void Renderer_FirstPerson_Render
(
	FRAMEBUFFER_HANDLE *	handle,
	MAP *					map
)
{
	NODE **	nodeSet = malloc(sizeof(NODE*) * map->nodeCount);
	int		i;
	int		setSize;

	// Get ordered list of walls
	setSize = BSP_GenerateOrderedLineSet(&player.position, map->bspRoot, nodeSet);

	for (i = 0; i < setSize; i++)
	{
		renderWall(handle, nodeSet[i]);
	}

	free(nodeSet);
}

void renderWall
(
	FRAMEBUFFER_HANDLE *	handle,
	NODE *					node
)
{
	RENDERER_POINT startTop, startBottom, endTop, endBottom;
	int tempHeight;
	RENDERER_POINT fbCentre = { FRAMEBUFFER_WIDTH / 2, FRAMEBUFFER_HEIGHT / 2 };
	uint32_t argb;
	DEGREES startAngle;
	DEGREES endAngle;

	startAngle = getColumnAngle(&node->wall.start);
	endAngle = getColumnAngle(&node->wall.end);

	startTop.x = startBottom.x = flattenAngle(startAngle);
	endTop.x = endBottom.x = flattenAngle(endAngle);
	tempHeight = getColumnHeight(&node->wall.start) / 2;
	startTop.y = fbCentre.y - tempHeight;
	startBottom.y = fbCentre.y + tempHeight;
	tempHeight = getColumnHeight(&node->wall.end) / 2;
	endTop.y = fbCentre.y - tempHeight;
	endBottom.y = fbCentre.y + tempHeight;

	argb = 0xFF000000 | ((node->wall.start.x & 0xFF) << 16) | ((node->wall.start.y & 0xFF) << 8) | ((node->wall.end.x & 0xFF) << 0);

	if (((startAngle > 90 && endAngle < -90) || (startAngle < -90 && endAngle > 90)) ||
		((startAngle > 90 && endAngle > 90)  || (startAngle < -90 && endAngle < -90)))
	{
		node->draw = false;
	}

	fixOverdraw(startAngle, endAngle, &startTop.x, &endTop.x);
	startBottom.x = startTop.x;
	endBottom.x = endTop.x;

	if (node->draw == false)
	{
		return;
	}

	Graphics_DrawWall(handle, startTop.x, startTop.y, startBottom.y, endTop.x, endTop.y, endBottom.y, argb);
}

DEGREES getColumnAngle
(
	MAP_POINT *	point
)
{
	return Angle_Atan2(point->y - player.position.y, point->x - player.position.x) + player.angle;
}

int flattenAngle
(
	DEGREES angle
)
{
	return ((angle + (0.5 * PLAYER_FOV)) / PLAYER_FOV) * FRAMEBUFFER_WIDTH;
}

int getColumnHeight
(
	MAP_POINT *	point
)
{
	MAP_POINT relativePoint = { point->x - player.position.x, point->y - player.position.y };

	float distance = sqrtf(powf(relativePoint.x, 2.0f) + powf(relativePoint.y, 2));

	return (DIST_SCALE / distance);
}

void fixOverdraw
(
	DEGREES	a,
	DEGREES	b,
	int *	ax,
	int *	bx
)
{
	DEGREES halfFov = PLAYER_FOV / 2;
	DEGREES quarterFov = PLAYER_FOV / 4;

	if (0 > a && a > -halfFov && -halfFov > b && b > -180)
	{
		*bx = 0;
	}
	if (0 > a && a > -halfFov && 180 > b && b > halfFov)
	{
		if ((180 - b) < -a)
		{
			*bx = 0;
		}
		else
		{
			*bx = FRAMEBUFFER_WIDTH;
		}
	}
	if (halfFov > a && a > 0 && 180 > b && b > halfFov)
	{
		*bx = FRAMEBUFFER_WIDTH;
	}
	if (halfFov > a && a > 0 && -halfFov > b && b > -180)
	{
		if ((180 + b) < a)
		{
			*bx = FRAMEBUFFER_WIDTH;
		}
		else
		{
			*bx = 0;
		}
	}
	if (0 > b && b > -halfFov && -halfFov > a && a > -180)
	{
		*ax = 0;
	}
	if (0 > b && b > -halfFov && 180 > a && a > halfFov)
	{
		if ((180 - a) < -b)
		{
			*ax = 0;
		}
		else
		{
			*ax = FRAMEBUFFER_WIDTH;
		}
	}
	if (halfFov > b && b > 0 && 180 > a && a > halfFov)
	{
		*ax = FRAMEBUFFER_WIDTH;
	}
	if (halfFov > b && b > 0 && -halfFov > a && a > -180)
	{
		if ((180 + a) < b)
		{
			*ax = FRAMEBUFFER_WIDTH;
		}
		else
		{
			*ax = 0;
		}
	}
}

MAP_POINT getLineIntersect
(
	MAP_POINT *	a1,
	MAP_POINT *	a2,
	MAP_POINT *	b1,
	MAP_POINT *	b2
)
{
	int x12 = a1->x - a2->x;
	int x34 = b1->x - b2->x;
	int y12 = a1->y - a2->y;
	int y34 = b1->y - b2->y;

	int c = x12 * y34 - y12 * x34;

	int a = a1->x * a2->y - a1->y * a2->x;
	int b = b1->x * b2->y - b1->y * b2->x;

	int x = (a * x34 - b * x12) / c;
	int y = (a * y34 - b * y12) / c;

	return (MAP_POINT){ x, y };
}

MAP_WALL constrainWallToViewplane
(
	MAP_WALL *	wall
)
{
	DEGREES halfFov = PLAYER_FOV / 2;
	MAP_POINT fovRayA, fovRayB;
	DEGREES startAngle, endAngle;
	MAP_POINT intersect;

	fovRayA.x = player.position.x + Angle_Cos(player.angle - halfFov);
	fovRayA.y = player.position.y - Angle_Sin(player.angle - halfFov);

	fovRayB.x = player.position.x + Angle_Cos(player.angle + halfFov);
	fovRayB.y = player.position.y - Angle_Sin(player.angle + halfFov);

	startAngle = getColumnAngle(&wall->start);
	endAngle = getColumnAngle(&wall->end);

	intersect = getLineIntersect(&player.position, &fovRayA, &wall->start, &wall->end);
	return *wall;
	// Not done
}