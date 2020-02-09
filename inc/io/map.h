#ifndef IO_MAP_H_
#define IO_MAP_H_

// Includes
#include <io/error.h>

#include <stdbool.h>

// Typedefs
typedef struct point
{
	int	x;
	int	y;
} POINT;

typedef struct line
{
	POINT	start;
	POINT	end;
	bool	front;
} LINE;

typedef struct node
{
	LINE			line;
	struct node *	left;
	struct node *	right;
	int				id;
} NODE;

typedef struct map
{
	NODE *	bspRoot;
	char *	mapName;
} MAP;

// Function declarations
MESSAGE Map_Load
(
	char *	mapPath,
	MAP *	map
);

#endif