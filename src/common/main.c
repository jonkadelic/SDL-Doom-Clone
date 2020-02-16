// Includes
#include <SDL2/SDL.h>
#include <unistd.h>
#include <stdbool.h>

#include <graphics/graphics.h>
#include <graphics/framebuffer.h>
#include <graphics/map.h>
#include <io/error.h>
#include <io/map.h>
#include <graphics/renderer_fp.h>
#include <game/player.h>

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
	RENDERER_POINT a = { 0, 0 };
	RENDERER_POINT b = { 300, 0 };
	RENDERER_POINT c = { 300, 300 };
	RENDERER_POINT d = { 200, 50 };
	RENDERER_POINT pts[] = { a, b, c, d };
	RENDERER_POLYGON polygon =
	{
		4,
		pts
	};

	Error_Handle(Map_Load(argv[1], &map));

	Error_Handle(Framebuffer_Create(SCREEN_WIDTH, SCREEN_HEIGHT, &fb));

	player.fov = PLAYER_FOV;
	player.height = PLAYER_HEIGHT;
	player.position.x = 100;
	player.position.y = 100;

	while (draw)
	{
		SDL_Event event;

		//Graphics_DrawMap(fb, &map);
		//Graphics_DrawFilledPolygon(fb, &polygon, 0xFFFF0000);
		Graphics_RenderFirstPerson(fb, &map);
		Framebuffer_Blit(fb);
		Framebuffer_Clear(fb, 0xFF000000);
		Player_SetAngle(&player, player.angle + 1);

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