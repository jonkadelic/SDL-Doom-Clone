// Includes
#include <SDL2/SDL.h>
#include <unistd.h>
#include <stdbool.h>

#include <graphics/graphics.h>
#include <io/error.h>
#include <io/map.h>

#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480

void BSP_PrintTree(NODE* node, int parent);

int main
(
	int argc,
	char* argv[]
)
{
	MAP map;
	bool draw = true;

	Error_Handle(Map_Load(argv[1], &map));

	BSP_PrintTree(map.bspRoot, 0);

	Error_Handle(Graphics_Init("Test Window", SCREEN_WIDTH, SCREEN_HEIGHT));

	while (draw)
	{
		SDL_Event event;

		Graphics_DrawMap(&map);

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				draw = false;
			}
		}
	}

	Error_Handle(Graphics_Deinit());

	return 0;
}

void BSP_PrintTree(NODE* node, int parent)
{
    static int index = 0;
    int me = index;

    index++;

    if (node->left == NULL && node->right == NULL)
    {
        printf("Node %d (parent %d) goes (X=%d, Y=%d) to (X=%d, Y=%d), no left, no right.\r\n",
                me,
                parent,
                node->line.start.x,
                node->line.start.y,
                node->line.end.x,
                node->line.end.y);
    }
    else if (node->left != NULL && node->right == NULL)
    {
        printf("Node %d (parent %d) goes (X=%d, Y=%d) to (X=%d, Y=%d), has left, no right.\r\n",
                me,
                parent,
                node->line.start.x,
                node->line.start.y,
                node->line.end.x,
                node->line.end.y);
        BSP_PrintTree(node->left, me);
    }
    else if (node->left == NULL && node->right != NULL)
    {
        printf("Node %d (parent %d) goes (X=%d, Y=%d) to (X=%d, Y=%d), no left, has right.\r\n",
                me,
                parent,
                node->line.start.x,
                node->line.start.y,
                node->line.end.x,
                node->line.end.y);
        BSP_PrintTree(node->right, me);
    }
    else if (node->left != NULL && node->right != NULL)
    {
        printf("Node %d (parent %d) goes (X=%d, Y=%d) to (X=%d, Y=%d), has left, has right.\r\n",
                me,
                parent,
                node->line.start.x,
                node->line.start.y,
                node->line.end.x,
                node->line.end.y);
        BSP_PrintTree(node->left, me);
        BSP_PrintTree(node->right, me);
    }
}