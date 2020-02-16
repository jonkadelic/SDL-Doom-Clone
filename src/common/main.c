// Includes
#include <SDL2/SDL.h>
#include <unistd.h>
#include <stdbool.h>

#include <graphics/graphics.h>
#include <graphics/framebuffer.h>
#include <graphics/map.h>
#include <io/error.h>
#include <io/map.h>

#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480

FRAMEBUFFER_HANDLE *	fb;

int main
(
	int argc,
	char* argv[]
)
{
	MAP map;
	bool draw = true;

	Error_Handle(Map_Load(argv[1], &map));

	Error_Handle(Framebuffer_Create(SCREEN_WIDTH, SCREEN_HEIGHT, &fb));

	while (draw)
	{
		SDL_Event event;

		Graphics_DrawMap(fb, &map);

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				draw = false;
			}
		}
	}

	Error_Handle(Framebuffer_Destroy(fb));

	return 0;
}