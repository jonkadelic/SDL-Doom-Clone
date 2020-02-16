#ifndef GAME_DATA_H_
#define GAME_DATA_H_

// Includes
#include <stdbool.h>

// Typedefs
struct point
{
	int	x;
	int	y;
};
typedef struct point MAP_POINT;
typedef struct point RENDERER_POINT;

typedef struct map_wall
{
	MAP_POINT	start;
	MAP_POINT	end;
	bool		front;
} MAP_WALL;

typedef struct polygon
{
	int					pointCount;
	RENDERER_POINT *	points;
} POLYGON;

#endif