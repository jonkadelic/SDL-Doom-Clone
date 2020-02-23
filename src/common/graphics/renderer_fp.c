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
#define HEIGHT_SCALE	256

#define vxs(x0,y0, x1,y1)    ((x0)*(y1) - (x1)*(y0))   // vxs: Vector cross product
#define Intersect(x1,y1, x2,y2, x3,y3, x4,y4) ((MAP_POINT) { \
    vxs(vxs(x1,y1, x2,y2), (x1)-(x2), vxs(x3,y3, x4,y4), (x3)-(x4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)), \
    vxs(vxs(x1,y1, x2,y2), (y1)-(y2), vxs(x3,y3, x4,y4), (y3)-(y4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)) })


// Local variables
static bool drawNode = true;

// Function declarations
void renderWall
(
	FRAMEBUFFER_HANDLE *	handle,
	NODE *					node
);

void transformWall
(
	MAP_WALL *	wall,
	MAP_POINT *	offset
);

void rotateWall
(
	MAP_WALL *	wall,
	MAP_POINT *	origin,
	DEGREES		angle
);

int dotCross
(
	int x1,
	int y1,
	int x2,
	int y2
);

void getViewplaneIntersect
(
	MAP_POINT *	w1,
	MAP_POINT *	w2,
	MAP_POINT *	v1,
	MAP_POINT *	v2,
	MAP_POINT *	out
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
	RENDERER_POINT center = { FRAMEBUFFER_WIDTH / 2, FRAMEBUFFER_HEIGHT / 2 };
	MAP_WALL tempWall = node->wall;
	RENDERER_POINT sTop, sBottom, eTop, eBottom;
	uint32_t argb;

	if (node->draw == false)
	{
		return;
	}

	transformWall(&tempWall, &player.position);
	rotateWall(&tempWall, &player.position, player.angle);

	if (tempWall.start.x <= 0 && tempWall.end.x <= 0)
	{
		return;
	}

	if (tempWall.start.x <= 0 || tempWall.end.x <= 0)
	{
		float nearz = 1e-4f, farz = 5, nearside = 1e-5f, farside = 30.f;
		// Find an intersection between the wall and the approximate edges of player's view
		MAP_POINT i1 = Intersect(tempWall.start.y,tempWall.start.x,tempWall.end.y,tempWall.end.x, -nearside,nearz, -farside,farz);
		MAP_POINT i2 = Intersect(tempWall.start.y,tempWall.start.x,tempWall.end.y,tempWall.end.x,  nearside,nearz,  farside,farz);
		if(tempWall.start.x < nearz) { if(i1.y > 0) { tempWall.start.y = i1.x; tempWall.start.x = i1.y; } else { tempWall.start.y = i2.x; tempWall.start.x = i2.y; } }
		if(tempWall.end.x < nearz) { if(i1.y > 0) { tempWall.end.y = i1.x; tempWall.end.x = i1.y; } else { tempWall.end.y = i2.x; tempWall.end.x = i2.y; } }
	}

	// Divide Y and Z coordinates by the X
	// Let's just assume for the moment the Z coordinates are 128 and -128
	if (tempWall.start.x > 0)
	{
		sTop.x = sBottom.x = 	center.x + ((tempWall.start.y * PLAYER_FOV) / tempWall.start.x);
		sTop.y = 				center.y + ((player.height * HEIGHT_SCALE + HEIGHT_SCALE * -node->wall.height) / tempWall.start.x);
		sBottom.y = 			center.y + ((player.height * HEIGHT_SCALE + HEIGHT_SCALE) / tempWall.start.x);
	}
	
	if (tempWall.end.x > 0)
	{
		eTop.x = eBottom.x = 	center.x + ((tempWall.end.y * PLAYER_FOV) / tempWall.end.x);
		eTop.y = 				center.y + ((player.height * HEIGHT_SCALE + HEIGHT_SCALE * -node->wall.height) / tempWall.end.x);
		eBottom.y = 			center.y + ((player.height * HEIGHT_SCALE + HEIGHT_SCALE) / tempWall.end.x);
	}

	argb = 0xFF000000 | ((node->wall.start.x & 0xFF) << 16) | ((node->wall.start.y & 0xFF) << 8) | ((node->wall.end.x & 0xFF) << 0);
	
	Graphics_DrawWall(handle, sTop.x, sTop.y, sBottom.y, eTop.x, eTop.y, eBottom.y, argb);
}

void transformWall
(
	MAP_WALL *	wall,
	MAP_POINT *	offset
)
{
	wall->start.x -= offset->x;
	wall->start.y -= offset->y;
	wall->end.x -= offset->x;
	wall->end.y -= offset->y;
}

void rotateWall
(
	MAP_WALL *	wall,
	MAP_POINT *	origin,
	DEGREES		angle
)
{
	float s = Angle_Sin(angle);
	float c = Angle_Cos(angle);

	MAP_POINT p = { wall->start.x, wall->start.y };

	wall->start.x = (p.x * c - p.y * s);
	wall->start.y = (p.x * s + p.y * c);

	p.x = wall->end.x;
	p.y = wall->end.y;

	wall->end.x = (p.x * c - p.y * s);
	wall->end.y = (p.x * s + p.y * c);
}