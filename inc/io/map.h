#ifndef IO_MAP_H_
#define IO_MAP_H_

// Includes
#include <io/error.h>
#include <game/data.h>

#include <stdbool.h>

// Typedefs
typedef struct node
{
	MAP_WALL		wall;
	struct node *	left;
	struct node *	right;
	int				id;
} NODE;

typedef struct map
{
	NODE *	bspRoot;
	int		nodeCount;
	char *	mapName;
} MAP;

// Function declarations
MESSAGE Map_Load
(
	char *	mapPath,
	MAP *	map
);

#endif