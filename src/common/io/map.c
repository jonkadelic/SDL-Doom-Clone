// Includes
#include <io/map.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defines
#define MAP_NAME_BUFFER_SIZE	32

// Function definitions
MESSAGE Map_Load
(
	char *	mapPath,
	MAP *	map
)
{
	FILE *	fp;

	int		nodeCount;
	int		i;
	int		id, startx, starty, endx, endy, front;
	int		leftid, rightid;

	char	mapName[MAP_NAME_BUFFER_SIZE];

	NODE *	nodeArray;

	fp = fopen(mapPath, "r");
	if (fp == NULL)
	{
		THROW_ERROR(STATUS_FAILURE, "Map does not exist!");
	}

	if (fscanf(fp, "%d\n", &nodeCount) != 1)
	{
		THROW_ERROR(STATUS_FAILURE, "Map data is not valid!");
	}

	nodeArray = malloc(sizeof(NODE) * nodeCount);
	if (nodeArray == NULL)
	{
		THROW_ERROR(STATUS_FAILURE, "Could not allocate memory for map load!");
	}

	for (i = 0; i < nodeCount; i++)
	{
		if (fscanf(fp, "%d %d %d %d %d %d\n", &id, &startx, &starty, &endx, &endy, &front) != 6)
		{
			THROW_ERROR(STATUS_FAILURE, "Map data is not valid!");
		}
		else
		{
			nodeArray[id].id = id;
			nodeArray[id].wall.start.x = startx;
			nodeArray[id].wall.start.y = starty;
			nodeArray[id].wall.end.x = endx;
			nodeArray[id].wall.end.y = endy;
			nodeArray[id].wall.front = (bool)front;
		}
	}

	for (i = 0; i < nodeCount; i++)
	{
		if (fscanf(fp, "%d %d %d\n", &id, &leftid, &rightid) != 3)
		{
			THROW_ERROR(STATUS_FAILURE, "Map data is not valid!");
		}
		else
		{
			if (leftid != -1)
			{
				nodeArray[id].left = nodeArray + leftid;
			}
			else
			{
				nodeArray[id].left = NULL;
			}
			
			if (rightid != -1)
			{
				nodeArray[id].right = nodeArray + rightid;
			}
			else
			{
				nodeArray[id].right = NULL;
			}
		}
	}

	map->bspRoot = nodeArray;
	map->mapName = malloc(sizeof(char) * (strlen(mapName) + 1));
	strcpy(map->mapName, mapName);
	
	RETURN_STATUS_OK;
}