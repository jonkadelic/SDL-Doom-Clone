// Includes
#include <graphics/bsp.h>

#include <stddef.h>

// Global variables
int setIndex = 0;

// Function declarations
void BSP_TraverseNodes
(
	NODE *	node,
	LINE *	outputSet,
	POINT *	point
);

bool BSP_IsPointInFrontOfNode
(
	NODE * node,
	POINT * point
);

// Function definitions
void BSP_GenerateOrderedLineSet
(
	POINT *	position,
	NODE *	inputSet,
	LINE *	outputSet
)
{
	setIndex = 0;

	BSP_TraverseNodes(inputSet, outputSet, position);
}

void BSP_TraverseNodes
(
	NODE *	node,
	LINE *	outputSet,
	POINT *	point
)
{
	if (node->left == NULL && node->right == NULL)
	{
		outputSet[setIndex++] = node->line;
	}
	else
	{
		int pos = BSP_IsPointInFrontOfNode(node, point);

		if (pos == 1)
		{
			BSP_TraverseNodes(node->left, outputSet, point);
			outputSet[setIndex++] = node->line;
			BSP_TraverseNodes(node->right, outputSet, point);
		}
		else if (pos == -1)
		{
			BSP_TraverseNodes(node->right, outputSet, point);
			outputSet[setIndex++] = node->line;
			BSP_TraverseNodes(node->left, outputSet, point);
		}
		else
		{
			BSP_TraverseNodes(node->right, outputSet, point);
			BSP_TraverseNodes(node->left, outputSet, point);
		}
	}
	
}

bool BSP_IsPointInFrontOfNode
(
	NODE * node,
	POINT * point
)
{
	int x = point->x;
	int y = point->y;
	int x1 = node->line.start.x;
	int x2 = node->line.end.x;
	int y1 = node->line.start.y;
	int y2 = node->line.end.y;

	int out = ((x - x1) * (y2 - y1)) - ((y - y1) * (x2 - x1));

	int pos = 0;

	if (out < 0)
	{
		pos = 1;
	}
	else if (out > 0)
	{
		pos = -1;
	}	
	else
	{
		pos = 0;
	}

	if (node->line.front == false)
	{
		pos = -pos;
	}

	return pos;
}