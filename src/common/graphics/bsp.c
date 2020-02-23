// Includes
#include <graphics/bsp.h>

#include <stddef.h>

// Defines
#define IN_FRONT	1
#define BEHIND		-1

// Global variables
int setIndex = 0;

// Function declarations
void BSP_TraverseNodes
(
	NODE *		node,
	NODE **		outputSet,
	MAP_POINT *	point
);

int BSP_IsPointInFrontOfNode
(
	NODE * 		node,
	MAP_POINT * point
);

// Function definitions
int BSP_GenerateOrderedLineSet
(
	MAP_POINT *	position,
	NODE *		inputSet,
	NODE **		outputSet
)
{
	setIndex = 0;

	BSP_TraverseNodes(inputSet, outputSet, position);

	return setIndex;
}

void BSP_TraverseNodes
(
	NODE *		node,
	NODE **		outputSet,
	MAP_POINT *	point
)
{
	int pos;
	
	if (node == NULL)
	{
		return;
	}
	
	pos = BSP_IsPointInFrontOfNode(node, point);
	
	if (node->left == NULL && node->right == NULL)
	{
		if (pos == IN_FRONT)
		{
			outputSet[setIndex++] = node;
		}
	}
	else
	{
		if (pos == IN_FRONT)
		{
			BSP_TraverseNodes(node->left, outputSet, point);
			outputSet[setIndex++] = node;
			BSP_TraverseNodes(node->right, outputSet, point);
		}
		else if (pos == BEHIND)
		{
			BSP_TraverseNodes(node->right, outputSet, point);
			outputSet[setIndex++] = node;
			BSP_TraverseNodes(node->left, outputSet, point);
		}
		else
		{
			BSP_TraverseNodes(node->right, outputSet, point);
			BSP_TraverseNodes(node->left, outputSet, point);
		}
	}

	if (pos == IN_FRONT)
	{
		node->draw = true;
	}
	else
	{
		node->draw = false;
	}
}

int BSP_IsPointInFrontOfNode
(
	NODE * 		node,
	MAP_POINT * point
)
{
	int aX = node->wall.start.x, bX = node->wall.end.x, cX = point->x, aY = node->wall.start.y, bY = node->wall.end.y, cY = point->y;

	int out = ((bX - aX) * (cY - aY) - (bY - aY) * (cX - aX));

	int pos = 0;

	if (out < 0)
	{
		pos = BEHIND;
	}
	else if (out > 0)
	{
		pos = IN_FRONT;
	}	
	else
	{
		pos = 0;
	}

	if (node->wall.front == false)
	{
		pos = -pos;
	}

	return pos;
}